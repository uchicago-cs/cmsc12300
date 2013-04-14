import math
import random
import numbers
import sys
import numpy

class DimensionMismatchError(Exception):
    """Exception class thrown whenever the wrong number of
    dimensions is used with an N-dimensional dataset"""

    def __init__(self, expected_dim, got_dim):
        message = "Dimension mismatch. Expected %i, got %i" % (expected_dim, got_dim)

        Exception.__init__(self, message)

        self.expected_dim = expected_dim
        self.got_dim = got_dim


class ClusteredData(object):
    """A class representing N-dimensional data where each
    point may be associated with a cluster.

    You can create ClusteredData objects to create your
    own data:

        data = ClusteredData(dim = 3)
        data.add_point([2,3,4], k=2)
        data.to_file("data.txt")        
        
    You can also read data from a file:

        data = ClusteredData.from_file("data.txt")
        for point, k in data:
            print point

    You can also use a ClusterDataGenerator object:

        data = ClusteredData.from_generator(
            Clustered2DDataGenerator(5, 500, 50)
            )

        for point, k in data:
            print point    

    """

    def __init__(self, dim, generator_func=None):
        self.dim = dim
        self.f = generator_func
        self.data = []
        self.data_iter = None

    def __iter__(self):
        if self.f is None:
            return iter(self.data)
        else:
            return self.f

    def add_point(self, p, k=None):
        if self.f is not None:
            raise RuntimeError("Cannot add points to a data generator object.")
        if not all(isinstance(n, numbers.Number) for n in p):
            raise TypeError("Point contains non-numeric values")
        if k is not None and not isinstance(k, numbers.Number):
            raise TypeError("k is not a number")
        if k is not None and k < 0:
            raise ValueError("k must be a positive integer")            
        if len(p) != self.dim:
            raise DimensionMismatchError(expected_dim = self.dim, got_dim = len(p))
            
        self.data.append((p,k))

    @classmethod
    def from_file(cls, fname):
        def generator_func(dim, fname):
            f = open(fname)
            f.readline() # Skip dimensions
            for l in f:
                l2 = l.split()
                p = [float(x) for x in l2[0:dim]]
                if len(l2) == dim:
                    yield p, None
                elif len(l2) == dim + 1:
                    yield p, int(l2[-1])
                else:
                    raise DimensionMismatchError(expected_dim = self.dim, got_dim = len(l2))
            f.close()

        f = open(fname)
        dim = int(f.readline())
        f.close()

        return cls(dim = dim, generator_func = generator_func(dim, fname))

    @classmethod
    def from_generator(cls, generator_obj):
        return cls(dim = generator_obj.get_dimensions(),
                   generator_func = generator_obj.get_generator())

    def to_array(self):
        return numpy.array([p for p,k in self])

    def to_file(self, fname):
        pass


class ClusteredDataGenerator(object):
    """Base class for clustered data generators.

    The get_generator() method must return a generator
    function that will produce the data, and the
    get_dimensions() method must return the number of
    dimensions in the data."""

    def __init__(self):
        pass

    def get_generator(self):
        raise NotImplementedError()

    def get_dimensions(self):
        raise NotImplementedError()

class Clustered2DDataGenerator(ClusteredDataGenerator):
    """Generates random clustered two-dimensional data. For
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
    """

    CLUSTER_DIST = 100
    JITTER = 5

    def __init__(self, k, n, d, seed = None):
        """Creates a cluster data generator.

        Parameters:
        - k: The number of clusters
        - n: The total number of datapoints to generate (the data
        points are distributed equally amongst all the clusters)
        - d: The maximum distance (in any direction) between
        the center of the cluster and its points. 
        - seed: An optional seed to pass to the cluster data generator
        """
        ClusteredDataGenerator.__init__(self)
        self.k = k
        self.n = n
        self.d = d
        self.seed = seed

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

    def get_dimensions(self):
        return 2

    def get_generator(self):
        """Creates a ClusteredData object that generates random points
        clustered around K clusters.

        """
        def generator_func(k,n,d,seed,centers):
            random.seed(seed)
            per_cluster = n/k

            for i in range(k):
                cx, cy = centers[i]

                for j in range(per_cluster):
                    x = cx + random.randint(-d, d)
                    y = cy + random.randint(-d, d)

                    yield (x,y), i

        centers = self.__generate_centers(self.k)
        return generator_func(self.k, self.n, self.d, self.seed, centers)



