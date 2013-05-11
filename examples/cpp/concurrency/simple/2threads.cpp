/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Simple thread example: one thread prints 0's the
 * other prints 1's
 *
 */

#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

void print_zero()
{
	while(1)
		cout << "0" << endl;
}

void print_one()
{
	while(1)
		cout << "1" << endl;

}

int main(int argc, char* argv[])
{
	thread t1(print_zero);
	thread t2(print_one);

	t1.join();
	t2.join();

	return 0;
}
