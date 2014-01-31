/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 *
 */

#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <condition_variable>
using namespace std;

const unsigned int BUFFER_SIZE = 100;
int buf[BUFFER_SIZE];

#ifndef DISABLE_LOCKS
mutex m;
condition_variable not_empty;
condition_variable not_full;
#endif

unsigned int in = 0, out = 0, n = 0, v = 0;

void producer()
{
	while(true)
	{

#ifndef DISABLE_LOCKS
		unique_lock<mutex> lock(m);
		while(n==BUFFER_SIZE)
			not_full.wait(lock);
#endif

		buf[in] = v;
		n++;
		in = (in + 1) % BUFFER_SIZE;
		cout << "Wrote " << v << " (n=" << n << ")" << endl;
		v++;

#ifndef DISABLE_LOCKS
		lock.unlock();
		not_empty.notify_all();
#endif
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void consumer()
{
	int data;

	while(true)
	{

#ifndef DISABLE_LOCKS
		unique_lock<mutex> lock(m);
		while(n==0)
			not_empty.wait(lock);
#endif

		data = buf[out];
		n--;
		out = (out + 1) % BUFFER_SIZE;
		cout << "Read " << data << " (n=" << n << ")" << endl;

#ifndef DISABLE_LOCKS
		lock.unlock();
		not_full.notify_all();
#endif
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

int main(int argc, char* argv[])
{
	thread pt = thread(producer);
	thread ct = thread(consumer);

	pt.join();
	ct.join();

	return 0;
}
