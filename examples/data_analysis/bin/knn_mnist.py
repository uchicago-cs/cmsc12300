#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Uses k-nearest neighbor to classify MNIST data

If an index parameter is specified, KNN is run only on
the image in that index (in the testing set). The ascii-art representation
of the image and it K neighbors is shown, along with 
a message indicating whether the image was classified correctly.

If you select a specific image in the test set, KNN
will be run only on that image, and the program
will show the nearest neighbors and the computed label
(indicating whether is matches the known label or not)

If you do not specify an image, KNN will be run on
the entire testing set and, for each image in the testing
set, the following line will be output:

    IDX LABEL_KNOWN LABEL_KNN [XXX]

Where IDX is the index of the image, LABEL_KNOWN is the
known (correct) label of the image, LABEL_KNN is the
label produced by KNN, and the verbatim "XXX" string is
printed if the labels don't match.
"""

import heapq
import sys
import argparse

from cs123.data.mnist import MNISTReader, MNISTImage
from cs123.classification.knn import knn

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
                       help='Number of neighbors to use')
    parser.add_argument('-i', '--index', dest='index', action='store', type=int,
                       help="Image index")

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

datadir = args.datadir
k = args.k
idx = args.index

if idx == None:
    train = MNISTReader("%s/train-images-idx3-ubyte" % datadir, "%s/train-labels-idx1-ubyte" % datadir, preload=True)
    test = MNISTReader("%s/t10k-images-idx3-ubyte" % datadir, "%s/t10k-labels-idx1-ubyte" % datadir, preload=True)
else:
    train = MNISTReader("%s/train-images-idx3-ubyte" % datadir, "%s/train-labels-idx1-ubyte" % datadir)
    test = MNISTReader("%s/t10k-images-idx3-ubyte" % datadir, "%s/t10k-labels-idx1-ubyte" % datadir)

if idx == None:
    i = 0
    for p, known_label in test.images(as_array=True):
        label, nearest = knn(p, train.images(as_array=True), k)
        
        if label == known_label:
            x=""
        else:
            x="XXX"

        print "%i %i %i %s" % (i, known_label, label, x)
        sys.stdout.flush()

        i+=1
else:
    img = test.get_image(idx)

    label, nearest = knn(img.as_array(), train.images(as_array=True), k)

    print "K-NEAREST NEIGHBORS"
    print "============================================================"
    print
    for dist, nearpoint, nearlabel  in nearest:
        print MNISTImage(nearpoint, nearlabel, 28, 28).as_asciiart()
        print

    print "CLASSIFIED IMAGE"
    print "============================================================"
    print
    print img.as_asciiart()
    print 
    print "Labelled as %d" % label

    if label == img.label:
        print "Labels match!"
    else:
        print "Labels do not match."



