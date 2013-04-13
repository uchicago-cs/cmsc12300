#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Uses k-nearest neighbor to classify MNIST data
#
#     python -m knn.knn_mnist.py DATADIR K [IDX]
#
# DATADIR is the directory containing the MNIST files,
# which are assumed to have the standard names:
#
#     t10k-images-idx3-ubyte   Test set (images)
#     t10k-labels-idx1-ubyte   Test set (labels)
#     train-images-idx3-ubyte  Training set (images)
#     train-labels-idx1-ubyte  Training set (labels)
#
# The K parameter specifies how many neighbors to use.
# If no IDX parameter is specified, then KNN is run on
# the entire testing set and, for each image in the testing
# set, outputs the following line:
#
#     IDX LABEL_KNOWN LABEL_KNN [XXX]
#
# Where IDX is the index of the image, LABEL_KNOWN is the
# known (correct) label of the image, LABEL_KNN is the
# label produced by KNN, and the verbatim "XXX" string is
# printed if the labels don't match.
#
# If an IDX parameter is specified, KNN is run only on
# the image in that index. The ascii-art representation
# of the image and it K neighbors is shown, along with 
# a message indicating whether the image was classified correctly.


from common.mnist import MNISTReader
import heapq
import sys

def find_majority(labels):
    labels.sort()
    max_occur = 0
    max_label = None
    cur_occur = 0
    cur_label = labels[0]
    for label in labels:
        if label == cur_label:
            cur_occur += 1
        elif label != cur_label:
            cur_label = label
            cur_occur = 1
        
        if cur_occur > max_occur:
            max_occur = cur_occur
            max_label = cur_label
    
    return max_label

def do_single_knn(img, train, k):
    h =  [[-sys.maxint,None] for x in range(k)]

    for timg in train.images():
        k_distance, k_image = h[0]

        k_distance = -k_distance

        distance = img.distance(timg)

        if distance < k_distance:
            heapq.heapreplace(h, [-distance, timg])

    labels = [timg.label for dist,timg in h]
    max_label = find_majority(labels)

    h.sort()
    for x in h:
        x[0] = -x[0]

    return (max_label, h)



if len(sys.argv) in (3,4):
    datadir = sys.argv[1]
    k = int(sys.argv[2])
    if len(sys.argv) == 4:
        idx = int(sys.argv[3])
    else:
        idx = None
else:
    print "Usage %s DATADIR K [IDX]" % (sys.argv[0])
    exit(1)


if idx == None:
    train = MNISTReader("%s/train-images-idx3-ubyte" % datadir, "%s/train-labels-idx1-ubyte" % datadir, preload=True)
    test = MNISTReader("%s/t10k-images-idx3-ubyte" % datadir, "%s/t10k-labels-idx1-ubyte" % datadir, preload=True)
else:
    train = MNISTReader("%s/train-images-idx3-ubyte" % datadir, "%s/train-labels-idx1-ubyte" % datadir)
    test = MNISTReader("%s/t10k-images-idx3-ubyte" % datadir, "%s/t10k-labels-idx1-ubyte" % datadir)

if idx == None:
    i = 0
    for img in test.images():
        label, nearest = do_single_knn(img, train, k)
        
        if label == img.label:
            x=""
        else:
            x="XXX"

        print "%i %i %i %s" % (i, img.label, label, x)
        sys.stdout.flush()

        i+=1
else:
    img = test.get_image(idx)

    label, nearest = do_single_knn(img, train, k)

    print "K-NEAREST NEIGHBORS"
    print "============================================================"
    print
    for nearlabel, nearimg in nearest:
        print nearimg.as_asciiart()
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



