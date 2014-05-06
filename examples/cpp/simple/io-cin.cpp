#include <iostream>
using namespace std;


int main(int argc, char **argv)
{
    /* To read from standard input, we use the predefined "cin" stream. However,
       since we're reading (as opposed to writing, as we did to the "cout" stream),
       we use the >> operator. */

    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "You entered the number " << n << endl;

    /* We can use >> multiple times. In that case, we will need to enter each value
       separated by whitespace (which includes newlines) */
    int a, b, c;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;
    cout << "You entered these numbers: " << a << " " << b << " " << c << endl;

    return 0;
}

