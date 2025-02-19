#include "MultivariatePolynomial.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <numeric>
#include "UnivariatePolynomial.hpp"


void printVector(const std::vector<std::pair<std::vector<int>, double>>& v) {
	for (const auto& pair : v)
	{
		std::cout << "(";
		for (size_t i = 0; i < pair.first.size(); ++i)
		{
			std::cout << pair.first[i];
			if (i < pair.first.size() - 1)
			{
				std::cout << ", ";
			}
		}
		std::cout << ") : " << pair.second << std::endl;
	}
}


MultivariatePolynomial::MultivariatePolynomial() {}


MultivariatePolynomial::MultivariatePolynomial(const std::vector<std::pair<std::vector<int>, double>>& terms) {
	for (const auto& term : terms)
	{
		coefficients[term.first] = term.second;
	}
}


MultivariatePolynomial::~MultivariatePolynomial() {}


void MultivariatePolynomial::print() const {
	bool firstTerm = true;

	for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it)
	{
		const auto& degrees = it->first;
		double coef = it->second;

		if (coef != 0.0)
		{
			if (!firstTerm)
			{
				if (coef > 0.0)
					std::cout << " + ";
				else
					std::cout << " - ";
				coef = std::abs(coef);
			}
			else if (coef < 0.0)
			{
				std::cout << " - ";
				coef = std::abs(coef);
			}


			if (std::abs(coef - 1.0) > 1e-6 || degrees == std::vector<int>(degrees.size(), 0))
			{
				std::cout << coef;
			}


			for (size_t i = 0; i < degrees.size(); ++i)
			{
				if (degrees[i] > 0)
				{
					std::cout << char('a' + i); // Переменные, например, 'a', 'b', 'c', ...
					if (degrees[i] > 1)
						std::cout << "^" << degrees[i];
				}
			}

			firstTerm = false;
		}
	}

	if (firstTerm)
	{
		std::cout << "0";
	}

	std::cout << std::endl;
}


double MultivariatePolynomial::evaluate_horner(const std::vector<double>& variables) const {

	if (!validateVariables(variables))
	{
		throw std::invalid_argument("Error: The number of variables in the input vector does not match the number of variables in the polynomial.");
	}

	double result = 0.0;

	for (const auto& term : coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;

		double term_value = coef;


		for (size_t i = 0; i < powers.size(); ++i)
		{
			term_value *= std::pow(variables[i], powers[i]);
		}

		result += term_value;
	}

	return result;
}


int MultivariatePolynomial::getDegree() const {
	int max_degree = 0;


	for (const auto& term : coefficients)
	{
		const std::vector<int>& powers = term.first;
		int term_degree = std::accumulate(powers.begin(), powers.end(), 0);

		if (term_degree > max_degree)
		{
			max_degree = term_degree;
		}
	}

	return max_degree;
}


double MultivariatePolynomial::getCoefficient(const std::vector<int>& powers) const {
	auto it = coefficients.find(powers);
	if (it != coefficients.end())
	{
		return it->second;
	}
	return 0.0;
}


void MultivariatePolynomial::setCoefficient(const std::vector<int>& powers, double value) {

	if (value == 0.0)
	{
		coefficients.erase(powers);
	}
	else
	{
		coefficients[powers] = value;
	}
}


bool MultivariatePolynomial::isZero() const {
	for (const auto& term : coefficients)
	{
		if (term.second != 0.0)
		{
			return false;
		}
	}
	return true;
}


bool MultivariatePolynomial::validateVariables(const std::vector<double>& variables) const
{

	size_t num_variables = coefficients.begin()->first.size();
	if (variables.size() != num_variables)
	{
		return false;
	}
	return true;
}


MultivariatePolynomial MultivariatePolynomial::sqrt() const {
	if (this->isZero())
	{
		return MultivariatePolynomial();
	}

	// Определяем количество переменных (размерность)
	int num_vars = coefficients.begin()->first.size();
	std::vector<int> alphas(num_vars - 1, 0); // Храним alpha для каждой переменной

	std::vector<std::pair<std::vector<int>, double>> transformed_coefficients(coefficients.begin(), coefficients.end());

	// Поочередно заменяем переменные (кроме последней)
	for (int var = 1; var < num_vars; ++var)
	{
		// Определяем максимальную степень текущей первой переменной (a)
		int max_degree = 0;
		for (const auto& term : transformed_coefficients)
		{
			max_degree = std::max(max_degree, term.first[0]);
		}

		// Вычисляем alpha
		alphas[var - 1] = (max_degree / 2) + 1;
		int alpha = alphas[var - 1];

		std::cout << "Alpha[" << var - 1 << "]: " << alpha << std::endl;

		// Подставляем x[var] = a^alpha
		std::vector<std::pair<std::vector<int>, double>> new_coeffs;
		for (const auto& term : transformed_coefficients)
		{
			std::vector<int> new_powers = term.first;
			int a_exp = new_powers[0];  // Степень a
			int x_exp = new_powers[var]; // Степень заменяемой переменной

			// Преобразуем x[var] = a^(alpha * x_exp)
			int new_a_exp = a_exp + (x_exp * alpha);

			// Обновляем степени
			new_powers[0] = new_a_exp; // a принимает новую степень
			new_powers[var] = 0;       // Убираем x[var]

			new_coeffs.emplace_back(new_powers, term.second);
		}

		transformed_coefficients = new_coeffs;
	}

	// Новый вектор для хранения нормализованных коэффициентов
	std::vector<std::pair<std::vector<int>, double>> new_coeffs;
	/*std::cout << "Before normalize: " << std::endl;
	printVector(transformed_coefficients);*/

	// Проходим по всем термам
	for (const auto& term : transformed_coefficients)
	{
		const auto& powers = term.first;
		double coef = term.second;

		bool found = false;

		// Ищем, есть ли уже такой терм в new_coeffs
		for (auto& existing_term : new_coeffs)
		{
			if (existing_term.first == powers)
			{
				existing_term.second += coef;  // Если нашли, суммируем коэффициенты
				found = true;
				break;
			}
		}

		// Если такого терма нет, добавляем его в new_coeffs
		if (!found)
		{
			new_coeffs.push_back(term);
		}
	}

	// Теперь new_coeffs содержит нормализованные коэффициенты, где одинаковые степени объединены
	std::cout << "Normalized coefficients: " << std::endl;
	printVector(new_coeffs);  // Выводим нормализованные коэффициенты

	// Создаем одномерный многочлен от a
	int max_degree_a = 0;
	for (const auto& term : new_coeffs)
	{
		max_degree_a = std::max(max_degree_a, term.first[0]); // Берем степень a
	}

	// Создаем вектор коэффициентов для одномерного многочлена
	std::vector<double> univariate_coeffs(max_degree_a + 1, 0.0);

	// Заполняем вектор коэффициентов, теперь с учетом нормализации
	for (const auto& term : new_coeffs)
	{
		int a_exp = term.first[0];
		univariate_coeffs[a_exp] = term.second;
	}

	// Строим одномерный многочлен и извлекаем квадратный корень
	UnivariatePolynomial univariatePoly(univariate_coeffs);
	std::cout << "Univariate polynomial before sqrt: ";
	univariatePoly.print();

	// Извлекаем квадратный корень
	UnivariatePolynomial sqrtUnivariatePoly = univariatePoly.sqrt();
	std::cout << "Univariate polynomial after sqrt: ";
	sqrtUnivariatePoly.print();

	// Восстанавливаем степени (обратное преобразование)
	MultivariatePolynomial result;
	const auto& coeffs = sqrtUnivariatePoly.getCoefficients();
	for (size_t i = 0; i < coeffs.size(); ++i)
	{
		double coef = coeffs[i];

		// Восстанавливаем степени для каждой переменной
		std::vector<int> restored_powers(num_vars, 0);
		int remaining = i;
		for (int var = num_vars - 2; var >= 0; --var)
		{
			restored_powers[var + 1] = remaining / alphas[var];
			remaining = remaining % alphas[var];
		}
		restored_powers[0] = remaining;

		result.setCoefficient(restored_powers, coef);
	}

	std::cout << "Final restored MultivariatePolynomial: ";
	result.print();

	return result;
}


MultivariatePolynomial MultivariatePolynomial::operator+(const MultivariatePolynomial& other) const {

	MultivariatePolynomial result;

	for (const auto& term : this->coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;
		result.setCoefficient(powers, coef);
	}

	for (const auto& term : other.coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;

		double currentCoef = result.getCoefficient(powers);
		result.setCoefficient(powers, currentCoef + coef);
	}

	return result;
}


MultivariatePolynomial MultivariatePolynomial::operator-(const MultivariatePolynomial& other) const {

	MultivariatePolynomial result;


	for (const auto& term : this->coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;
		result.setCoefficient(powers, coef);
	}


	for (const auto& term : other.coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;


		double currentCoef = result.getCoefficient(powers);
		result.setCoefficient(powers, currentCoef - coef);
	}

	return result;
}


MultivariatePolynomial MultivariatePolynomial::operator*(const MultivariatePolynomial& other) const {
	MultivariatePolynomial result;


	for (const auto& term1 : this->coefficients)
	{
		const std::vector<int>& powers1 = term1.first;
		double coef1 = term1.second;


		for (const auto& term2 : other.coefficients)
		{
			const std::vector<int>& powers2 = term2.first;
			double coef2 = term2.second;


			double newCoef = coef1 * coef2;


			std::vector<int> newPowers;
			for (size_t i = 0; i < powers1.size(); ++i)
			{
				newPowers.push_back(powers1[i] + powers2[i]);
			}


			double currentCoef = result.getCoefficient(newPowers);
			result.setCoefficient(newPowers, currentCoef + newCoef);
		}
	}

	return result;
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

std::pair<MultivariatePolynomial, MultivariatePolynomial> MultivariatePolynomial::operator/(const MultivariatePolynomial& other) const {
	MultivariatePolynomial quotient;
	MultivariatePolynomial remainder = *this;


	if (other.isZero())
	{
		throw std::invalid_argument("Cannot divide by zero polynomial.");
	}


	while (!remainder.isZero() && remainder.getDegree() >= other.getDegree())
	{

		auto highestTermRemainder = remainder.coefficients.rbegin();
		auto highestTermOther = other.coefficients.rbegin();

		std::vector<int> powersRemainder = highestTermRemainder->first;
		double coefRemainder = highestTermRemainder->second;

		std::vector<int> powersOther = highestTermOther->first;
		double coefOther = highestTermOther->second;


		if (coefRemainder == 0 || coefOther == 0 || powersRemainder.size() != powersOther.size())
		{
			throw std::invalid_argument("Cannot divide: incompatible degrees or zero coefficients.");
		}


		double newCoef = coefRemainder / coefOther;
		std::vector<int> newPowers;
		for (size_t i = 0; i < powersRemainder.size(); ++i)
		{
			newPowers.push_back(powersRemainder[i] - powersOther[i]);
		}

		quotient.setCoefficient(newPowers, newCoef);

		MultivariatePolynomial termToSubtract;
		termToSubtract.setCoefficient(newPowers, newCoef);

		remainder = remainder - (other * termToSubtract);
	}

	return std::make_pair(quotient, remainder);
}