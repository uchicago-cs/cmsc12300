#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Finds the top values in a text file of integers by
# using a lossy counter. Instead of specifying a
# "top K" value, you must specify a minimum frequency
# (e.g., "only keep track of elements that appear
# at least 0.1% of the times)
# 
# See the documentation in the lossycount.py module
# for more details on how lossy counting works.

import sys
from lossycount import LossyCounter

f = open(sys.argv[1])
s = float(sys.argv[2])

lc = LossyCounter(s)

for l in f:
    n = int(l)
    lc.count_element(n)

counts = lc.get_counts()

print "n\tf\tdelta"
for e in counts:
    print "%i\t%i\t%i" % (e.e, e.f, e.delta)
    

