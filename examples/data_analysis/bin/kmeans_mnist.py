# CMSC 12300 - Computer Science with Applications 3
# Borja Sotomayor, 2013

from common.kmeans import KMeans
from common.utils import read_cluster_points, gen_scatter_plot, distance
from common.mnist import MNISTReader
import sys
import random
import numpy
from PIL import Image

CUTOFF = 100.0

if len(sys.argv) == 4:
    k = int(sys.argv[1])
    data_dir = sys.argv[2]
    resfile = sys.argv[3]
else:
    print "Usage %s K DATADIR OUTFILE" % (sys.argv[0])
    exit(1)

print "Loading data..."
test = MNISTReader("%s/t10k-images-idx3-ubyte" % data_dir, "%s/t10k-labels-idx1-ubyte" % data_dir)

points = None
for img in test.images():
    if points is None:
        points = numpy.array([img.imgdata])
    else:
        points = numpy.append(points, [img.imgdata], axis=0)

km = KMeans(points, k)

centroids = km.select_random_centroids()

iteration=1
while True:
    print "Iteration #%i" % iteration

    new_centroids, point_assignment = km.get_k_means(centroids)

    distances = [distance(c1,c2) for c1,c2 in zip(centroids,new_centroids)]
    max_d = max(distances)

    if max_d <= CUTOFF:
        print "Max shift: %.2f <= %.2f" % (max_d, CUTOFF)
        print "Algorithm has converged."
        break
    else:
        print "Max shift: %.2f > %.2f" % (max_d, CUTOFF)
        print "Algorithm hasn't converged yet."
        centroids = new_centroids
        iteration += 1

imgarray = numpy.reshape(255 - new_centroids[0], (28, 28))
for centroid in new_centroids:
    imgc = numpy.reshape(255 - centroid, (28, 28))
    imgarray = numpy.hstack( (imgarray, imgc) )

i = Image.fromarray(imgarray.astype(numpy.uint8))
i.show()
i.save(resfile)



