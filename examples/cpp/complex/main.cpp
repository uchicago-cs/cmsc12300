#include "complex.h"

int main()
{
	Complex c1;
	Complex c2(3, 4);
	Complex c3 = c2;
	Complex c4, c5, *c6;
	
	c1 = c2;
	c4 = Complex::ONE;
	c5 = 7.0;
	c6 = new Complex(1,2);
	
	std::cout << "The number of complex numbers is " << Complex::getNumComplex() << std::endl;

	std::cout << std::endl;
	
	std::cout << "c1: " << c1 << std::endl;
	std::cout << "c2: " << c2 << std::endl;
	std::cout << "c3: " << c3 << std::endl;
	std::cout << "c4: " << c4 << std::endl;
	std::cout << "c5: " << c5 << std::endl;

	std::cout << std::endl;
	
	std::cout << "|c1| = " << c1.modulus() << std::endl;
	std::cout << "|c5| = " << c5.modulus() << std::endl;

	std::cout << std::endl;
	
	std::cout << "c1 + c2: " << c1 + c2 << std::endl;
	std::cout << "c1 - c4: " << c1 - c4 << std::endl;
	std::cout << "c1 * c5: " << c1 * c5 << std::endl;

	std::cout << std::endl;
	
	std::cout << "  c1   : " <<   c1   << std::endl;
	std::cout << "++c1   : " << ++c1   << std::endl;
	std::cout << "  c1   : " <<   c1   << std::endl;
	std::cout << "  c1++ : " <<   c1++ << std::endl;
	std::cout << "  c1   : " <<   c1   << std::endl;
	std::cout << "--c1   : " << --c1   << std::endl;
	std::cout << "  c1   : " <<   c1   << std::endl;
	std::cout << "  c1-- : " <<   c1-- << std::endl;
	std::cout << "  c1   : " <<   c1   << std::endl;
	std::cout << "- c1   : " <<  -c1   << std::endl;
	
	std::cout << std::endl;
	
	if (c2 > c4)
		std::cout << "c2 is greater than c4. Good!" << std::endl;
	else
		std::cout << "c2 is smaller than c4. Bad!" << std::endl;
	if (c2 == c3)
		std::cout << "c2 is equal to c3. Good!" << std::endl;
	else
		std::cout << "c2 is not equal to c3. Bad!" << std::endl;
	
	std::cout << std::endl;
	
	delete c6;
	std::cout << "The number of complex numbers is " << Complex::getNumComplex() << std::endl;
	
}
