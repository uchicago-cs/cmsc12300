/*
 * JacobiSolver.h
 *
 *  Created on: Apr 24, 2013
 *      Author: borja
 */

#ifndef JACOBISOLVER_H_
#define JACOBISOLVER_H_

#include "Solver.h"

class JacobiSolver: public Solver {

private:
	bool hasConverged();
	void doIteration();

public:
	JacobiSolver(const LinearEquations &leq, int maxiter = 100);
	virtual ~JacobiSolver();
};

#endif /* JACOBISOLVER_H_ */
