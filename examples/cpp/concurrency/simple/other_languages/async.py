# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013
#
# Python implementation of async.cpp (spawn a single
# thread to perform an operation asynchronously).
#
# This implementation uses threading.Thread to invoke
# the function directly. This approach is simple,
# but has a few limitations (e.g., collecting the
# return value is not straightforward)
#
# See async-subclass.py for an example that uses
# a more common approach: defining a derived class 
# of threading.Thread

import threading

def multiply(a,b,retval):
    retval[0] = a*b

# When using threading.Thread to run a function, we cannot
# simply retrieve the return value. So, we pass a mutable
# object (a list) to act as a pseudo-by-reference parameter
# to contain the return value.

retval = [None]
t = threading.Thread(target=multiply, args=(2,3,retval))
t.start()
t.join()

print "The thread returned %i" % retval[0]
