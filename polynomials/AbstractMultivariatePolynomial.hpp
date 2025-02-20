#include <utility>
#include <vector>
class AbstractMultivariatePolynomial {
public:
    virtual ~AbstractMultivariatePolynomial() = default;
    virtual void print() const = 0;
    virtual double evaluate(const std::vector<double>& variables) const = 0;
    virtual int getDegree() const = 0;
    virtual double getCoefficient(const std::vector<int>& powers) const = 0;
    virtual void setCoefficient(const std::vector<int>& powers, double value) = 0;
    virtual bool isZero() const = 0;
    virtual bool validateVariables(const std::vector<double>& variables) const = 0;
};