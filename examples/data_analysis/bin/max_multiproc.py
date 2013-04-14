#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Finds the maximum value in a text file of integers.

This program divides the file into several chunks, and spawns
a separate process to find the maximum in each chunk.
"""

import argparse
import os.path
from multiprocessing import Pool

from cs123.topk.max import find_file_ranges, find_max_in_range

def find_max_in_range_wrapper(args):
    """Wrapper around find_max_in_range.

    The multiprocessing library requires that this
    function have a single argument, so the args
    argument is actually a tuple:

       (fname, (range_start, range_end))
    """
    max_in_range = find_max_in_range(args[0], args[1])
    print "Chunk %i-%i done. Max: %i" % (args[1][0], args[1][1], max_in_range)
    return max_in_range 

def parse_command_line_arguments():
    """Parses the arguments provided through the
    command line. Run the program with option "-h"
    to see a human-readable description of the
    arguments"""

    description, epilog = __doc__.split("\n\n", 1)

    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=description,
        epilog=epilog)

    parser.add_argument('datafile', metavar='FILE',
                       help='Text file with one integer per line')
    parser.add_argument('-n', '--nchunks', dest='nchunks', action='store', type=int, required=True,
                       help='Number of chunks to divide the file into')

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

fname = args.datafile
nchunks = args.nchunks

franges = find_file_ranges(fname, nchunks)

print "Dividing the file into %i chunks:" % nchunks

for frange in franges:
    print "  %i - %i" % (frange[0],frange[1])
print

# Multi-processing magic
p = Pool(nchunks)
args = zip([fname]*nchunks, franges)
res = p.map(find_max_in_range_wrapper, args)

print
print "Maximum: %i" % (max(res))

