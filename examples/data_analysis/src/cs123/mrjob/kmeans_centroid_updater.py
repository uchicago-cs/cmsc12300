# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#

import sys
import random
import numpy
import pickle

from mrjob.job import MRJob



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


if __name__ == '__main__':
    MRKMeansUpdateCentroids.run()
