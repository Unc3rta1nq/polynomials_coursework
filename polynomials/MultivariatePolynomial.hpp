#include "AbstractPolynomial.hpp"

class MultivariatePolynomial : public AbstractPolynomial {
public:
	MultivariatePolynomial();
	MultivariatePolynomial(const std::vector<std::vector<double>>& coeffs);
	MultivariatePolynomial(int degree, std::vector<std::vector<double>>& coeffs);
	MultivariatePolynomial(const int size);
	~MultivariatePolynomial() override;
	void print() const override;
	double evaluate_horner(double x) const override;
	// double evaluate_horner(double ) пока что не понятно как и че дышать, тут должен быть вектор по идее равный числу переменных
	int getDegree() const override;
	double getCoefficient(int power) const override;
	void setCoefficient(int power, double value) override;
	bool isZero() const override;
	MultivariatePolynomial findRoots() const;
	MultivariatePolynomial operator+(const MultivariatePolynomial& other) const;
	MultivariatePolynomial operator-(const MultivariatePolynomial& other) const;
	MultivariatePolynomial operator*(const MultivariatePolynomial& other) const;
	bool operator!=(const MultivariatePolynomial& other) const;
	std::pair<MultivariatePolynomial, MultivariatePolynomial> operator/(const MultivariatePolynomial& other) const;

private:
	std::vector < std::vector<double>> coefficients;
	int degree;
};