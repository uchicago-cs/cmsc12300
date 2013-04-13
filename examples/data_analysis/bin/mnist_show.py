#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Visualizes an image from the MNIST dataset
#
#     python -m data.show_mnist_image.py DATADIR ("TEST"|"TRAIN") IDX
#
# DATADIR is the directory containing the MNIST files,
# which are assumed to have the standard names:
#
#     t10k-images-idx3-ubyte   Test set (images)
#     t10k-labels-idx1-ubyte   Test set (labels)
#     train-images-idx3-ubyte  Training set (images)
#     train-labels-idx1-ubyte  Training set (labels)
#
# The second parameter must be TEST or TRAIN, to specify what dataset
# to use. The IDX parameter specifies the index within the file.


from common.mnist import MNISTReader
import sys


if len(sys.argv) == 4:
    datadir = sys.argv[1]
    dataset = sys.argv[2]
    idx = int(sys.argv[3])
else:
    print "Usage %s DATADIR (""TEST""|""TRAIN"") IDX" % (sys.argv[0])
    exit(1)

if dataset == "TRAIN":
    data = MNISTReader("%s/train-images-idx3-ubyte" % datadir, "%s/train-labels-idx1-ubyte" % datadir)
elif dataset == "TEST":
    data = MNISTReader("%s/t10k-images-idx3-ubyte" % datadir, "%s/t10k-labels-idx1-ubyte" % datadir)
else:
    print "Usage %s DATADIR (""TEST""|""TRAIN"") IDX" % (sys.argv[0])
    exit(1)

img = data.get_image(idx)

print img.as_asciiart()
print "Labelled as %d" % img.label

img.as_image().show()


