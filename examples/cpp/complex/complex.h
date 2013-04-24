#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>

class Complex
{
	private:
		/* Member variables */
		float real, imaginary;
		/* Static member variable */
		static int numComplex;
		
	public:
		/* Static (public) member variables */
		static const Complex ZERO;
		static const Complex ONE;
	
	
		/* Constructors */
		Complex();
		Complex(float real, float imaginary);
		Complex(const Complex &c); // Copy constructor
		
		
		/* Destructor */
		~Complex();
		
		
		/* Member functions */
		float modulus();
		
		
		/* Overloaded operators */
		
		// Assignment
		Complex& operator=(const Complex &c);
		Complex& operator=(float real);

		// Binary
		const Complex  operator+(const Complex &c) const;
		const Complex  operator-(const Complex &c) const;
		const Complex  operator*(const Complex &c) const;

		// Unary
		const Complex  operator-() const;

		// Increment / decrement
		Complex  operator++();    // prefix
		Complex  operator++(int); // postfix

		Complex  operator--();    // prefix
		Complex  operator--(int); // postfix

		// Relational
		bool     operator==(const Complex &c) const;
		bool     operator<(const Complex &c) const;
		bool     operator>(const Complex &c) const;
		bool     operator<=(const Complex &c) const;
		bool     operator>=(const Complex &c) const;
		bool     operator!=(const Complex &c) const;
		
		
		/* Friends */
		friend std::ostream& operator<<(std::ostream &os, const Complex &c);
		
		
		/* Static member function */
		static int getNumComplex();
};

#endif //_COMPLEX_H_
