#pragma once
#include <vector>
#include <utility>

class AbstractPolynomial {
public:
    virtual ~AbstractPolynomial() {}
    virtual void print() const = 0;
    virtual double evaluate_horner(double x) const = 0;
    virtual bool isZero() const = 0;
    virtual int getDegree() const = 0;
    virtual double getCoefficient(int power) const = 0;
    virtual void setCoefficient(int power, double value) = 0;
};
