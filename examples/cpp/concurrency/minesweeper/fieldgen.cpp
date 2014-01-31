/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Minefield generator.
 *
 */

#include <thread>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <random>
#include <time.h>
#include <string.h>
using namespace std;

#include "Minefield.h"

const string USAGE = "-x ROWS -y COLS -p PCT_MINES [-s SEED] [-f FILE]";

int main(int argc, char* argv[])
{
	// For parsing command-line options
	int opt;
	// Minefield file
	char *fname = NULL;
	ostream *os = &cout; // Use stdout by default
	// Number of rows and columns
	int x = 0, y = 0;
	// Percent of mines
	int pctmines = -1;
	// Seed
	random_device rd;
	int seed = rd();

	// Parse command-line options
	while ((opt = getopt(argc, argv, "x:y:p:s:f:h")) != -1)
		switch (opt)
		{
		case 'x':
			x = atoi(optarg);
			break;
		case 'y':
			y = atoi(optarg);
			break;
		case 'p':
			pctmines = atoi(optarg);
			break;
		case 's':
			seed = atoi(optarg);
			break;
		case 'f':
			fname = strdup(optarg);
			break;
		default:
			cerr << "Usage: " << argv[0] << " " << USAGE << endl;
			cerr << "ERROR: Unknown option -" << char(opt) << endl;
			exit(-1);
		}

	if(fname)
	{
		os = new ofstream(fname);
	}

	if(x==0 || y==0)
	{
		cerr << "Usage: " << argv[0] << " " << USAGE << endl;
		cerr << "ERROR: Must specify minefield size with -x and -y" << endl;
		exit(-1);
	}

	if(pctmines < 0 || pctmines > 100)
	{
		cerr << "Usage: " << argv[0] << " " << USAGE << endl;
		cerr << "ERROR: Must specify a mines percentage between 0 and 100" << endl;
		exit(-1);
	}

	Minefield mf(x,y,pctmines/100.0,seed);

	*os << x << " " << y << endl;
	*os << mf;

    return 0;
}

