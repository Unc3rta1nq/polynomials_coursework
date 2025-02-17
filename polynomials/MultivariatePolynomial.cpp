#include "MultivariatePolynomial.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>

MultivariatePolynomial::MultivariatePolynomial() {}

MultivariatePolynomial::MultivariatePolynomial(const std::vector<std::vector<double>>& coeffs) : degree(degree), coefficients(coeffs) {}

MultivariatePolynomial::MultivariatePolynomial(const int degree)
{
	coefficients.resize(degree + 1, std::vector<double>(degree + 1, 0.0));
}

MultivariatePolynomial::MultivariatePolynomial(int degree, std::vector<std::vector<double>>& coeffs)
{
	coefficients = coeffs;
}

MultivariatePolynomial::~MultivariatePolynomial() {}


void MultivariatePolynomial::print() const {
    bool printed = false; // ����, ����� �� �������� ���� "+" � ������

    // ���������� ��� ������� x (�� ��������)
    for (int i = degree; i >= 0; --i) {
        // ���������� ��� ������� y (�� ��������)
        for (int j = degree; j >= 0; --j) {
            double coef = coefficients[i][j];

            // ���� ����������� ���������, �� ����������
            if (coef != 0.0) {
                // ������� ����
                if (printed) {
                    if (coef > 0.0)
                        std::cout << " + ";
                    else
                        std::cout << " - ";
                    coef = std::abs(coef); // ������� ����������� ������������� ��� ������
                }
                else if (coef < 0.0) {
                    std::cout << " - ";
                    coef = std::abs(coef); // ���� ������ �������������, ������ ����
                }

                // ������� �����������, ���� �� �� ����� 1 ��� -1
                if (coef != 1.0 || (i == 0 && j == 0)) {
                    std::cout << coef;
                }

                // ������� ������� ����������
                if (i > 0) {
                    std::cout << "x";
                    if (i > 1) {
                        std::cout << "^" << i;
                    }
                }

                if (j > 0) {
                    std::cout << "y";
                    if (j > 1) {
                        std::cout << "^" << j;
                    }
                }

                // ������������� ���� ������
                printed = true;
            }
        }
    }

    // ���� ������ �� ����������, ������ ��� ����
    if (!printed) {
        std::cout << "0";
    }

    std::cout << std::endl;
}

double MultivariatePolynomial::evaluate_horner(double x) const
{
	return 0.0;
}

int MultivariatePolynomial::getDegree() const
{
	return 0;
}

double MultivariatePolynomial::getCoefficient(int power) const
{
	return 0.0;
}

void MultivariatePolynomial::setCoefficient(int power, double value)
{
}

bool MultivariatePolynomial::isZero() const
{
	return false;
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

bool MultivariatePolynomial::operator!=(const MultivariatePolynomial& other) const
{
	return false;
}

std::pair<MultivariatePolynomial, MultivariatePolynomial> MultivariatePolynomial::operator/(const MultivariatePolynomial& other) const
{
	return std::pair<MultivariatePolynomial, MultivariatePolynomial>();
}
