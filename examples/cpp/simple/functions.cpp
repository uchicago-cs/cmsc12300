#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void incr1(int a)
{
    a++;
}

void incr2(int *a)
{
    (*a)++;
}

void incr3(int &a)
{
    a++;
}



int main(int argc, char **argv)
{
    int x = 42;

    cout << "Before incr1: " << x << endl;
    incr1(x);
    cout << " After incr1: " << x << endl;

    cout << endl;

    cout << "Before incr2: " << x << endl;
    incr2(&x);
    cout << " After incr2: " << x << endl;
    
    cout << endl;

    cout << "Before incr3: " << x << endl;
    incr3(x);
    cout << " After incr3: " << x << endl;

    return 0;
}

