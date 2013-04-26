/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Implementation of the Solver class.
 *
 * See Solver.h for details on what each method does.
 */

#include "Solver.h"

Solver::Solver(const LinearEquations &leq, int maxiter): leq(leq), maxiter(maxiter)
{
	prevsolution = new double[leq.numVar];
	solution = new double[leq.numVar];
}

Solver::~Solver() {
	delete[] prevsolution;
	delete[] solution;
}

int Solver::solve(void)
{
	// Basic structure of an iterative method
	// The actual work is done by the implementations of
	// chooseInitialValue(), doIteration(), and hasConverged()
	// in the derived classes.
	iterations = 0;
	chooseInitialValues();
	do
	{
		doIteration();
		iterations++;
	} while (!hasConverged() && iterations < maxiter);


	if(iterations >= maxiter)
		return 1;
	else
	{
		// If we were able to find a solution,
		// we compute the values of b resulting
		// from that solution.
		b = leq.apply(solution);
		return 0;
	}
}

double Solver::getSolvedX(int i)
{
	return solution[i];
}

double Solver::getSolvedB(int j)
{
	return b[j];
}

int Solver::getNumIterations()
{
	return iterations;
}
