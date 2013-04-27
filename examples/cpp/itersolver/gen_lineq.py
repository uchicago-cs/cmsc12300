#!/usr/bin/python

# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""
Simple command to generate a system of N linear
equations (with N variables) for use with the
examples in this directory.

Takes in two parameters:

    gen_lineq.py N [SEED]

N: The number of equations/variables
SEED: An optional seed for the random number generator.
"""

import sys
import random

N = int(sys.argv[1])
if len(sys.argv) == 3:
    seed = int(sys.argv[2])
    random.seed(seed)

print N, N

for i in range(N):  
    rands = [random.randint(1,5) for x in range(N-1)]
    diag = sum(rands) + random.randint(1,100)
    ns = rands[0:i] + [diag] + rands[i:]
    b = random.randint(N**3,N**4)

    print " ".join([`x` for x in ns]), b

