# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

"""This module provides functions to find the maximum value
in a text file containing one integer per line.
"""

def find_max_in_file(fname):
    """Finds the maximum value in a file by doing
    a linear search.

    Parameters:
    - fname: The name of the file
    """
    n_max = 0

    f = open(fname)
    for n in f:
        if int(n) > n_max:
            n_max = int(n)
    f.close()


def find_file_ranges(fname, chunks):
    """Given a text file with one integer per line,
    this function finds the boundaries of the file
    that divide it into a given number of chunks (taking 
    into account that we don't want to divide the 
    file mid-number; it has to be divided after a newline)

    Parameters:
    - fname: The name of the file
    - chunks: Number of chunks
    """
    f = open(fname)

    f.seek(0,2)
    fsize = f.tell()

    ranges = []
    chunk_size = fsize / chunks
    start = 0
    for i in range(chunks):
        f.seek(start + chunk_size)
        l = f.readline()
        end = min(start + chunk_size + len(l) - 1, fsize)
        ranges.append( (start, end) )
        start = end + 1

    f.close()
    return ranges

def find_max_in_range(fname, frange):
    """Given a range of bytes in the file, and assuming
    that the range includes complete lines (as returned
    by find_file_ranges), return the maximum number
    in that range.

    Parameters:
    - fname: The name of the file
    - frange: Tuple with the start and end of the range
    """
    
    f = open(fname)
    n_max = 0

    f.seek(frange[0])

    for n in f:
        if int(n) > n_max:
            n_max = int(n)
        if f.tell() >= frange[1]:
            break

    f.close()

    return n_max


