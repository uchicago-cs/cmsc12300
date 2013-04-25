/*
 * main.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: borja
 */

#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

#include "LinearEquations.h"
#include "JacobiSolver.h"

int main(int arg, char** argv)
{
	ifstream ifs;

	ifs.open("leq.txt");

	LinearEquations leq = LinearEquations::fromText(ifs);
	JacobiSolver jacobi(leq);

	cout << "Solving the following system: " << endl << endl;
	cout << leq;

	cout << endl;

	cout << "Solution:" << endl << endl;
	if (jacobi.solve() == 0)
	{
		for(int i=0; i<leq.numVar; i++)
			cout << "x_" << i << " = " << jacobi.getSolvedX(i) << endl;
		cout << endl;
		for(int j=0; j<leq.numEq; j++)
		{
			cout << "b_" << j << " = " << jacobi.getSolvedB(j);
			cout << " (" << leq.b[j] << ")" << endl;
		}
	}
	else
		cout << "Solver did not converge" << endl;

	ifs.close();
}
