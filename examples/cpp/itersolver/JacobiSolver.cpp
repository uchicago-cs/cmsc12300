/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Implementation of the JacobiSolver class.
 *
 */

#include<assert.h>
#include<cmath>
#include "JacobiSolver.h"

JacobiSolver::JacobiSolver(const LinearEquations &leq, int maxiter):
	Solver(leq, maxiter)
{
	// The Jacobi method only works on systems of linear
	// equations with the same number of equations as
	// variables (i.e., where the A matrix is square)
	assert(leq.numVar == leq.numEq);
}

JacobiSolver::~JacobiSolver() {

}

void JacobiSolver::chooseInitialValues()
{
	// Arbitrarily make the initial solution all zeroes
	for(int i=0; i<leq.numVar; i++)
		solution[i] = 0.0;
}

void JacobiSolver::doIteration()
{
	// This implementation of the Jacobi method
	// does not attempt to be particularly
	// efficient or clever. It doesn't use any
	// matrix libraries, it doesn't attempt
	// to exploit data locality, etc.
	// And yet, it blows the equivalent Python
	// implementations out of the water (except
	// the linalg one, with large systems)
	int n = leq.numVar;

	for(int i=0; i<n; i++)
		prevsolution[i] = solution[i];

	for(int i=0; i<n; i++)
	{
		double v = 0;
		for(int j=0; j<n; j++)
			if(i!=j)
				v += leq.A[i][j]*prevsolution[j];
		solution[i] = (leq.b[i] - v) / leq.A[i][i];
	}
}

bool JacobiSolver::hasConverged()
{
	// Simple convergence check: for every x_i, check
	// whether the solution and the previous solution
	// differ by more than 0.001. If they do, we
	// haven't converged.
	for(int i=0; i<leq.numVar; i++)
		if(fabs(prevsolution[i]-solution[i])>=0.001)
			return false;

	return true;
}
