/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 *
 */

#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <mutex>
using namespace std;

vector<thread> rwthreads;
int value = 0;
mutex m;

void writer(int v)
{
	lock_guard<mutex> lock(m);
	cout << "Setting value to " << v << " (was " << value << ")" << endl;
	value = v;
	this_thread::sleep_for(chrono::milliseconds(2000));
}

void reader()
{
	lock_guard<mutex> lock(m);
	cout << "Reading value: " << value << endl;
	this_thread::sleep_for(chrono::milliseconds(500));
}


int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		cerr << "Usage: " << argv[0] << " FILENAME" << endl;
		exit(-1);
	}

	ifstream f(argv[1]);

	while(!f.eof())
	{
		string op;

		f >> op;
		if(op=="W")
		{
			int v;
			f >> v;
			rwthreads.push_back(thread(writer,v));
		}
		else if (op=="R")
		{
			rwthreads.push_back(thread(reader));
		}
	}

	for (auto i = rwthreads.begin(); i != rwthreads.end(); i++)
	   i->join();

	return 0;
}
