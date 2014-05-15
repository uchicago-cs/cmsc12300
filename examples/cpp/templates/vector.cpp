/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * "vector" container example
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<int> v1;

	v1.push_back(5);
	v1.push_back(10);
	v1.push_back(3);
	v1.push_back(1);

    cout << "Vector size: " << v1.size() << endl << endl;

    /* Pre-C++11 way of iterating over containers */
	for(vector<int>::iterator i = v1.begin(); i < v1.end(); i++)
		cout << *i << endl;

    cout << endl;

    /* C++11 adds "auto" types, which makes things slightly better */
	for(auto i = v1.begin(); i < v1.end(); i++)
		cout << *i << endl;

    cout << endl;

    /* C++11 also adds for-each loops, which makes things better...er */
    for(int i : v1)
		cout << i << endl;
    
    cout << endl;

    /* C++11 also allows us to initialize vectors like this */
    vector<int> v2 {5,10,3,1,20};

    /* Comparison, along with many other operators, is overloaded in vectors */
    if(v1 == v2)
        cout << "Vectors are equal" << endl;
    else
        cout << "Vectors are not equal" << endl;

    v2.pop_back();

    if(v1 == v2)
        cout << "Vectors are equal" << endl;
    else
        cout << "Vectors are not equal" << endl;

    /* We can use the "sort" function from <algorithm> to sort the vector */
	sort(v1.begin(), v1.end());

	return 0;
}

