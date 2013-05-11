#include "poly.h"
#define RESET "\e[m"
#define GREEN "\e[32m"
#define RED   "\e[31m"

using namespace std;

template <typename T>
bool test(const T &value, const T &expected, const string &name, bool eq = true) {
    if (!((value == expected) ^ eq)) {
        cout << GREEN "Passed test: " RESET << name << endl;
        return true;
    } else {
        cout << RED "Failed test: " RESET << name << endl;
        cout << ".. Compared " << value << " with " << expected << " expecting them to be " << (eq ? "the same" : "different") << endl;
        return false;
    }
}

Polynomial double_it(Polynomial x) {
    return x+x;
}

int main()
{
	Polynomial p1;
	Polynomial p2(2,4,-30);
	Polynomial p3 = p2; // Deceptively uses the copy constructor instead of the assignment operator
	Polynomial *p4 = new Polynomial(1,1,1);
	Polynomial p5;
	Polynomial p6(1,0,-20);
	
	//cout << "Number of polynomials is " << Polynomial::getNumPolynomials() << endl;

    test(Polynomial::getNumPolynomials(), 6, "6 polynomial instances");
	
	p5 = p2;
	
    bool copy_ok = test(p3, p2, "p3 == p2 (copy constructor and == operator)");
    test(p5, p2, "p5 == p2 (assignment operator and == opeator)");
    test(p2, *p4, "p2 != *p4", false);

    test(p2.evaluate(3), 0, "p2.evaluate(3) == 0"); 
    test(p2.evaluate(-5), 0, "p2.evaluate(-5) == 0");   
    test(p2.evaluate(0), -30, "p2.evaluate(0) == -30");

    bool ok = test(p2.hasRealSolution(), true, "p2 has real solutions");
    if (ok) {
        test(p2.getRealSolution1(), 3.0, "p2: x1 = 3");
        test(p2.getRealSolution2(), -5.0, "p2: x2 = -5");
    }

    test(p4->hasRealSolution(), false, "p4 has no real solutions");

    if (copy_ok) {
        Polynomial p7 = p2 + p6;
    
        test(p7, Polynomial(3, 4, -50), "p2 + p6");
    }

	delete p4;		
    test(Polynomial::getNumPolynomials(), 5, "5 polynomial instances");

    // This printing test is not automated
    cout << endl;
    cout << "Printing p6 yields:        " << p6 << endl;
    cout << "Try to make it look like:  x^2 - 20" << endl;
}
