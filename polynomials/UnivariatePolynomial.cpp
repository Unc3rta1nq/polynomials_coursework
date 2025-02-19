#include "UnivariatePolynomial.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>

UnivariatePolynomial::UnivariatePolynomial() {}

UnivariatePolynomial::UnivariatePolynomial(const std::vector<double>& coeffs) : coefficients(coeffs) {}

UnivariatePolynomial::UnivariatePolynomial(const int degree)
{
	this->coefficients.resize(degree + 1);
}

UnivariatePolynomial::UnivariatePolynomial(int degree, std::vector<double>& coeffs)
{
	coefficients.resize(degree + 1);
	coefficients = coeffs;
}

UnivariatePolynomial::~UnivariatePolynomial() {}

void UnivariatePolynomial::print() const
{
	size_t degree = coefficients.size() - 1;
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

double UnivariatePolynomial::evaluate_horner(double x) const
{
	double result = coefficients.back(); // Начинаем с наивысшей степени
	for (int i = coefficients.size() - 1; i >= 0; i--) {
		result = coefficients[i] + x * result; // Вычисляем значения по схеме Горнера
	}
	return result;
}

int UnivariatePolynomial::getDegree() const
{
	return coefficients.size() - 1;
}

double UnivariatePolynomial::getCoefficient(int power) const
{
	if (power >= 0 && power < coefficients.size() - 1) {
		return coefficients[power];
	}
	return 0.0;
}

void UnivariatePolynomial::setCoefficient(int power, double value)
{
	if (power >= 0) {
		if (power >= coefficients.size() - 1) {
			coefficients.resize(power + 1, 0.0);
		}
		coefficients[power] = value;
	}
}

bool UnivariatePolynomial::isZero() const
{
	return coefficients.empty() || (coefficients.size() == 1 && coefficients[0] == 0);
}

double& UnivariatePolynomial::operator[](int index)
{
	if (index < 0 || index > coefficients.size()) {
		throw std::out_of_range("Index out of range");
	}
	return coefficients[index];
}

UnivariatePolynomial UnivariatePolynomial::operator+(const UnivariatePolynomial& other) const
{
	int degree = coefficients.size() - 1,
		other_degree = other.coefficients.size() - 1,
		new_degree = std::max(degree, other_degree);
	std::vector<double> result_coeffs(new_degree + 1, 0.0);
	for (int i = 0; i <= new_degree; i++)
		result_coeffs[i] = (i <= coefficients.size() - 1 ? coefficients[i] : 0.0) + (i <= other.coefficients.size() - 1 ? other.coefficients[i] : 0.0);
	return UnivariatePolynomial(result_coeffs);
}
UnivariatePolynomial UnivariatePolynomial::operator-(const UnivariatePolynomial& other) const
{
	int degree = coefficients.size() - 1,
		other_degree = other.coefficients.size() - 1,
		new_degree = std::max(degree, other_degree);
	std::vector<double> result_coeffs(new_degree + 1, 0.0);
	for (int i = 0; i <= new_degree; i++)
		result_coeffs[i] = (i <= degree ? coefficients[i] : 0.0) - (i <= other_degree ? other.coefficients[i] : 0.0);
	return UnivariatePolynomial(result_coeffs);
}

bool UnivariatePolynomial::operator!=(const UnivariatePolynomial& other) const
{
	int degree_first = getDegree();
	int degree_second = other.getDegree();

	// Если степени многочленов не равны, они точно разные
	if (degree_first != degree_second)
		return true;

	// Сравниваем коэффициенты по степеням
	for (int i = 0; i <= degree_first; i++) // Цикл должен включать и степень degree_first
	{
		if (coefficients[i] != other.coefficients[i])
			return true;
	}
	// Если ни одно условие не сработало, значит многочлены одинаковые
	return false;
}

UnivariatePolynomial UnivariatePolynomial::sqrt() const {
	// Проверяем, что степень многочлена чётная
	int degree = this->getDegree();
	if (degree % 2 != 0) {
		throw std::invalid_argument("Polynomial degree must be even to have a square root.");
	}

	// Создаём вектор для коэффициентов корня
	std::vector<double> sqrtCoeffs(degree / 2 + 1, 0.0);

	// Первый коэффициент корня
	if (coefficients[degree] < 0) {
		throw std::invalid_argument("Leading coefficient must be non-negative for a perfect square.");
	}
	sqrtCoeffs[degree / 2] = std::sqrt(coefficients[degree]);

	// Постепенно вычисляем остальные коэффициенты
	for (int i = degree / 2 - 1; i >= 0; --i) {
		double sum = 0.0;
		for (int j = i + 1; j <= degree / 2; ++j) {
			sum += sqrtCoeffs[j] * sqrtCoeffs[degree / 2 + i - j];
		}
		if (sqrtCoeffs[degree / 2] == 0.0) {
			throw std::invalid_argument("Division by zero encountered. Polynomial is not a perfect square.");
		}
		sqrtCoeffs[i] = (coefficients[degree / 2 + i] - sum) / (2 * sqrtCoeffs[degree / 2]);
	}

	// Проверяем, что вычисленный корень действительно является квадратом исходного многочлена
	UnivariatePolynomial sqrtPoly(sqrtCoeffs);
	UnivariatePolynomial squaredPoly = sqrtPoly * sqrtPoly;

	if (squaredPoly != *this) {
		throw std::invalid_argument("Polynomial is not a perfect square.");
	}

	return sqrtPoly;
}

UnivariatePolynomial UnivariatePolynomial::operator*(const UnivariatePolynomial& other) const
{
	int degree = coefficients.size() - 1,
		other_degree = other.coefficients.size() - 1,
		new_degree = degree + other_degree;
	std::vector<double> result_coeffs((new_degree + 1), 0.0);

	for (int i = 0; i <= new_degree; i++) {
		result_coeffs[i] = 0;
		for (int j = 0; j <= degree; j++) {
			if (i - j >= 0 && i - j <= other_degree) {
				result_coeffs[i] += coefficients[j] * other.coefficients[i - j];
			}
		}
	}
	return UnivariatePolynomial(result_coeffs);
}

std::pair<UnivariatePolynomial, UnivariatePolynomial> UnivariatePolynomial::operator/(const UnivariatePolynomial& other) const
{
	if (other.isZero()) {
		throw std::invalid_argument("Division by zero!");
	}
	int degree = coefficients.size() - 1,
		other_degree = other.coefficients.size() - 1;
	std::vector<double> coefficients_quotient(degree - other_degree + 1);
	std::vector<double> coefficients_remainder(coefficients.begin(), coefficients.end());
	for (int i = degree - other_degree; i >= 0; i--) {

		double quotientCoefficient = coefficients_remainder[other_degree + i] / other.coefficients[other_degree];
		coefficients_quotient[i] = quotientCoefficient;

		for (int j = 0; j <= other.getDegree(); j++) {
			int index = i + j;
			coefficients_remainder[index] -= quotientCoefficient * other.coefficients[j];
		}
	}

	UnivariatePolynomial quotient(coefficients_quotient);
	UnivariatePolynomial remainder(coefficients_remainder);
	std::pair<UnivariatePolynomial, UnivariatePolynomial> result(quotient, remainder);
	return result;
}

std::vector<double> UnivariatePolynomial::getCoefficients() const {
    return coefficients;
}

