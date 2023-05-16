#include "UnivariatePolynomial.hpp"
#include <iostream>
//TODO:
// evavuate horner +
// operator []
//  basic arithmetic operations + - * \
// change basic methods change retur nvalue
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
	AbstractPolynomial* a = new UnivariatePolynomial({ 1.0,2.0,3.0 });
	AbstractPolynomial* b = new UnivariatePolynomial({ 1.0,2.0,3.0 });
	AbstractPolynomial* c = new UnivariatePolynomial({ 1.0,2.0,3.0 });
	//AbstractPolynomial* a = PolynomL::add(b, c);

	//AbstractPolynomial* result = PolynomialMath::add(*a, *b);
	std::cout << std::endl;
	UnivariatePolynomial result = poly1 + poly2;

	std::cout << "Result sum of 2 poly: ";
	result.print();
	UnivariatePolynomial result1 = poly1 * poly2;
	result1.print();
	std::pair <UnivariatePolynomial, UnivariatePolynomial> result2 = poly1 / poly2;
	result2.first.print();
	result2.second.print();
	//result->print();
	return 0;
}