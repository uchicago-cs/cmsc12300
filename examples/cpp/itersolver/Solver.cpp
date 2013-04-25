/*
 * Solver.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: borja
 */

#include "Solver.h"

Solver::Solver(const LinearEquations &leq, int maxiter): leq(leq), maxiter(maxiter)
{
	solution = new float[leq.numVar];
}

Solver::~Solver() {
	delete[] solution;
}

int Solver::solve(void)
{
	iterations = 0;
	do
	{
		doIteration();
		iterations++;
	} while (!hasConverged() && iterations < maxiter);


	if(iterations >= maxiter)
		return 1;
	else
	{
		b = leq.apply(solution);
		return 0;
	}
}

float Solver::getSolvedX(int i)
{
	return solution[i];
}

float Solver::getSolvedB(int j)
{
	return b[j];
}
