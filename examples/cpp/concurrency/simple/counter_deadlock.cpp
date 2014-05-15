/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * Same as counter.cpp, but with multiple mutexes
 * (using the lock() function to avoid deadlocks)
 */

#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
using namespace std;

const unsigned int NTHREADS = 20;
const int ITERS = 100000;

mutex m1, m2, m3, m4, m5;
int counter = 0;

void increment(int n)
{
	for(int i=0; i<ITERS; i++)
    {
        lock(m1,m2,m3,m4,m5);
        lock_guard<mutex> l1(m1, std::adopt_lock);
        lock_guard<mutex> l2(m2, std::adopt_lock);
        lock_guard<mutex> l3(m3, std::adopt_lock);
        lock_guard<mutex> l4(m4, std::adopt_lock);
        lock_guard<mutex> l5(m5, std::adopt_lock);

        counter++;
    }
}

void decrement(int n)
{
	for(int i=0; i<ITERS; i++)
    {
        lock(m1,m2,m3,m4,m5);
        lock_guard<mutex> l1(m1, std::adopt_lock);
        lock_guard<mutex> l2(m2, std::adopt_lock);
        lock_guard<mutex> l3(m3, std::adopt_lock);
        lock_guard<mutex> l4(m4, std::adopt_lock);
        lock_guard<mutex> l5(m5, std::adopt_lock);

        counter--;
    }
}


int main(int argc, char* argv[])
{
    vector<thread> vt;

	cout << "The counter is " << counter << endl;

	for(unsigned int i=0; i<NTHREADS; i++)
		if(i%2==0)
            vt.push_back(thread(increment, i));
		else
            vt.push_back(thread(decrement, i));

    for(thread &t : vt)
		t.join();

	cout << "The counter is " << counter << endl;

	return 0;
}
