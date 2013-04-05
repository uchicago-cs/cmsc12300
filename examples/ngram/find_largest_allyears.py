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
# word in the file across all years. It runs in O(n) time,
# but only needs O(1) space.

import sys

f = open(sys.argv[1])

lines = 0
largest = 0

cur_gram = None
cur_gram_count = 0
largest_gram = None
largest_n = 0
for line in f:
    gram, year, n, pages, books = line.split()

    if cur_gram is None or gram != cur_gram:
        if cur_gram_count > largest_n:
            largest_n = cur_gram_count
            largest_gram = cur_gram        
        cur_gram_count = 0
        cur_gram = gram
    
    cur_gram_count += int(n)

    lines += 1
    if lines % 1000000 == 0:
        print "Processed %iM entries" % (lines / 1000000)
        print "Largest so far: %s %i" % (largest_gram, largest_n)
        print


print "Largest so far: %s %i" % (largest_gram, largest_n)

