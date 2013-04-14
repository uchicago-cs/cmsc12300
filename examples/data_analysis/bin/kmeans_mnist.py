#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Runs k-means clustering on the MNIST dataset

The output is an image with the K centroids representing
the K "average" digits found by k-means."""

import sys
import random
import numpy
import argparse
from PIL import Image

from cs123.clustering.kmeans import KMeans
from cs123.data.mnist import MNISTReader
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

    parser.add_argument('datadir', metavar='DIR',
                       help='Directory containing the MNIST files')
    parser.add_argument('-k', '--k', dest='k', action='store', type=int, required=True,
                       help='The number of clusters')
    parser.add_argument('-o', '--outfile', metavar='FILE', dest='outfile', action='store',
                       help='The file to save k-mean images to. If none is specified, the image is displayed interactively.')
    parser.add_argument('-t', '--threshold', dest='cutoff', action='store', type=float, default=100.0,
                       help="Converge once the centroids move less than this threshold.")

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

k = args.k
cutoff = args.cutoff

print "Loading data..."
test = MNISTReader("%s/t10k-images-idx3-ubyte" % args.datadir, "%s/t10k-labels-idx1-ubyte" % args.datadir)

points = None
for img in test.images():
    if points is None:
        points = numpy.array([img.imgdata])
    else:
        points = numpy.append(points, [img.imgdata], axis=0)

km = KMeans(points, k)

centroids = km.select_random_centroids()

iteration=1
while True:
    print "Iteration #%i" % iteration

    new_centroids, point_assignment = km.get_k_means(centroids)

    distances = [distance(c1,c2) for c1,c2 in zip(centroids,new_centroids)]
    max_d = max(distances)

    if max_d <= cutoff:
        print "Max shift: %.2f <= %.2f" % (max_d, cutoff)
        print "Algorithm has converged."
        break
    else:
        print "Max shift: %.2f > %.2f" % (max_d, cutoff)
        print "Algorithm hasn't converged yet."
        centroids = new_centroids
        iteration += 1

imgarray = numpy.reshape(255 - new_centroids[0], (28, 28))
for centroid in new_centroids[1:]:
    imgc = numpy.reshape(255 - centroid, (28, 28))
    imgarray = numpy.hstack( (imgarray, imgc) )

i = Image.fromarray(imgarray.astype(numpy.uint8))
i.show()
if args.outfile is not None:
    i.save(args.outfile)



