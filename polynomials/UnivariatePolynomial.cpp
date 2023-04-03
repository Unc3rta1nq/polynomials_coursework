#include "UnivariatePolynomial.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>

UnivariatePolynomial::UnivariatePolynomial() {}
UnivariatePolynomial::UnivariatePolynomial(const std::vector<double>& coeffs) : coefficients(coeffs) {}
UnivariatePolynomial::~UnivariatePolynomial() {}

void UnivariatePolynomial::print() const {
	size_t degree = getDegree();
	bool printed = false;
	for (size_t i = degree; i > 0; --i) {
		double coef = coefficients[i];
		if (coef != 0.0) {
			if (printed && coef > 0.0)
				std::cout << " + ";
			else if (coef < 0.0) {
				std::cout << " - ";
				coef = -coef;
			}
			std::cout << coef;
			if (i > 1)
				std::cout << "x^" << i;
			else if (i == 1)
				std::cout << "x";
			printed = true;
		}
	}
	double coef = coefficients[0];
	if (coef != 0.0) {
		if (printed && coef > 0.0)
			std::cout << " + ";
		else if (coef < 0.0) {
			std::cout << " - ";
			coef = -coef;
		}
		std::cout << coef;
	}
	else if (!printed)
		std::cout << "0";
	std::cout << std::endl;
}

double UnivariatePolynomial::evaluate(double x) const {
	double result = 0.0;
	double power = 1.0;
	for (int i = 0; i < coefficients.size(); i++) {
		result += coefficients[i] * power;
		power *= x;
	}
	return result;
}

bool UnivariatePolynomial::isZero() const {
	return coefficients.empty() || (coefficients.size() == 1 && coefficients[0] == 0);
}

int UnivariatePolynomial::getDegree() const {
	return coefficients.size() - 1;
}

double UnivariatePolynomial::getCoefficient(int power) const {
	if (power >= 0 && power < coefficients.size()) {
		return coefficients[power];
	}
	return 0.0;
}

void UnivariatePolynomial::setCoefficient(int power, double value) {
	if (power >= 0) {
		if (power >= coefficients.size()) {
			coefficients.resize(power + 1, 0.0);
		}
		coefficients[power] = value;
	}
}

UnivariatePolynomial* UnivariatePolynomial::add(const AbstractPolynomial& other) const {
	const UnivariatePolynomial& casted = dynamic_cast<const UnivariatePolynomial&>(other);
	
	if (getDegree() < casted.getDegree()) 
		return casted.add(*this);

	const int degree = getDegree();
	const int degree_casted = casted.getDegree();
	const int degree_max = std::max(degree, degree_casted);
	std::vector<double> result_coeffs(degree_max + 1, 0.0);
	
	for (int i = 0; i <= degree_max; i++) {
		double coefficient = (i <= degree ? coefficients[i] : 0.0) + (i <= degree_casted ? casted.coefficients[i] : 0.0);
		result_coeffs[i] = coefficient;
	}

	return new UnivariatePolynomial(result_coeffs);
}

UnivariatePolynomial* UnivariatePolynomial::subtract(const AbstractPolynomial& other) const {
	const UnivariatePolynomial& casted = dynamic_cast<const UnivariatePolynomial&>(other);
	
	if (getDegree() < casted.getDegree()) 
		return casted.add(*this);
	
	const int degree = getDegree();
	const int degree_casted = casted.getDegree();
	const int degree_max = std::max(degree, degree_casted);
	std::vector<double> result_coeffs((degree_max + 1), 0.0);

	for (int i = 0; i <= degree_max; i++) {
		double coefficient = (i <= degree ? coefficients[i] : 0.0) - (i <= degree_casted ? casted.coefficients[i] : 0.0);
		result_coeffs[i] = coefficient;
	}

	return new UnivariatePolynomial(result_coeffs);
}

UnivariatePolynomial* UnivariatePolynomial::multiply(const AbstractPolynomial& other) const {
	const UnivariatePolynomial& casted = dynamic_cast<const UnivariatePolynomial&>(other);

	const int size = coefficients.size() + casted.coefficients.size() - 1;
	std::vector<double> result_coeffs(size, 0.0);

	for (int i = 0; i < coefficients.size(); i++) {
		for (int j = 0; j < casted.coefficients.size(); j++) {
			result_coeffs[i + j] += coefficients[i] * casted.coefficients[j];
		}
	}

	return new UnivariatePolynomial(result_coeffs);
}

std::pair<UnivariatePolynomial, UnivariatePolynomial> UnivariatePolynomial::divide(const UnivariatePolynomial& other)  {
	if (other.isZero()) {
		throw std::invalid_argument("Division by zero!");
	}

	std::vector<double> coefficientsQuotient(getDegree() - other.getDegree() + 1);
	std::vector<double> coefficientsRemainder(coefficients.begin(), coefficients.end());

	for (int i = getDegree() - other.getDegree(); i >= 0; i--) {
		// Вычисляем текущий коэффициент частного
		double quotientCoefficient = coefficientsRemainder[other.getDegree() + i] / other.coefficients[other.getDegree()];
		coefficientsQuotient[i] = quotientCoefficient;
		// Обновляем остаток
		for (int j = 0; j <= other.getDegree(); j++) {
			int index = i + j;
			coefficientsRemainder[index] -= quotientCoefficient * other.coefficients[j];
		}
	}

	UnivariatePolynomial quotient(coefficientsQuotient);
	UnivariatePolynomial remainder(coefficientsRemainder);
	std::pair<UnivariatePolynomial, UnivariatePolynomial> result(quotient, remainder);
	return result;
}
