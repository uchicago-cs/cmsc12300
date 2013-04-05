#!/usr/bin/python
#
# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Connect to the Twitter public stream and use a
# lossy counter to keep track of the most popular
# hashtags (where "most popular" is "appears at least some
# percent of the time"). The percentage is specified
# as a command-line parameter.
# 
# For this to work, you need to create a ".tpass" file
# with your Twitter username and password, separated
# by a single space.
# 
# See the documentation in the lossycount.py module
# for more details on how lossy counting works.

import sys
import tweetstream
import re
from lossycount import LossyCounter

s = float(sys.argv[1])

username,password = open(".tpass").read().strip().split()

stream = tweetstream.SampleStream(username,password)
lc = LossyCounter(s)

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

