/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2014
 *
 * "map" container example
 *
 */

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	map<string, int> m1;

    m1["foo"] = 10;
    m1["bar"] = 20;
    m1["baz"] = 30;

    cout << m1["foo"] << endl << endl;

    /* When iterating over the map, the iterator actually returns
       a pair object. We can access the key using the "first"
       attribute, and the value using the "second" attribute */
    for(pair<const string, int> i : m1)
		cout << i.first << ": " << i.second << endl;
    
    cout << endl;

    /* Even easier with the "auto" type */
    for(auto i : m1)
		cout << i.first << ": " << i.second << endl;
    
    cout << endl;

    /* We can also initialize maps like this in C++11 */
    map<string, int> m2 { {"aaa", 100}, {"bbb", 200}, {"ccc", 300}};

    for(auto i : m2)
		cout << i.first << ": " << i.second << endl;

	return 0;
}

