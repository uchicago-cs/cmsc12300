#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Finds the top K values in a text file of integers by
# using a priority queue. Runs in O(n·logK)

import sys
import heapq

f = open(sys.argv[1])
k = int(sys.argv[2])

counts = {}

for l in f:
    n = int(l)
    counts[n] = counts.setdefault(n, 0) + 1

h = [(count,n) for (n,count) in counts.items()[:k]]
heapq.heapify(h)

for n, count in counts.items()[k:]:
    min_count, min_n = h[0]

    if count > min_count:
        heapq.heapreplace(h, (count, n))

h.sort(reverse=True)

i=1
for count, n in h:
    print "%i\t%i\t%i" % (i, n, count)
    i+=1
    

