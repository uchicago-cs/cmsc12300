#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Finds the top values in a text file of integers by
using a lossy counter. 

Instead of specifying a "top K" value, you must specify 
a minimum frequency (e.g., "only keep track of elements 
that appear at least 0.1% of the times)
 
See the documentation in the cs123.topk.lossycount module
for more details on how lossy counting works.
"""

import argparse
from cs123.topk.lossycount import LossyCounter

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
    parser.add_argument('-s', '--s', dest='s', action='store', type=float, required=True,
                       help='Minimum frequency')

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

f = open(args.datafile)
s = args.s

lc = LossyCounter(s)

for l in f:
    n = int(l)
    lc.count_element(n)

counts = lc.get_counts()

print "n\tf\tdelta"
for e in counts:
    print "%i\t%i\t%i" % (e.e, e.f, e.delta)
    

