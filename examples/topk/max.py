#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Finds the maximum value in a text file of integers by
# doing a linear search.

import sys

fname = sys.argv[1]

n_max = 0

f = open(fname)
for n in f:
    if int(n) > n_max:
        n_max = int(n)
f.close()

print n_max

