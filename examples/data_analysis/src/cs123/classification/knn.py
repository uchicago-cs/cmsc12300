#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""This module provides functions to perform
K-Nearest-Neighbor classification on labelled
numpy arrays
"""

import heapq
import sys

from cs123.common.utils import distance

def find_majority(labels):
    """Finds the majority label in a list of labels
    in a single pass
    """

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

def knn(p, train, k):
    """Does a K-nearest-neighbors classification on
    a point p given a training set.

    Parameters:
    - p: Numpy array with the point to classify
    - train: An iterable object with (p, label) entries,
      where p is a numpy array representing a point
      in the training set, and label is the label for that
      point.
    - k: The number of neighbors to use.
    """

    h =  [[-sys.maxint,None,None] for x in range(k)]

    for pt, label in train:
        k_distance, _, _ = h[0]

        k_distance = -k_distance

        dist = distance(p.astype("float"), pt)

        if dist < k_distance:
            heapq.heapreplace(h, [-dist, pt, label])

    labels = [label for dist,pt,label in h]
    max_label = find_majority(labels)

    h.sort()
    for x in h:
        x[0] = -x[0]

    return (max_label, h)


