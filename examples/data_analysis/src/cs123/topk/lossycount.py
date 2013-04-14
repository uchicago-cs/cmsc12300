# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""
This module implements the Lossy Count algorithm described in

    Gurmeet Singh Manku and Rajeev Motwani. 2002. Approximate 
    frequency counts over data streams. In Proceedings of the 
    28th international conference on Very Large Data Bases 
    (VLDB '02). VLDB Endowment 346-357.

To use it, simply create a LossyCounter object like this:

    lc = LossyCounter(s)

Where 's' is the minimum frequency. For example, if you
create a LossyCounter with s=0.01, only items in the stream
that account for at least 1% of the data will be counted.
The paper above also refers to this parameter as 's'

Next, just count items like this:

    for item in stream:
        lc.count_element(item)

Then, you can use the counts() method to obtain a list of
Entry objects representing the counted items in the string.
Each Entry object has three members: e, the counted item (as
passed to count_element()), f, the absolute frequency, and
delta, the absolute error (as described in the paper)
"""

import math

class Entry(object):
    def __init__(self, e,f,delta):
        self.e = e
        self.f = f
        self.delta = delta

class LossyCounter(object):
    
    FACTOR = 0.1

    def __init__(self, s):
        self.s = s
        self.error = s * self.FACTOR
        self.w = int(1/self.error)
        self.entries = {}
        self.N = 0

    def count_element(self, elem):
        self.N += 1
        b_current = int(math.ceil(float(self.N)/self.w))

        if self.entries.has_key(elem):
            self.entries[elem].f += 1
        else:
            self.entries[elem] = Entry(elem, 1, b_current - 1)

        if self.N % self.w == 0:
            for elem in self.entries.keys():
                e = self.entries[elem]
                if e.f + e.delta <= b_current:
                    del self.entries[elem]

    def get_counts(self):
        return [e for e in self.entries.values() if e.f >= (self.s - self.error)*self.N]

