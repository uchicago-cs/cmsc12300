#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Here we define a function template for
   a function that swaps the value of two
   variables. Since assignment is defined
   for all built-in types (and it typically
   defined for built-in types) this function
   should work with most types T */
template<typename T>
void mySwap(T &a, T &b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

/* And here we define a class template for
   pairs of objects, similar to the standard
   "pair" class */
template<typename T, typename U>
class myPair
{
    public:
        T first;
        U second;
    
        myPair(T first, U second)
        {
            this->first = first;
            this->second = second;
        }
};

template<typename T, typename U>
std::ostream& operator<<(std::ostream &os, const myPair<T,U> &p)
{
    os << "(" << p.first << ", " << p.second << ")";
}


int main() {
	int a = 10, b = 20;

	cout << a << " " << b << endl;

    // To use the mySwap function, we need to specify the type
    // we want to use in place of T
	mySwap<int>(a,b);

	cout << a << " " << b << endl;

    // Similarly when creating objects of a class template
	myPair<string,int> p1("one",1);
	myPair<string,int> p2("two",2);
	myPair<string,int> p3("three",3);
	myPair<string,int> p4("four",4);

    // We can create vectors of class templates
	vector<myPair<string,int> > pv {p1, p2, p3, p4};

	for(auto p : pv)
		cout << p << endl;

	return 0;
}

