# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#

import sys
import random
import numpy
import pickle

from mrjob.job import MRJob
from kmeans_centroid_selector import MRKMeansChooseInitialCentroids
from kmeans_centroid_updater import MRKMeansUpdateCentroids

def extract_centroids(job, runner):
    c = []
    for line in runner.stream_output():
        key, value = job.parse_output_line(line)
        print key, value
        c.append(value)
    return c

# If we were running on AWS, we would simply write the centroids
# to an S3 bucket, and then read them from the jobs.
def write_centroids_to_disk(centroids, fname):
    f = open(fname, "w")
    pickle.dump(centroids, f)
    f.close()

def get_biggest_diff(centroids,new_centroids):
    distances = [numpy.linalg.norm(numpy.array(c1) - c2) for c1,c2 in zip(centroids,new_centroids)]
    max_d = max(distances)
    return max_d

CENTROIDS_FILE="/tmp/emr.kmeans.centroids"

if __name__ == '__main__':
    args = sys.argv[1:]

    choose_centroids_job = MRKMeansChooseInitialCentroids(args=args)
    with choose_centroids_job.make_runner() as choose_centroids_runner:
        choose_centroids_runner.run()

        centroids = extract_centroids(choose_centroids_job, choose_centroids_runner)
        write_centroids_to_disk(centroids, CENTROIDS_FILE)

        i = 1
        while True:
            print "Iteration #%i" % i
            update_centroids_job = MRKMeansUpdateCentroids(args=args + ['--centroids='+CENTROIDS_FILE])
            with update_centroids_job.make_runner() as update_centroids_runner:
                update_centroids_runner.run()

                new_centroids = extract_centroids(update_centroids_job, update_centroids_runner)
                write_centroids_to_disk(new_centroids, CENTROIDS_FILE)

                diff = get_biggest_diff(centroids, new_centroids)

                if diff > 10.0:
                    centroids = new_centroids
                else:
                    break

                i+=1





