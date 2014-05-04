#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


int main(int argc, char **argv)
{
    /* Input/output in C++ is organized around "streams", abstract data types
       representing devices where one can read/write data. For example,
       there is a stream for standard output, a stream for standard input,
       you can create a stream to read from a file, and even a stream to
       write to a string.

       To use these streams, we must use the "iostream" library. */

    /* For now, we will just use the predefined "cout" stream, which represents
       standard output */

    /* To write something to a stream, we use the "<<" operator */
    cout << "Hello, world!\n";

    /* We can use the "<<" multiple times to concatenate multiple strings */
    cout << "Hello, " << "world!\n";

    /* And, instead of using the '\n' character, we can use the predefined "endl" */
    cout << "Hello, world!" << endl;


    /* One of the great features of iostream library is that the predefined streams
       support all the C++ primitive types */
    cout << 42 << endl;
    cout << 3.1415 << endl;

    /* Not just that, we can use the "<<" operator multiple times with heterogeneous
       data types */
    int x = 42;
    cout << "The answer is " << x << endl;

    /* We can also use "I/O manipulators" to affect the formatting */
    cout << setw(10) << "ID:" << setw(10) << 42 << endl;
    cout << setw(10) << "Price:" << setw(10) << 100.37 << endl;
    cout << setprecision(4) << M_PI << endl;
    cout << setprecision(10) << M_PI << endl;
    cout << setprecision(20) << M_PI << endl;

    return 0;
}

