#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""This module provides a function to find the
top K values in a list of integers by
using a priority queue. Runs in O(n·logK)"""

import heapq

def get_topk(l, k):
    """Finds the top K elements in a list
    of integers.

    Parameters:
    - l: list of integers
    - k: an integer
    """
    counts = {}

    for i in l:
        counts[i] = counts.setdefault(i, 0) + 1

    h = [(count,n) for (n,count) in counts.items()[:k]]
    heapq.heapify(h)

    for n, count in counts.items()[k:]:
        min_count, min_n = h[0]

        if count > min_count:
            heapq.heapreplace(h, (count, n))

    h.sort(reverse=True)

    return h

