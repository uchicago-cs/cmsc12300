import numpy
from numpy.linalg import inv

class LinearPredictorFunction(object):
    
    def __init__(self, X, Y):
        if Y.shape[0] != X.shape[0]:
            raise ValueError("Number of observations in Y and X doesn't match (%i !=) %i)" % (Y.shape[0], X.shape[0]) )

        self.X = X
        self.Y = numpy.reshape(Y, (Y.shape[0],1))

    def __prepend_ones_column(self, A):
        """
        Add a ones column to the left side of a numpy array
        """
        ones_col = numpy.ones((A.shape[0], 1))
        return numpy.hstack((ones_col, A))

    def get_num_observations(self):
        return self.X.shape[0]

    def get_num_covariates(self):
        return self.X.shape[1]

    def apply_model(self, B):
        X = self.__prepend_ones_column(self.X)

        return numpy.dot(X, B)

    def compute_R2(self, B):
        f = self.apply_model(B)
        y_mean = numpy.mean(self.Y)

        sstot = sum( (self.Y - y_mean)**2 )
        sserr = sum( (self.Y - f) **2 )        

        return 1.0 - (float(sserr) / float(sstot))

    def compute_linear_regression_model(self):
        X = self.__prepend_ones_column(self.X)
        Y = self.Y

        A = numpy.dot( X.T, X)
        b = numpy.dot( X.T, Y)

        Ai = inv(A)

        B = numpy.dot( Ai, b)

        return B


    def compute_linear_regression_model_sums(self):
        X = self.__prepend_ones_column(self.X)
        Y = self.Y

        p = self.get_num_covariates() + 1
        n = self.get_num_observations()

        A = numpy.zeros((p,p))
        for i in range(p):
            for j in range(p):
                for k in range(n):
                    A[i,j] += X[k,i] * X[k,j]  # X[k,i] instead of X[i,k] because we're using the transpose

        print
        b = numpy.zeros((p,1))
        for i in range(p):
            for j in range(1): # <-- Unnecesary, but included for clarity
                for k in range(n):
                    b[i,j] += X[k,i] * Y[k,j]  # X[k,i] instead of X[i,k] because we're using the transpose
            
        Ai = inv(A)
        B = numpy.dot( Ai, b)

        return B        



    
