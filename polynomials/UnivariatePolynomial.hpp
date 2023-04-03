#include "AbstractPolynomial.hpp"

class UnivariatePolynomial : public AbstractPolynomial {
public:
	UnivariatePolynomial();
	UnivariatePolynomial(const std::vector<double>& coeffs);
	~UnivariatePolynomial() override;
	void print() const override;
	double evaluate(double x) const override;
	int getDegree() const override;
	double getCoefficient(int k) const override;
	void setCoefficient(int k, double value) override;
	bool isZero() const override;
	UnivariatePolynomial* add(const AbstractPolynomial& other) const override;
	UnivariatePolynomial* subtract(const AbstractPolynomial& other) const override;
	UnivariatePolynomial* multiply(const AbstractPolynomial& other) const override;
	std::pair<UnivariatePolynomial, UnivariatePolynomial> divide(const UnivariatePolynomial& other) ;
private:
	std::vector<double> coefficients;
};