#include "AbstractPolynomial.hpp"
#include <map>

class MultivariatePolynomial {

public:
	MultivariatePolynomial();
	MultivariatePolynomial(const std::vector<std::pair<std::vector<int>, double>>& terms);
	~MultivariatePolynomial();
	void print() const;
	double evaluate_horner(const std::vector<double>& variables) const;
	int getDegree() const;
	double getCoefficient(const std::vector<int>& powers) const;
	void setCoefficient(const std::vector<int>& powers, double value);
	bool isZero() const;
	bool validateVariables(const std::vector<double>& variables) const;
	MultivariatePolynomial sqrt() const;
	MultivariatePolynomial operator+(const MultivariatePolynomial& other) const;
	MultivariatePolynomial operator-(const MultivariatePolynomial& other) const;
	MultivariatePolynomial operator*(const MultivariatePolynomial& other) const;
	bool operator!=(const MultivariatePolynomial& other) const;
	std::pair<MultivariatePolynomial, MultivariatePolynomial> operator/(const MultivariatePolynomial& other) const;

private:
	// Храним коэффициенты многочлена как map: ключ — степень каждой переменной, значение — коэффициент
	std::map<std::vector<int>, double> coefficients; // Мапа для хранения коэффициентов
};