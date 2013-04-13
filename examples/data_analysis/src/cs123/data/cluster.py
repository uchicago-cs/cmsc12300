import math
import random
import sys


class ClusteredData2D(object):
    """A class to generate and read 2-dimensional clustered data.

    Cluster files are text files where each line contains the 
    following:
    
         X Y K
    
    (X,Y) being the coordinate of the point, and K the cluster
    that point belongs to.
    """

    CLUSTER_DIST = 100
    JITTER = 5

    def __init__(self, seed = None):
        self.seed = seed

    # Maps the centroid number to a 2-dimensional point
    def __one2two(self, x):
        """Maps a 1-dimensional centroid index to a 2-dimensional point
        According to this scheme:

             .      .
             .     .
             .    .
             6 7 8
             2 3 5
             0 1 4...

        """

        if x==0: return (0,0)
        r = int(math.floor(math.sqrt(x)))
        d = x/r
        m = x%r
        if d == r:
            return (r,m)
        elif d == r+1:
            return (m,r)
        elif d == r+2:
            return (r,r)

    def __generate_centers(self, k):
        """ Generate the centers of the clusters."""

        centers = []
        for i in range(k):
            x, y = self.__one2two(i)
            x = 100 + self.CLUSTER_DIST * x + random.randint(-self.JITTER, self.JITTER)
            y = 100 + self.CLUSTER_DIST * y + random.randint(-self.JITTER, self.JITTER)
            centers.append( (x,y) )
        return centers


    def generate(self, k, n, d):
        """
        Generates random clustered data. For
        simplicity, the center of the clusters are located 
        100 points aparts, with a bit of jitter added. 
        The clusters are laid out like this:
        
             .      .
             .     .
             .    .
             6 7 8
             2 3 5
             0 1 4...
        
        Where 0 is at (100,100), 1 is at (200,0), 2 is at (0,200),
        3 is at (200,300), 4 is at (300,0), etc.
    
        Parameters:
        - k: The number of clusters
        - n: The total number of datapoints to generate (the data
        points are distributed equally amongst all the clusters)
        - d: The maximum distance (in any direction) between
        the center of the cluster and its points. 
        """

        per_cluster = n/k

        centers = self.__generate_centers(k)

        for i in range(k):
            cx, cy = centers[i]

            for j in range(per_cluster):
                x = cx + random.randint(-d, d)
                y = cy + random.randint(-d, d)

                yield (x,y,i)

    def read(self, fname):
        f = open(fname)
        for line in f:
            vals = line.strip().split()
            if len(vals) == 2:
                yield int(vals[0]), int(vals[1]), None
            elif len(vals) == 3:
                yield int(vals[0]), int(vals[1]), int(vals[2])
        f.close()
