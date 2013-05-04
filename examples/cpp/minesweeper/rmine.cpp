/*
 * rmine.cpp
 *
 *  Created on: May 3, 2013
 *      Author: borja
 */

#include <thread>
#include <iostream>
#include <fstream>
using namespace std;

#include "Minefield.h"

void hello(){
    cout << "Hello from thread " << endl;
}

int main(int argc, char* argv[])
{
    //thread t1(hello);
    //t1.join();

	ifstream f("minefield.xlarge.txt");
	Minefield mf;

	f >> mf;
	cout << "Loaded" << endl;
	//cout << mf << endl;

	mf.solve();
	//cout << mf;
	cout << "Done" << endl;

	f.close();
    return 0;
}

