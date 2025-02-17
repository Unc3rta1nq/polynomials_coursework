#include "AbstractPolynomial.hpp"

class MultivariatePolynomial : public AbstractPolynomial {
public:
	MultivariatePolynomial();
	MultivariatePolynomial(int degree, std::vector<double>& coeffs);
	MultivariatePolynomial(const int size);
	~MultivariatePolynomial() override;
	void print() const override;
	// double evaluate_horner(double ) пока что не понятно как и че дышать, тут должен быть вектор по идее равный числу переменных
	int getDegree() const override;
	double getCoefficient(int power) const override;
	void setCoefficient(int power, double value) override;

};