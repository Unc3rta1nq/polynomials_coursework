#include "MultivariatePolynomial.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <numeric>

MultivariatePolynomial::MultivariatePolynomial() {}

// Конструктор, принимающий коэффициенты как вектор, где каждый элемент - это пара (степени, коэффициент)
MultivariatePolynomial::MultivariatePolynomial(const std::vector<std::pair<std::vector<int>, double>>& terms) {
	for (const auto& term : terms) {
		coefficients[term.first] = term.second;
	}
}

MultivariatePolynomial::~MultivariatePolynomial() {}


void MultivariatePolynomial::print() const {
	bool firstTerm = true; // Флаг, чтобы не выводить знак "+" в начале

	// Перебираем члены в порядке убывания степеней (от старших)
	for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
		const auto& degrees = it->first;
		double coef = it->second;

		if (coef != 0.0) { // Пропускаем члены с коэффициентом 0
			if (!firstTerm) {  // Только после первого члена
				if (coef > 0.0)
					std::cout << " + ";
				else
					std::cout << " - ";
				coef = std::abs(coef);
			}
			else if (coef < 0.0) {  // Для первого отрицательного члена
				std::cout << " - ";
				coef = std::abs(coef);
			}

			// Выводим коэффициент (если не 1)
			if (std::abs(coef - 1.0) > 1e-6 || degrees == std::vector<int>(degrees.size(), 0)) {
				std::cout << coef;
			}

			// Выводим степени для каждой переменной
			for (size_t i = 0; i < degrees.size(); ++i) {
				if (degrees[i] > 0) {
					std::cout << char('a' + i); // Переменные, например, 'a', 'b', 'c', ...
					if (degrees[i] > 1)
						std::cout << "^" << degrees[i];
				}
			}

			firstTerm = false;  // После первого члена больше не выводим знак
		}
	}

	// Если ничего не напечатано, значит это ноль
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
	// Проходим по всем членам многочлена
	for (const auto& term : coefficients) {
		const std::vector<int>& powers = term.first;  // Степени переменных
		double coef = term.second;  // Коэффициент

		double term_value = coef;

		// Для каждой переменной вычисляем значение переменной в нужной степени
		for (size_t i = 0; i < powers.size(); ++i) {
			term_value *= std::pow(variables[i], powers[i]);  // Возводим переменную в степень
		}

		// Добавляем значение члена многочлена к результату
		result += term_value;
	}

	return result;
}



int MultivariatePolynomial::getDegree() const {
	int max_degree = 0;

	// Проходим по всем членам многочлена
	for (const auto& term : coefficients) {
		const std::vector<int>& powers = term.first;  // Степени переменных
		int term_degree = std::accumulate(powers.begin(), powers.end(), 0);  // Сумма степеней

		// Обновляем максимальную степень
		if (term_degree > max_degree) {
			max_degree = term_degree;
		}
	}

	return max_degree;
}

double MultivariatePolynomial::getCoefficient(const std::vector<int>& powers) const {
	auto it = coefficients.find(powers);
	if (it != coefficients.end()) {
		return it->second;  // Если найдено, возвращаем коэффициент
	}
	return 0.0;  // Если такого члена нет, возвращаем 0.0
}

void MultivariatePolynomial::setCoefficient(const std::vector<int>& powers, double value) {
	// Если коэффициент равен нулю, удаляем соответствующий член
	if (value == 0.0) {
		coefficients.erase(powers);
	}
	else {
		coefficients[powers] = value;  // Добавляем или обновляем коэффициент
	}
}


bool MultivariatePolynomial::isZero() const {
	// Проверяем все коэффициенты, если хоть один ненулевой, то многочлен не нулевой
	for (const auto& term : coefficients) {
		if (term.second != 0.0) {  
			return false; 
		}
	}
	return true; 
}


bool MultivariatePolynomial::validateVariables(const std::vector<double>& variables) const
{
	// Проверяем, что количество переменных совпадает с размером степени многочлена
	size_t num_variables = coefficients.begin()->first.size();  // Берем размер первого члена (количество переменных)
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
