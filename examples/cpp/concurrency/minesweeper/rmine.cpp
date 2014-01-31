/*
 * rmine.cpp
 *
 *  Created on: May 3, 2013
 *      Author: borja
 */

#include <thread>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;

#include "Minefield.h"

const string USAGE = "-f FILE [-t THREADS] [-r RADIUS] [-s (mines|empty)] [-i ITERS] [-v]";

void solverThread(Minefield *mf, int x_min, int x_max, int y_min, int y_max, int radius, StrategyType strategy)
{
	mf->solve_range(x_min, x_max, y_min, y_max, radius, strategy);
}


int main(int argc, char* argv[])
{
	// For parsing command-line options
	int opt;
	// Minefield file
	char *fname = NULL;
	// Should we be verbose?
	bool verbose = false;
	// Number of threads
	int nthreads = 1;
	// Radius
	int radius = 1;
	// Iterations
	int iterations = 1;
	// Solving strategy
	char *strategyname = NULL;
	StrategyType strategy;

	// Parse command-line options
	while ((opt = getopt(argc, argv, "f:t:s:r:i:vh")) != -1)
		switch (opt)
		{
			case 'f':
				fname = optarg;
				break;
			case 't':
				nthreads = atoi(optarg);
				break;
			case 'r':
				radius = atoi(optarg);
				break;
			case 'i':
				iterations = atoi(optarg);
				break;
			case 's':
				strategyname = strdup(optarg);
				break;
			case 'v':
				verbose = true;
				break;
			default:
				cerr << "Usage: " << argv[0] << " " << USAGE << endl;
				cerr << "ERROR: Unknown option -" << char(opt) << endl;
				exit(-1);
		}

	if(!fname)
	{
		cerr << "Usage: " << argv[0] << " " << USAGE << endl;
		cerr << "ERROR: Must specify a file with -f" << endl;
		exit(-1);
	}

	if(!strategyname)
		strategyname = strdup("mines");

	if(!strcmp(strategyname,"mines"))
		strategy = ADD_AROUND_MINES;
	else if(!strcmp(strategyname,"empty"))
		strategy = COUNT_MINES_AROUND_EMPTIES;
	else
	{
		cerr << "Usage: " << argv[0] << " " << USAGE << endl;
		cerr << "ERROR: Unknown strategy '" << optarg << "'" << endl;
		exit(-1);
	}

	struct timespec start, finish, cpustart, cpufinish;
	double elapsed, cpuelapsed;

	ifstream f(fname);

	Minefield mf;

	f >> mf;
	f.close();

	if(verbose)
	{
		cout << "Solving " << mf.getNumRows() << "x" << mf.getNumCols() << " minefield." << endl;
		cout << "Using r=" << radius << " and " << nthreads << " threads." << endl;

		if (mf.getNumRows() < 100 && mf.getNumCols() < 100)
			cout << endl << mf;
	}

	for(int i=0; i<iterations; i++)
	{
		thread *threads = new thread[nthreads];

		clock_gettime(CLOCK_MONOTONIC, &start);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpustart);

		int chunksize = mf.getNumRows() / nthreads;
		for (int i = 0; i < nthreads; i++)
		{
			int x_min = i * chunksize;
			int x_max = (i+1) * chunksize;
			if(i==nthreads - 1)
				x_max += mf.getNumRows() % nthreads;
			int y_min = 0;
			int y_max = mf.getNumCols();

			if(verbose)
				cout << "Spawning thread to process (" << x_min << ", " << y_min << ") -> (" << x_max << ", " << y_max << ")" << endl;

			threads[i] = thread(solverThread, &mf, x_min, x_max, y_min, y_max, radius, strategy);
		}

		//Join threads
		for (int i = 0; i < nthreads; i++)
			threads[i].join();

		delete[] threads;

		clock_gettime(CLOCK_MONOTONIC, &finish);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpufinish);

		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

		cpuelapsed = (cpufinish.tv_sec - cpustart.tv_sec);
		cpuelapsed += (cpufinish.tv_nsec - cpustart.tv_nsec) / 1000000000.0;

		if(verbose)
		{
			if (mf.getNumRows() < 100 && mf.getNumCols() < 100)
			{
				cout << endl << mf;
			}
			cout << endl << "Solved minefield in " << elapsed << "s (CPU: " << cpuelapsed << "s)" << endl;
		}
		else
			cout << fname << "," << nthreads << "," << strategyname << "," << radius << "," << elapsed << "," << cpuelapsed << endl;

		mf.reset();
	}

    return 0;
}

