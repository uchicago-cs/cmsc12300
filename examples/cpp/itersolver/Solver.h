/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * A base class for solvers of systems of linear equations
 * that use an iterative method.
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "LinearEquations.h"

class Solver {
	// The maximum number of iterations
	int maxiter;
	// The actual number of iterations
	int iterations;

protected:
	// The system of linear equations
	const LinearEquations &leq;
	// The previous solution and the current solution
	double *prevsolution, *solution;
	// The computed values of b (applying the solution
	// to leq
	double *b;

	// Chooses an initial value for the solution, and places
	// it in the solution attribute.
	// Abstract method. Must be implemented by the subclass.
	virtual void chooseInitialValues() = 0;

	// Does a single iteration of the iterative method.
	// Abstract method. Must be implemented by the subclass.
	virtual void doIteration() = 0;

	// Determines whether the algorithm has converged.
	// Abstract method. Must be implemented by the subclass.
	virtual bool hasConverged() = 0;

public:
	// Constructor.
	//
	// Parameters:
	// - leq: A system of linear equations
	// - maxiter: The maximum number of iterations
	Solver(const LinearEquations &leq, int maxiter = 10000);

	// Destructor
	virtual ~Solver();

	// Solves the system of linear equations.
	// Returns 0 if successful, and 1 otherwise.
	int solve();

	// Gets x_i in the current solution
	double getSolvedX(int i);

	// Gets b_i (resulting from applying the solution to
	// the system of linear equations)
	double getSolvedB(int j);

	// Gets the number of iterations that the iterative
	// method used.
	int getNumIterations();
};

#endif /* SOLVER_H_ */
