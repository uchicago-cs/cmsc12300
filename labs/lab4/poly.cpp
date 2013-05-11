#include <cmath>
#include "poly.h"

using namespace std;

// We must initialize static variables like this 
int Polynomial::numPolynomials = 0;

Polynomial::Polynomial() {
	a = b = c = 0;
}

Polynomial::Polynomial(int a, int b, int c) {
	this->a = a;
	this->b = b;
	this->c = c;
}
		
// ...

Polynomial& Polynomial::operator=(const Polynomial &p) {

    // ...

    return *this; 
}

// ...

int Polynomial::getNumPolynomials() {
    return numPolynomials;
}


// Global operators

// Printing the class
std::ostream& operator<<(std::ostream &out, const Polynomial &p) {
    return out << p.a << "*x^2 + " << p.b << "*x + " << p.c;
}
