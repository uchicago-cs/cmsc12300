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
#include <condition_variable>
using namespace std;

vector<thread> rwthreads;
int value = 0;
int nreaders = 0;
int nwriters = 0;
condition_variable no_readers, no_writers;
mutex m;
mutex console;

void writer(int v)
{
	unique_lock<mutex> lock(m);
	nwriters++;
	while(nreaders > 0)
		no_readers.wait(lock);
	this_thread::sleep_for(chrono::milliseconds(1000));
	{
		lock_guard<mutex> consolelock(console);
		cout << "Set value to " << v << " (was " << value << ")" << endl;
	}
	value = v;
	nwriters--;
	if(nwriters==0)
		no_writers.notify_all();
}

void reader()
{
	unique_lock<mutex> lock(m);
	while(nwriters > 0)
		no_writers.wait(lock);
	nreaders++;
	lock.unlock();

	this_thread::sleep_for(chrono::milliseconds(500));

	{
		lock_guard<mutex> consolelock(console);
		cout << "Read value: " << value << endl;
	}

	lock.lock();
	nreaders--;
	if(nreaders==0)
		no_readers.notify_all();
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
