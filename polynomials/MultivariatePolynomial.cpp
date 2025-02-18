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

MultivariatePolynomial MultivariatePolynomial::operator+(const MultivariatePolynomial& other) const
{
	return MultivariatePolynomial();
}

MultivariatePolynomial MultivariatePolynomial::operator-(const MultivariatePolynomial& other) const
{
	return MultivariatePolynomial();
}

MultivariatePolynomial MultivariatePolynomial::operator*(const MultivariatePolynomial& other) const
{
	return MultivariatePolynomial();
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


std::pair<MultivariatePolynomial, MultivariatePolynomial> MultivariatePolynomial::operator/(const MultivariatePolynomial& other) const
{
	return std::pair<MultivariatePolynomial, MultivariatePolynomial>();
}
