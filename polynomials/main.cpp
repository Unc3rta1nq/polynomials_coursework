#include "UnivariatePolynomial.hpp"
#include <iostream>

int main(void) {

	UnivariatePolynomial poly1({ 1.0, 2.0, 3.5 });
	std::cout << "First polynomial: ";
	poly1.print();
	std::cout << std::endl;

	UnivariatePolynomial poly2({ -1.0, 1.0 });
	std::cout << "Second polynomial: ";
	poly2.print();
	std::cout << std::endl;

	int x = 10;
	std::cout << "Polynomial value at x = " << x << " is " << poly1.evaluate(x) << std::endl;

	UnivariatePolynomial* sum = poly1.add(poly2);
	std::cout << "New polynomial coefficients after add: ";
	sum->print();
	std::cout << std::endl;

	UnivariatePolynomial* sum1 = poly1.subtract(poly2);
	std::cout << "New polynomial coefficients after subtract: ";
	sum1->print();
	std::cout << std::endl;

	UnivariatePolynomial* sum2 = poly1.multiply(poly2);
	std::cout << "New polynomial coefficients after multiply: ";
	sum2->print();
	std::cout << std::endl;

	auto result = poly1.divide(poly2);
	std::cout << "New polynomial coefficients after divide:" << std::endl <<  "Quotient: ";
	result.first.print();
	std::cout << "Remainder:" ;
	result.second.print();
	std::cout << std::endl;

	return 0;
}	