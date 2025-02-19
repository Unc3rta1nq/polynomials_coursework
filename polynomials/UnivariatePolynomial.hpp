#include "AbstractUnivariatePolynomial.hpp"

class UnivariatePolynomial : public AbstractPolynomial {
public:
	UnivariatePolynomial();
	UnivariatePolynomial(const std::vector<double>& coeffs);
	UnivariatePolynomial(int degree, std::vector<double>& coeffs);
	UnivariatePolynomial(const int size);
	~UnivariatePolynomial() override;
	void print() const override;
	double evaluate_horner(double x) const override;
	int getDegree() const override;
	double getCoefficient(int power) const override;
	void setCoefficient(int power, double value) override;
	bool isZero() const override;
	double& operator[](int index);
	UnivariatePolynomial sqrt() const;
	UnivariatePolynomial operator+(const UnivariatePolynomial& other) const;
	UnivariatePolynomial operator-(const UnivariatePolynomial& other) const;
	UnivariatePolynomial operator*(const UnivariatePolynomial& other) const;
	bool operator!=(const UnivariatePolynomial& other) const;
	std::pair<UnivariatePolynomial, UnivariatePolynomial> operator/(const UnivariatePolynomial& other) const;
	std::vector<double> getCoefficients() const;





private:
	std::vector<double> coefficients;
};