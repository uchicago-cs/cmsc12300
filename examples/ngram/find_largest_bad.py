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
# word in the file across all years. 
# It runs in O(n) time and also uses O(n) space, so it is not
# a good solution for large datasets.

import sys

f = open(sys.argv[1])

grams = {}
lines = 0
for line in f:
    gram, year, n, pages, books = line.split()

    grams[gram] = grams.setdefault(gram, 0) + int(n)

    lines += 1
    if lines % 1000000 == 0:
        print "Processed %iM entries" % (lines / 1000000)

largest_n = 0
largest_gram = None
for gram in grams:
    if grams[gram] > largest_n:
        largest_n = grams[gram]
        largest_gram = gram

print "Largest: %s %i" % (largest_gram, largest_n)
