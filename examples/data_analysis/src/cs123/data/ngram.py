# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""This module provides functions that perform some
basic operations on the Google N-Gram dataset.
(any file from the dataset should work with these functions). 
You can download files here:

    http://storage.googleapis.com/books/ngrams/books/datasetsv2.html

"""

def find_largest(fname, debug=False):
    """Takes an n-gram file and finds the most popular
    word in the file across all years (i.e., the line
    in the file with the biggest value for the occurrences
    field). It runs in O(n) time, but only needs O(1) space.

    Parameters:
    - fname: Name of a file containing an N-Gram dataset
    - debug: If True, prints a status message for every
             millionth line processed.
    """
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
        if debug and lines % 1000000 == 0:
            print "Processed %iM entries" % (lines / 1000000)
            print "Largest so far:", largest_line
    
    return largest_line.split()


def find_largest_allyears_bad(fname, debug=False):
    """Takes an n-gram file and finds the most popular
    word in the dataset, taking into account that the same
    word appears in multiple years. 
    It runs in O(n) time and also uses O(n) space, so it is not
    a good solution for large datasets.

    Parameters:
    - fname: Name of a file containing an N-Gram dataset
    - debug: If True, prints a status message for every
             millionth line processed.
    """
    grams = {}
    lines = 0
    for line in f:
        gram, year, n, pages, books = line.split()

        grams[gram] = grams.setdefault(gram, 0) + int(n)

        lines += 1
        if debug and lines % 1000000 == 0:
            print "Processed %iM entries" % (lines / 1000000)

    largest_n = 0
    largest_gram = None
    for gram in grams:
        if grams[gram] > largest_n:
            largest_n = grams[gram]
            largest_gram = gram

    return largest_gram, largest_n


def find_largest_allyears_bad(fname, debug=False):
    """Takes an n-gram file and finds the most popular
    word in the dataset, taking into account that the same
    word appears in multiple years. 
    It runs in O(n) time but only needs O(1) space.

    Parameters:
    - fname: Name of a file containing an N-Gram dataset
    - debug: If True, prints a status message for every
             millionth line processed.
    """
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
        if debug and lines % 1000000 == 0:
            print "Processed %iM entries" % (lines / 1000000)
            print "Largest so far: %s %i" % (largest_gram, largest_n)
            print

    return largest_gram, largest_n

