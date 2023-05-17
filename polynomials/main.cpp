#include "UnivariatePolynomial.hpp"
#include <iostream>
//TODO:
// evavuate horner +
// operator []
//  basic arithmetic operations + - * \
// change basic methods change return value
// add constructor (const int degree)

int main(void) {

	UnivariatePolynomial poly1({ 1.0, 0.0, 3.0 });
	std::cout << "First polynomial: ";
	poly1.print();
	std::cout << std::endl;

	UnivariatePolynomial poly2({ -1.0, 1.0, 1.0 });
	std::cout << "Second polynomial: ";
	poly2.print();
	std::cout << std::endl;

	UnivariatePolynomial sum = poly1 + poly2;
	std::cout << "Result sum of 2 poly: ";
	sum.print();

	UnivariatePolynomial sub = poly1 - poly2;
	std::cout << "Result sub of 2 poly: ";
	sub.print();

	UnivariatePolynomial mul = poly1 * poly2;
	std::cout << "Result mul of 2 poly: ";
	mul.print();

	std::pair <UnivariatePolynomial, UnivariatePolynomial> divide = poly1 / poly2;
	std::cout << "Result divide of 2 poly: " << std::endl << "Quotient: ";
	divide.first.print();

	std::cout << "Remainder: ";
	divide.second.print();

	std::cout << std::endl;
	return 0;
}