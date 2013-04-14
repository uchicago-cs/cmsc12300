#!/usr/bin/python
#
# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""Find the most frequent hashtags in the Twitter
public stream.

Connects to the Twitter public stream and uses a
lossy counter to keep track of the most popular
hashtags (where "most popular" is "appears at least some
percent of the time"). The percentage is specified
as a command-line parameter.
 
For this to work, you need to create a file
with your Twitter username and password, separated
by a single space (by default, the program will
look for a ".tpass" file, but a different path
can be specified with the "-c" option)
 
See the documentation in the cs123.topk.lossycount module
for more details on how lossy counting works.
"""

import argparse
import tweetstream
import re
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

    parser.add_argument('-s', '--s', dest='s', action='store', type=float, required=True,
                       help='Minimum frequency')
    parser.add_argument('-c', '--credentials', dest='credentials', action='store',
                        default="./.tpass",
                        help='File with Twitter credentials (username and password, separated by a space)')

    args = parser.parse_args()
    
    return args

args = parse_command_line_arguments()

username,password = open(args.credentials).read().strip().split()

stream = tweetstream.SampleStream(username,password)
lc = LossyCounter(args.s)

N=0
while True:
    try:
        t = stream.next()
    except Exception, e:
        print e
        break
    if t.has_key("text"):
        tags = re.findall("#[A-Za-z0-9]+", t["text"])
        if len(tags) > 0:
            for tag in tags:
                print tag
                N+=1
                lc.count_element(tag)

            if N > 0 and N % 500 == 0:
                counts = lc.get_counts()
                print
                print " N = %i" % N
                print "=============================="
                print "%s\t%s\t%s" % ("tag".ljust(30), "f".ljust(6), "delta".ljust(6))
                print "-"*30 + "\t" + "-"*6 + "\t" + "-"*6
                for e in counts:
                    print "%s\t%6i\t%6i" % (e.e.ljust(30), e.f, e.delta)
                print "=============================="
                print

