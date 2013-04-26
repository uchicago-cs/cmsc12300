/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Implementation of the LinearEquations class.
 *
 * See LinearEquations.h for more details on what each function does
 *
 */

#include "LinearEquations.h"
#include<iostream>
using namespace std;

LinearEquations LinearEquations::fromText(std::istream &is) {
	int numEq, numVar;
	double **A, *b;

	is >> numEq >> numVar;

	A = new double*[numEq];
	for(int i = 0; i<numEq; i++) {
	    A[i] = new double[numVar];
	}
	b = new double[numEq];

	for(int i=0; i<numEq; i++)
	{
		for(int j=0; j<numVar; j++)
			is >> A[i][j];
		is >> b[i];
	}

	return LinearEquations(A,b, numEq, numVar);
}

LinearEquations::LinearEquations(const LinearEquations &leq):
		A(leq.A), b(leq.b), numEq(leq.numEq), numVar(leq.numVar)
{

}

LinearEquations::~LinearEquations() {
	for(int i = 0; i<numEq; i++) {
	    delete[] A[i];
	}
	delete[] A;
	delete[] b;
}

LinearEquations::LinearEquations(double **A, double *b, int numEq, int numVar):
		A(A), b(b), numEq(numEq), numVar(numVar)
{
	// Empty
}

double* LinearEquations::apply(double x[]) const
{
	double *b = new double[numEq];

	for(int i=0; i<numEq; i++)
		for(int j=0; j<numVar; j++)
			b[i] += (x[j] * A[i][j]);

	return b;
}

std::ostream& operator<<(std::ostream &os, const LinearEquations &leq)
{
	for(int i=0; i<leq.numEq; i++)
	{
		for(int j=0; j<leq.numVar; j++)
		{
			os << (j==0?"":" + ") << leq.A[i][j] << "*x_" << j;
		}
		os << " = " << leq.b[i] << endl;
	}
	return os;
}
