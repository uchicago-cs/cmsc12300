/*
 * JacobiSolver.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: borja
 */

#include "JacobiSolver.h"

JacobiSolver::JacobiSolver(const LinearEquations &leq, int maxiter):
	Solver(leq, maxiter)
{
	// TODO Auto-generated constructor stub
}

JacobiSolver::~JacobiSolver() {
	// TODO Auto-generated destructor stub
}

bool JacobiSolver::hasConverged()
{
	return true;
}

void JacobiSolver::doIteration()
{

}
