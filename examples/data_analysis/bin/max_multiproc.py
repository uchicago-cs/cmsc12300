#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Finds the maximum value in a text file of integers by
# dividing the file into several chunks, and spawning
# a separate process to find the maximum in each chunk.
#
# Takes two command-line parameters: the file and the 
# number of chunks:
#
#     python max_multiproc.py numbers.txt 4
#

import sys
import os.path
from multiprocessing import Pool

# Given a text file with one integer per line,
# this functions finds the boundaries of the file
# that divide it into four chunks (taking into account
# that we don't want to divide the file mid-number;
# it has to be divided after a newline)
def find_file_ranges(f, chunks):
    f.seek(0,2)
    fsize = f.tell()

    ranges = []
    chunk_size = fsize / chunks
    start = 0
    for i in range(chunks):
        f.seek(start + chunk_size)
        l = f.readline()
        end = min(start + chunk_size + len(l) - 1, fsize)
        ranges.append( (start, end) )
        start = end + 1

    return ranges

# Given a range of bytes in the file, and assuming
# that the range includes complete lines (as returned
# by find_file_ranges), return the maximum number
# in that range.
#
# The multiprocessing library requires that this
# function have a single argument, so the args
# argument is actually a tuple:
#
#    (fname, (range_start, range_end))
#
def find_max_in_range(args):
    fname = args[0]
    frange = args[1]

    f = open(fname)
    n_max = 0

    f.seek(frange[0])

    for n in f:
        if int(n) > n_max:
            n_max = int(n)
        if f.tell() >= frange[1]:
            break

    f.close()

    print "Chunk (%i - %i) done (max=%i)." % (frange[0], frange[1],n_max)

    return n_max


fname = sys.argv[1]
nchunks = int(sys.argv[2])


f = open(fname)

franges = find_file_ranges(f, nchunks)

print "Dividing the file into %i chunks:" % nchunks

for frange in franges:
    print "  %i - %i" % (frange[0],frange[1])
print

# Multi-processing magic
p = Pool(nchunks)
args = zip([fname]*nchunks, franges)
res = p.map(find_max_in_range, args)

print
print "Maximum: %i" % (max(res))


f.close()
