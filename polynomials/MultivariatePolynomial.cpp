#include "MultivariatePolynomial.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <numeric>

MultivariatePolynomial::MultivariatePolynomial() {}

// �����������, ����������� ������������ ��� ������, ��� ������ ������� - ��� ���� (�������, �����������)
MultivariatePolynomial::MultivariatePolynomial(const std::vector<std::pair<std::vector<int>, double>>& terms) {
	for (const auto& term : terms) {
		coefficients[term.first] = term.second;
	}
}

MultivariatePolynomial::~MultivariatePolynomial() {}


void MultivariatePolynomial::print() const {
	bool firstTerm = true; // ����, ����� �� �������� ���� "+" � ������

	// ���������� ����� � ������� �������� �������� (�� �������)
	for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
		const auto& degrees = it->first;
		double coef = it->second;

		if (coef != 0.0) { // ���������� ����� � ������������� 0
			if (!firstTerm) {  // ������ ����� ������� �����
				if (coef > 0.0)
					std::cout << " + ";
				else
					std::cout << " - ";
				coef = std::abs(coef);
			}
			else if (coef < 0.0) {  // ��� ������� �������������� �����
				std::cout << " - ";
				coef = std::abs(coef);
			}

			// ������� ����������� (���� �� 1)
			if (std::abs(coef - 1.0) > 1e-6 || degrees == std::vector<int>(degrees.size(), 0)) {
				std::cout << coef;
			}

			// ������� ������� ��� ������ ����������
			for (size_t i = 0; i < degrees.size(); ++i) {
				if (degrees[i] > 0) {
					std::cout << char('a' + i); // ����������, ��������, 'a', 'b', 'c', ...
					if (degrees[i] > 1)
						std::cout << "^" << degrees[i];
				}
			}

			firstTerm = false;  // ����� ������� ����� ������ �� ������� ����
		}
	}

	// ���� ������ �� ����������, ������ ��� ����
	if (firstTerm) {
		std::cout << "0";
	}

	std::cout << std::endl;
}

double MultivariatePolynomial::evaluate_horner(const std::vector<double>& variables) const {

	if (!validateVariables(variables)) {
		throw std::invalid_argument("Error: The number of variables in the input vector does not match the number of variables in the polynomial.");
	}

	double result = 0.0;
	// �������� �� ���� ������ ����������
	for (const auto& term : coefficients) {
		const std::vector<int>& powers = term.first;  // ������� ����������
		double coef = term.second;  // �����������

		double term_value = coef;

		// ��� ������ ���������� ��������� �������� ���������� � ������ �������
		for (size_t i = 0; i < powers.size(); ++i) {
			term_value *= std::pow(variables[i], powers[i]);  // �������� ���������� � �������
		}

		// ��������� �������� ����� ���������� � ����������
		result += term_value;
	}

	return result;
}



int MultivariatePolynomial::getDegree() const {
	int max_degree = 0;

	// �������� �� ���� ������ ����������
	for (const auto& term : coefficients) {
		const std::vector<int>& powers = term.first;  // ������� ����������
		int term_degree = std::accumulate(powers.begin(), powers.end(), 0);  // ����� ��������

		// ��������� ������������ �������
		if (term_degree > max_degree) {
			max_degree = term_degree;
		}
	}

	return max_degree;
}

double MultivariatePolynomial::getCoefficient(const std::vector<int>& powers) const {
	auto it = coefficients.find(powers);
	if (it != coefficients.end()) {
		return it->second;  // ���� �������, ���������� �����������
	}
	return 0.0;  // ���� ������ ����� ���, ���������� 0.0
}

void MultivariatePolynomial::setCoefficient(const std::vector<int>& powers, double value) {
	// ���� ����������� ����� ����, ������� ��������������� ����
	if (value == 0.0) {
		coefficients.erase(powers);
	}
	else {
		coefficients[powers] = value;  // ��������� ��� ��������� �����������
	}
}


bool MultivariatePolynomial::isZero() const {
	// ��������� ��� ������������, ���� ���� ���� ���������, �� ��������� �� �������
	for (const auto& term : coefficients) {
		if (term.second != 0.0) {  
			return false; 
		}
	}
	return true; 
}


bool MultivariatePolynomial::validateVariables(const std::vector<double>& variables) const
{
	// ���������, ��� ���������� ���������� ��������� � �������� ������� ����������
	size_t num_variables = coefficients.begin()->first.size();  // ����� ������ ������� ����� (���������� ����������)
	if (variables.size() != num_variables) {
		return false;
	}
	return true;
}

MultivariatePolynomial MultivariatePolynomial::findRoots() const
{
	return MultivariatePolynomial();
}

MultivariatePolynomial MultivariatePolynomial::operator+(const MultivariatePolynomial& other) const {
	// ����� ��������� ��� ����������
	MultivariatePolynomial result;
	// �������� �� ���� ������ �������� ����������
	for (const auto& term : this->coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;
		result.setCoefficient(powers, coef);  // ��������� � ��������� ������� ����
	}
	// �������� �� ���� ������ ������� ����������
	for (const auto& term : other.coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;

		// ���� ����� ���� ��� ���� � ������� ����������, ���������� �����������
		double currentCoef = result.getCoefficient(powers);
		result.setCoefficient(powers, currentCoef + coef);  // �������� �������������
	}

	return result;
}


MultivariatePolynomial MultivariatePolynomial::operator-(const MultivariatePolynomial& other) const {
	// ����� ��������� ��� ����������
	MultivariatePolynomial result;

	// �������� �� ���� ������ �������� ����������
	for (const auto& term : this->coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;
		result.setCoefficient(powers, coef);  // ��������� ������� ����
	}

	// �������� �� ���� ������ ������� ����������
	for (const auto& term : other.coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;

		// ���� ����� ���� ��� ���� � ������� ����������, �������� ��� �����������
		double currentCoef = result.getCoefficient(powers);
		result.setCoefficient(powers, currentCoef - coef);  // ��������� �������������
	}

	return result;
}


MultivariatePolynomial MultivariatePolynomial::operator*(const MultivariatePolynomial& other) const {
	MultivariatePolynomial result;  // ����� ��������� ��� ����������

	// �������� �� ���� ������ �������� ����������
	for (const auto& term1 : this->coefficients)
	{
		const std::vector<int>& powers1 = term1.first;  // ������� ���������� ��� ������� �����
		double coef1 = term1.second;  // ����������� ������� �����

		// �������� �� ���� ������ ������� ����������
		for (const auto& term2 : other.coefficients)
		{
			const std::vector<int>& powers2 = term2.first;  // ������� ���������� ��� ������� �����
			double coef2 = term2.second;  // ����������� ������� �����

			// �������� ������������
			double newCoef = coef1 * coef2;

			// ���������� ������� ��������������� ����������
			std::vector<int> newPowers;
			for (size_t i = 0; i < powers1.size(); ++i)
			{
				newPowers.push_back(powers1[i] + powers2[i]);
			}

			// ��������� ����� ���� � ��������� (���������� ����� setCoefficient)
			double currentCoef = result.getCoefficient(newPowers);
			result.setCoefficient(newPowers, currentCoef + newCoef);  // �������� ������������� ��� ���������� ��������
		}
	}

	return result;  // ���������� ���������
}


bool MultivariatePolynomial::operator!=(const MultivariatePolynomial& other) const {
	if (this->getDegree() != other.getDegree())
	{
		return true;
	}
	if (this->coefficients != other.coefficients)
	{
		return true;
	}
	return false;  
}

// �������� �������
std::pair<MultivariatePolynomial, MultivariatePolynomial> MultivariatePolynomial::operator/(const MultivariatePolynomial& other) const {
	MultivariatePolynomial quotient;  // �������
	MultivariatePolynomial remainder = *this;  // �������, �������� � ������ ��������

	// ���������, ��� �������� �� ����� ����
	if (other.isZero())
	{
		throw std::invalid_argument("Cannot divide by zero polynomial.");
	}

	// �������� ������� � ��������
	while (!remainder.isZero() && remainder.getDegree() >= other.getDegree())
	{
		// �������� ������� ����� � �������� � ��������
		auto highestTermRemainder = remainder.coefficients.rbegin();  // ������� ���� �������
		auto highestTermOther = other.coefficients.rbegin();  // ������� ���� ��������

		// ������� � ������������ ������� ������
		std::vector<int> powersRemainder = highestTermRemainder->first;
		double coefRemainder = highestTermRemainder->second;

		std::vector<int> powersOther = highestTermOther->first;
		double coefOther = highestTermOther->second;

		// ��������, ����� ������� ���� ��������
		if (coefRemainder == 0 || coefOther == 0 || powersRemainder.size() != powersOther.size())
		{
			throw std::invalid_argument("Cannot divide: incompatible degrees or zero coefficients.");
		}

		// ���������� ������ ����� ��������
		double newCoef = coefRemainder / coefOther;
		std::vector<int> newPowers;
		for (size_t i = 0; i < powersRemainder.size(); ++i)
		{
			newPowers.push_back(powersRemainder[i] - powersOther[i]);  // ������� ���������� ��� ��������
		}

		// ��������� ���� ����� ���� � �������
		quotient.setCoefficient(newPowers, newCoef);

		// ��������� ����� ������� ����� ���������
		MultivariatePolynomial termToSubtract;
		termToSubtract.setCoefficient(newPowers, newCoef);

		remainder = remainder - (other * termToSubtract);  // �������� ���������� ���� �� �������
	}

	return std::make_pair(quotient, remainder);  // ���������� ���� (�������, �������)
}