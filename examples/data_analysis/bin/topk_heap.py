#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Finds the top-K values in a text file of integers by
using a priority queue.

Runs in O(n*logK)
"""

import argparse
import heapq

from cs123.topk.heap import get_topk

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
    parser.add_argument('-k', '--k', dest='k', action='store', type=int, required=True,
                       help='Number of top elements to find')

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

f = open(args.datafile)
k = args.k

top = get_topk(f, k)

i=1
for count, n in top:
    print "%i\t%i\t%i" % (i, n, count)
    i+=1
    

