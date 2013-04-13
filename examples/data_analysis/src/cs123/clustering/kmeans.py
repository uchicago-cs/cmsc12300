# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

import sys
import random
import numpy
from cs123.common.utils import distance

class KMeans(object):
    
    def __init__(self, points, k):
        self.points = points
        self.k = k

    def select_random_centroids(self):
        return numpy.array(random.sample(self.points, self.k))

    def get_k_means(self, centroids):
        point_assignment = []
        for n in self.points:
            distances = [distance(n,c) for c in centroids]
            point_assignment.append(numpy.argmin(distances))

        new_centroids = numpy.array([ numpy.zeros(self.points.shape[1]) for i in range(self.k)])
        points_in_cluster = [0]*self.k
        for p,i in zip(self.points,point_assignment):
            new_centroids[i] += p
            points_in_cluster[i] += 1

        for i in range(self.k):
            new_centroids[i] /= points_in_cluster[i]

        return new_centroids, point_assignment


