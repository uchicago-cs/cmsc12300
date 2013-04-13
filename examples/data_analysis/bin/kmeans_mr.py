# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#


from utils import *
import sys
import random
import numpy

from mrjob.job import MRJob


class MRKMeansChooseInitialCentroids(MRJob):

    def get_coordinates(self, _, line):
        l = line.split()
        yield None, [int(x) for x in l[:-1]]

    def find_ranges(self, _, points):
        minp = maxp = None
        for p in points:
            if minp is None or p < minp:
                minp = p
            if maxp is None or p > maxp:
                maxp = p
        yield None, (minp, maxp)

    def select_centroids(self, _, minmax):
        minP = maxP = None
        for minp, maxp in minmax:
            if minP is None or minp < minP:
                minP = minp
            if maxP is None or maxp > maxP:
                maxP = maxp

        yield None, (minP,maxP)

    def steps(self):
        return [self.mr(mapper=self.get_coordinates,
                        combiner=self.find_ranges,
                        reducer=self.select_centroids)]

if __name__ == '__main__':
    MRKMeansChooseInitialCentroids.run()

