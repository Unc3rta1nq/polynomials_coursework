#include "AbstractMultivariatePolynomial.hpp"
#include <map>

class MultivariatePolynomial : AbstractMultivariatePolynomial {

public:
	MultivariatePolynomial();
	MultivariatePolynomial(const std::vector<std::pair<std::vector<int>, double>>& terms);
	~MultivariatePolynomial();
	void print() const override;
	double evaluate_horner(const std::vector<double>& variables) const override;
	int getDegree() const override;
	double getCoefficient(const std::vector<int>& powers) const override;
	void setCoefficient(const std::vector<int>& powers, double value) override;
	bool isZero() const override;
	bool validateVariables(const std::vector<double>& variables) const override;
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