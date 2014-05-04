#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char **argv)
{
    /* In C++, files are manipulated as streams. We can use the << and >>
       operators but, unlike cin and cout, we first need to create a
       stream corresponding to the file we want to access. */

    /* When writing to a file, we use an "ofstream" */

    ofstream examplef("example.txt");

    examplef << "Hello, foo!" << endl;
    examplef << "Hello, bar!" << endl;
    examplef << "Hello, baz!";

    /* Once we're done with a file stream, we need to explicitly close it */
    examplef.close();


    /* When reading from a file, we use an "ifstream" */

    ifstream ifs("example.txt");

    /* We can read the file line by line by using getline().
       To check whether we're done, we use the eof() method */
    int linenum = 1;
    while (!ifs.eof())
    {
        string line;
        getline(ifs, line);
        cout << linenum++ << ": " << line << endl;
    }
    ifs.close();

    return 0;
}


