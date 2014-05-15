/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Example of an unchecked race condition. Two threads
 * modify the same variable (a counter). One thread
 * increments the counter 10,000,000 times, and
 * the other thread decrements it 10,000,000 times.
 * If the code were run sequentially, a counter
 * starting at zero would eventually return to
 * zero.
 *
 */

#include <thread>
#include <iostream>
#include <vector>
using namespace std;

const unsigned int NTHREADS = 20;
const int ITERS = 10000000;

int counter;

void increment()
{
	for(int i=0; i<ITERS; i++)
		counter++;
}

void decrement()
{
	for(int i=0; i<ITERS; i++)
		counter--;
}

int main(int argc, char* argv[])
{
    vector<thread> vt;

	cout << "The counter is " << counter << endl;

	for(unsigned int i=0; i<NTHREADS; i++)
		if(i%2==0)
            vt.push_back(thread(increment));
		else
            vt.push_back(thread(decrement));

    for(thread &t : vt)
		t.join();

	cout << "The counter is " << counter << endl;

	return 0;
}
