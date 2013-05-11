/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Subclass of the Solver class that implements the
 * Jacobi method.
 *
 * Does not add any additional methods; simply provides
 * an implementation of all the abstract methods.
 *
 */

#ifndef JACOBISOLVER_H_
#define JACOBISOLVER_H_

#include "Solver.h"

class JacobiSolver: public Solver {

private:
	void chooseInitialValues();
	void doIteration();
	bool hasConverged();

public:
	JacobiSolver(const LinearEquations &leq, int maxiter = 10000);
	virtual ~JacobiSolver();
};

#endif /* JACOBISOLVER_H_ */
