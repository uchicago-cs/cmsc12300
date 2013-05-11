#include "complex.h"
#include <cmath>
#include <iostream>

int Complex::numComplex = 0;
const Complex Complex::ZERO = Complex(0,0);
const Complex Complex::ONE = Complex(1,0);

Complex::Complex()
{
	real = imaginary = 0;
	numComplex++;
}

Complex::Complex(float real, float imaginary = 0)
{
	this->real = real;
	this->imaginary = imaginary;
	numComplex++;
}
		
Complex::Complex(const Complex &c)
{
	real = c.real;
	imaginary = c.imaginary;
	numComplex++;
}

Complex::~Complex()
{
	numComplex--;
}

float Complex::modulus()
{
	return sqrt(real*real + imaginary*imaginary);
}


Complex& Complex::operator=(const Complex &c)
{
	real = c.real;
	imaginary = c.imaginary;
	return *this;
}

Complex& Complex::operator=(float real)
{
	this->real = real;
	this->imaginary = 0;
	return *this;
}


const Complex  Complex::operator+(const Complex &c) const
{
	float new_real, new_imaginary;
	new_real = real + c.real;
	new_imaginary = imaginary + c.imaginary;

	Complex sum(new_real, new_imaginary);
	return sum;
}

const Complex  Complex::operator-(const Complex &c) const
{
	// More compact than above, but harder to read
	return Complex(real - c.real, imaginary - c.imaginary);
}

const Complex  Complex::operator*(const Complex &c) const
{
	// Again, compact but hard to read.
	return Complex(real * c.real - imaginary * c.imaginary, imaginary * c.real + real * c.imaginary);
}


const Complex  Complex::operator-() const
{
	return Complex(-real, -imaginary);
}


Complex  Complex::operator++()
{
	*this = *this + ONE;
	return *this;
}

Complex  Complex::operator++(int)
{
	Complex old_value = *this;
	*this = *this + ONE;
	return old_value;
}

Complex  Complex::operator--()
{
	*this = *this - ONE;
	return *this;
}

Complex  Complex::operator--(int)
{
	Complex old_value = *this;
	*this = *this - ONE;
	return old_value;
}


bool     Complex::operator==(const Complex &c) const
{
	return (real == c.real && imaginary == c.imaginary);
}

// This is arbitrary. There is no natural order in complex numbers
bool     Complex::operator<(const Complex &c) const
{
	return (real < c.real && imaginary < c.imaginary);
}

bool     Complex::operator>(const Complex &c) const
{
	return !(*this == c || *this < c);
}

bool     Complex::operator<=(const Complex &c) const
{
	return !(*this > c);
}

bool     Complex::operator>=(const Complex &c) const
{
	return !(*this < c);
}

bool     Complex::operator!=(const Complex &c) const
{
	return !(*this == c);
}



std::ostream& operator<<(std::ostream &os, const Complex &c)
{
	os << c.real << " + " << c.imaginary << "i";
	return os;
}

int Complex::getNumComplex()
{
	return numComplex - 2; // We don't include ZERO and ONE
}
