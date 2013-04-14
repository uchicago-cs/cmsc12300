import pylab
from matplotlib.colors import ListedColormap

def get_colors(k):
    cm = pylab.get_cmap('gist_rainbow')
    colors = []
    for i in range(k):
        colors.append(cm(1.*i/k))
    return colors

def gen_scatter_plot(points, ks, centroids, fname = None):
    pylab.close()
    lcm = ListedColormap(get_colors(len(centroids)))
    pylab.scatter(points[:,0], points[:,1], c=ks, cmap=lcm)

    pylab.scatter(centroids[:,0], centroids[:,1], marker='o', s = 200, linewidths=2, c='none')
    pylab.scatter(centroids[:,0], centroids[:,1], marker='x', s = 200, linewidths=2)

    if fname is None:
        pylab.show()
    else:
        pylab.savefig(fname)
