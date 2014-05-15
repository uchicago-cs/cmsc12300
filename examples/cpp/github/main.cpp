/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * Print the contents of a GitHub events file (as downloaded
 * from http://www.githubarchive.org/)
 *
 * It accepts the following command-line parameters:
 *
 *  -f FILE: Gzipped File with GitHub events in JSON.
 *
 *  -v: Verbose mode. Prints out more messages to the console.
 *
 */

#include "GitHubActivityReader.h"
#include "GitHubActivityFileReader.h"
#include "GitHubActivityEvent.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <getopt.h>
using namespace std;

const string USAGE = "-f FILE [-v]";

int main(int argc, char* argv[])
{
	// For parsing command-line options
	int opt;
	// Should we be verbose?
	bool verbose = false;
	// File with event data
	string file = "";
	fstream f;
	// Event reader
	GitHubActivityReader *reader;

	// Parse command-line options
	while ((opt = getopt(argc, argv, "f:wt:d:i:vh")) != -1)
		switch (opt)
		{
			case 'f':
				file = optarg;
				break;
			case 'v':
				verbose = true;
				break;
			default:
				cerr << "Usage: " << argv[0] << " " << USAGE << endl;
				cerr << "ERROR: Unknown option -" << char(opt) << endl;
				exit(-1);
		}

	if(file == "")
	{
		cerr << "Usage: " << argv[0] << " " << USAGE << endl;
		cerr << "ERROR: Must specify a file with -f." << endl;
		exit(-1);
	}

	// Create the reader
	f.open(file, ios_base::in | ios_base::binary);
	reader = new GitHubActivityFileReader(f);

	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

	int n=0;
	while(!reader->done())
	{
		GitHubActivityEvent *event;
		try
		{
			event = reader->next();
            cout << event->repr() << endl;
            delete event;
		} catch (GitHubActivityReaderException &e)
		{
			cerr << "Error reading event: " << e.what();
			continue;
		}

		n++;
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	if (verbose)
	{
		cout << endl << endl;
		cout << "Running time: " << elapsed << endl;
		cout << "Processed " << n << " events." << endl;
	}
	else
	{
		cout << file << "," << elapsed << "," << n << endl;
	}

}
