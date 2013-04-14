#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Uses k-means clustering to classify points into K clusters

The input file must be a text file where each line has
an entry like this:

     X Y

If no output file is specified, the clustering
will be visualized using a scatterplot after each iteration. 

If an output file is specified, the points are saved to a file 
where each line contains the following:

     X Y C

Where C is a number [0..K-1] specifying what cluster
the point belongs to."""

import argparse

from cs123.clustering.kmeans import KMeans
from cs123.data.cluster import ClusteredData
from cs123.data.visualizers import gen_scatter_plot
from cs123.common.utils import distance

def parse_command_line_arguments():
    """Parses the arguments provided through the
    command line. Run the program with option "-h"
    to see a human-readable description of the
    arguments"""

    description, epilog = __doc__.split("\n\n", 1)

    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=description,
        epilog=epilog)

    parser.add_argument('datafile', metavar='FILE',
                       help='File with 2-dimensional data to run k-means on')
    parser.add_argument('-k', '--k', dest='k', action='store', type=int, required=True,
                       help='The number of clusters')
    parser.add_argument('-o', '--outfile', metavar='FILE', dest='outfile', action='store',
                       help='The file to save the points along with their cluster assignment.')
    parser.add_argument('-t', '--threshold', dest='cutoff', action='store', type=float, default=1.0,
                       help="Converge once the centroids move less than this threshold.")

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

data = ClusteredData.from_file(args.datafile)
points = data.to_array()

km = KMeans(points, args.k)

centroids = km.select_random_centroids()

iteration=1
while True:
    print "Iteration #%i with centroids %s" % (iteration, [(x[0],x[1]) for x in centroids])

    new_centroids, point_assignment = km.get_k_means(centroids)

    if args.outfile == None:
        gen_scatter_plot(points, point_assignment, centroids)

    distances = [distance(c1,c2) for c1,c2 in zip(centroids,new_centroids)]
    max_d = max(distances)

    if max_d <= args.cutoff:
        print "Max shift: %.2f <= %.2f" % (max_d, args.cutoff)
        print "Algorithm has converged."
        if args.outfile == None:
            gen_scatter_plot(points, point_assignment, new_centroids)
        break
    else:
        print "Max shift: %.2f > %.2f" % (max_d, args.cutoff)
        print "Algorithm hasn't converged yet."
        centroids = new_centroids
        iteration += 1

if args.outfile != None:
    new_data = ClusteredData(dim=2)
    for p, k in zip(points, point_assignment):
        new_data.add_point(p, k)
    new_data.to_file(args.outfile)

