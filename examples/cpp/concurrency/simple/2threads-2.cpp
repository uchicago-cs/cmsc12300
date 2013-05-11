/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Same as 2threads.cpp, but using a single function
 * with parameters, as opposed to two functions.
 * Additionally, the thread function sleeps for
 * a number of milliseconds after printing the
 * string.
 *
 */

#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

void print_string(const char *s, int sleepms)
{
	while(1)
	{
		cout << s << endl;
		this_thread::sleep_for(chrono::milliseconds(sleepms));
	}
}

int main(int argc, char* argv[])
{
	thread t1(print_string, "0", 1);
	thread t2(print_string, "1", 2);

	t1.join();
	t2.join();

	return 0;
}
