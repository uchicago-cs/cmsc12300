# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Python implementation of async.cpp (spawn a single
# thread to perform an operation asynchronously).
#
# This implementation subclasses the Thread class
# to create our own thread class.

import threading

class MultiplyThread(threading.Thread):

    def __init__(self, a, b):
        threading.Thread.__init__(self)
        self.a = a
        self.b = b
        self.result = None

    def run(self):
        self.result = self.a * self.b

mt = MultiplyThread(2,3)
mt.start()
mt.join()

print "The thread returned %i" % mt.result

