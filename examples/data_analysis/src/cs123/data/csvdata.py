import numpy

class CSV(object):

    def __init__(self, fname):
        f = open(fname)
        self.colnames = f.readline().strip().split(",")
        f.close()

        self.data = numpy.genfromtxt(fname, dtype=float, delimiter=',', skip_header=True)

    def get_columns(self, cols, purgeNaNs=False):
        col_indexes = [self.colnames.index(c) for c in cols]

        data = self.data[:,col_indexes]

        if purgeNaNs:
            data = data[~numpy.isnan(data).any(axis=1)]

        return data

    def get_column_names(self):
        return self.colnames

    def get_num_entries(self):
        return self.data.shape[0]


        
