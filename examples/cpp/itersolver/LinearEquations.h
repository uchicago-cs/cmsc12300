/*
 * LinearEquations.h
 *
 *  Created on: Apr 24, 2013
 *      Author: borja
 */

#ifndef LINEAREQUATIONS_H_
#define LINEAREQUATIONS_H_

#include<iostream>

class LinearEquations {

public:
	const float* const *A;
	const float *b;
	const int numEq;
	const int numVar;

	static LinearEquations fromText(std::istream &is);
	LinearEquations(const LinearEquations &leq);
	~LinearEquations();

	float* apply(float x[]) const;

	friend std::ostream& operator<<(std::ostream &os, const LinearEquations &leq);

private:
	LinearEquations(float **A, float *b, int numEq, int numVar);
};

#endif /* LINEAREQUATIONS_H_ */
