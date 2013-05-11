#ifndef _POLY_H_
#define _POLY_H_

#include <iostream>
    
class Polynomial
{
private:
    // Member variables 

    // Coefficients
    int a, b, c;

    // Static variables
    static int numPolynomials;
    
public:
    // Constructors
    Polynomial();
    Polynomial(int a, int b, int c);
    Polynomial(const Polynomial &p); // Copy constructor
    
    // Destructor 
    ~Polynomial();
    
    // Member functions
    bool hasRealSolution() const;
    double getRealSolution1() const;
    double getRealSolution2() const;
    int evaluate(int x) const;
    
    // Overloaded operators
    Polynomial& operator=(const Polynomial &p);
    Polynomial  operator+(const Polynomial &p) const;
    bool        operator==(const Polynomial &p) const;

    // Static member functions
    static int getNumPolynomials();

    // Allow this function to access private members in Polynomial
    friend std::ostream& operator<<(std::ostream &out, const Polynomial &p);
};

#endif //_POLY_H_
