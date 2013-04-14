#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Visualizes an image from the MNIST dataset.

The directory containing the MNIST files is assumed to have the standard names:

    t10k-images-idx3-ubyte   Test set (images)
    t10k-labels-idx1-ubyte   Test set (labels)
    train-images-idx3-ubyte  Training set (images)
    train-labels-idx1-ubyte  Training set (labels)

"""

import argparse

from cs123.data.mnist import MNISTReader

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
    parser.add_argument('-d', '--dataset', dest='dataset', action='store', required=True,
                        choices = ("TEST","TRAIN"),
                        help='Dataset to use (testing or training)')
    parser.add_argument('-i', '--index', dest='index', action='store', type=int, required=True,
                       help="Image index")

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

datadir = args.datadir
dataset = args.dataset
idx = args.index

if dataset == "TRAIN":
    data = MNISTReader("%s/train-images-idx3-ubyte" % datadir, "%s/train-labels-idx1-ubyte" % datadir)
elif dataset == "TEST":
    data = MNISTReader("%s/t10k-images-idx3-ubyte" % datadir, "%s/t10k-labels-idx1-ubyte" % datadir)

img = data.get_image(idx)

print img.as_asciiart()
print "Labelled as %d" % img.label

img.as_image().show()


