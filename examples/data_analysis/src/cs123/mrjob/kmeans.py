# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#

import sys
import random
import numpy
import pickle

from mrjob.job import MRJob


class MRKMeansChooseInitialCentroids(MRJob):

    def __init__(self, args):
        MRJob.__init__(self, args)

    def configure_options(self):
        super(MRKMeansChooseInitialCentroids, self).configure_options()
        self.add_passthrough_option(
            '--k', type='int', help='Number of clusters')

    def get_coordinates(self, _, line):
        l = line.split()
        if len(l) == 1:
            return
        
        yield None, [int(x) for x in l[:-1]]

    def find_ranges(self, _, points):
        minp = maxp = numpy.array(points.next())
        for p in points:
            minp = numpy.minimum(minp, p)
            maxp = numpy.maximum(maxp, p)

        yield None, minp.tolist()
        yield None, maxp.tolist()


    def select_centroids(self, _, minmax):
        minp = maxp = numpy.array(minmax.next(), dtype=float)
        for p in minmax:
            minp = numpy.minimum(minp, p)
            maxp = numpy.maximum(maxp, p)

        # Find the K "average" centroids
        k = self.options.k
        step = (maxp-minp) / k

        for i in range(k):
            yield None, (minp + step*i).tolist()

    def steps(self):
        return [self.mr(mapper=self.get_coordinates,
                        combiner=self.find_ranges,
                        reducer=self.select_centroids)]

class MRKMeansUpdateCentroids(MRJob):

    def configure_options(self):
        super(MRKMeansUpdateCentroids, self).configure_options()
        self.add_passthrough_option(
            '--k', type='int', help='Number of clusters')
        self.add_file_option('--centroids')

    def get_centroids(self):
        f = open(self.options.centroids)
        centroids = pickle.load(f)
        f.close()
        return centroids

    def assign_cluster(self, _, line):
        l = line.split()
        if len(l) == 1:
            return

        point = numpy.array([float(x) for x in l[:-1]])
        centroids = self.get_centroids()
        
        distances = [numpy.linalg.norm(point - c) for c in centroids]
        cluster = numpy.argmin(distances)

        yield int(cluster), point.tolist()

    def partial_sum(self, cluster, points):
        s = numpy.array(points.next())
        n = 1
        for p in points:
            s += p
            n += 1

        yield cluster, (s.tolist(), n)

    def compute_average(self, cluster, partial_sums):
        SUM, N = partial_sums.next()
        SUM = numpy.array(SUM)
        for ps, n in partial_sums:
            SUM += ps
            N += n

        yield cluster, (SUM / N).tolist()

    def steps(self):
        return [self.mr(mapper=self.assign_cluster,
                        combiner=self.partial_sum,
                        reducer=self.compute_average)]

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





