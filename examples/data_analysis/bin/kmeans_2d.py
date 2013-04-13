# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Uses k-means clustering to classify points into K clusters
#
#     python kmeans.py K DATAFILE [CLUSTERFILE]
#
# Where DATAFILE is a file with the points. Each line has
# an entry like this:
#
#     X Y
#
# If no CLUSTERFILE parameters is specified, the clustering
# will be visualized using a scatterplot after each iteration. 
#
# If CLUSTERFILE is specified, the points are saved to a file 
# where each line contains the following:
#
#     X Y C
#
# Where C is a number [0..K-1] specifying what cluster
# the point belongs to.

from common.kmeans import KMeans
from common.utils import read_cluster_points, gen_scatter_plot, distance
import sys
import random
import numpy

CUTOFF = 1.0

if len(sys.argv) in (3,4):
    k = int(sys.argv[1])
    datafile = sys.argv[2]
    if len(sys.argv) == 4:
        resfile = sys.argv[3]
    else:
        resfile = None
else:
    print "Usage %s K DATAFILE [CLUSTERFILE]" % (sys.argv[0])

points, _, _ = read_cluster_points(datafile)

km = KMeans(points, k)

centroids = km.select_random_centroids()

iteration=1
while True:
    print "Iteration #%i with centroids %s" % (iteration, [(x[0],x[1]) for x in centroids])

    new_centroids, point_assignment = km.get_k_means(centroids)

    if resfile == None:
        gen_scatter_plot(points, point_assignment, centroids, resfile)

    distances = [distance(c1,c2) for c1,c2 in zip(centroids,new_centroids)]
    max_d = max(distances)

    if max_d <= CUTOFF:
        print "Max shift: %.2f <= %.2f" % (max_d, CUTOFF)
        print "Algorithm has converged."
        gen_scatter_plot(points, point_assignment, new_centroids, resfile)
        break
    else:
        print "Max shift: %.2f > %.2f" % (max_d, CUTOFF)
        print "Algorithm hasn't converged yet."
        centroids = new_centroids
        iteration += 1


