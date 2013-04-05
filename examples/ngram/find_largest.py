#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# This example requires files from the Google N-Gram dataset.
# (any file from the dataset should work with it). You can
# download files here:
#
#    http://storage.googleapis.com/books/ngrams/books/datasetsv2.html
#
# This example takes an n-gram file and finds the most popular
# word-year in the file across all years. It runs in O(n) time,
# and only needs O(1) space.

import sys

f = open(sys.argv[1])

lines = 0
largest = 0
largest_line = None
for line in f:
    gram, year, n, pages, books = line.split()

    n = int(n)

    if n > largest:
        largest = n
        largest_line = line

    lines += 1
    if lines % 1000000 == 0:
        print "Processed %iM entries" % (lines / 1000000)
        print "Largest so far:", largest_line

print "Largest:", largest_line
