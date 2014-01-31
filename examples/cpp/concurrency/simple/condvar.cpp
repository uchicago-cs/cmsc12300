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

mutex m;
condition_variable cv_setup_done;
bool setup_done;

void worker_thread()
{
	cout << "WORKER: Starting setup..." << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "WORKER: Setup done. Notifying main thread." << endl;


	m.lock();
	setup_done = true;
	cv_setup_done.notify_one();
	cout << "WORKER: Notified main thread." << endl;
	m.unlock();
}



int main(int argc, char* argv[])
{
	setup_done = false;

	unique_lock<mutex> lock(m);

	cout << "MAIN: Launching worker thread" << endl;
	thread wt = thread(worker_thread);

	while(!setup_done)
		cv_setup_done.wait(lock);
	cout << "MAIN: Setup done." << endl;

	wt.join();

	return 0;
}
