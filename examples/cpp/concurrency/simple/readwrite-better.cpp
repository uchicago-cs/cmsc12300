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
#include <atomic>
#include <mutex>
using namespace std;

vector<thread> rwthreads;
int value = 0;
int nreaders = 0;
mutex mreaders;
mutex mvalue;
mutex console;

void writer(int v)
{
	lock_guard<mutex> lock(mvalue);
	this_thread::sleep_for(chrono::milliseconds(1000));
	value = v;
	{
		lock_guard<mutex> consolelock(console);
		cout << "Set value to " << v << " (was " << value << ")" << endl;
	}
}

void reader()
{
	{
		lock_guard<mutex> rlock(mreaders);
		nreaders++;
		if(nreaders==1)
			mvalue.lock();
	}

	this_thread::sleep_for(chrono::milliseconds(500));
	{
		lock_guard<mutex> consolelock(console);
		cout << "Read value: " << value << endl;
	}

	{
		lock_guard<mutex> rlock(mreaders);
		nreaders--;
		if(nreaders==0)
			mvalue.unlock();
	}
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
		this_thread::sleep_for(chrono::milliseconds(250));
	}

	for (auto i = rwthreads.begin(); i != rwthreads.end(); i++)
	   i->join();

	return 0;
}
