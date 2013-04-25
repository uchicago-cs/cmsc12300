/*
 * Solver.h
 *
 *  Created on: Apr 24, 2013
 *      Author: borja
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "LinearEquations.h"

class Solver {
	int maxiter;
	int iterations;

protected:
	const LinearEquations &leq;
	float *solution;
	float *b;
	virtual bool hasConverged() = 0;
	virtual void doIteration() = 0;

public:
	Solver(const LinearEquations &leq, int maxiter = 100);
	virtual ~Solver();

	int solve();
	float getSolvedX(int i);
	float getSolvedB(int j);
};

#endif /* SOLVER_H_ */
