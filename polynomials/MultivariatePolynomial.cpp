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

MultivariatePolynomial MultivariatePolynomial::operator+(const MultivariatePolynomial& other) const {
	// Новый многочлен для результата
	MultivariatePolynomial result;
	// Проходим по всем членам текущего многочлена
	for (const auto& term : this->coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;
		result.setCoefficient(powers, coef);  // Добавляем в результат текущий член
	}
	// Проходим по всем членам другого многочлена
	for (const auto& term : other.coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;

		// Если такой член уже есть в текущем многочлене, прибавляем коэффициент
		double currentCoef = result.getCoefficient(powers);
		result.setCoefficient(powers, currentCoef + coef);  // Сложение коэффициентов
	}

	return result;
}


MultivariatePolynomial MultivariatePolynomial::operator-(const MultivariatePolynomial& other) const {
	// Новый многочлен для результата
	MultivariatePolynomial result;

	// Проходим по всем членам текущего многочлена
	for (const auto& term : this->coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;
		result.setCoefficient(powers, coef);  // Добавляем текущий член
	}

	// Проходим по всем членам другого многочлена
	for (const auto& term : other.coefficients)
	{
		const std::vector<int>& powers = term.first;
		double coef = term.second;

		// Если такой член уже есть в текущем многочлене, вычитаем его коэффициент
		double currentCoef = result.getCoefficient(powers);
		result.setCoefficient(powers, currentCoef - coef);  // Вычитание коэффициентов
	}

	return result;
}


MultivariatePolynomial MultivariatePolynomial::operator*(const MultivariatePolynomial& other) const {
	MultivariatePolynomial result;  // Новый многочлен для результата

	// Проходим по всем членам текущего многочлена
	for (const auto& term1 : this->coefficients)
	{
		const std::vector<int>& powers1 = term1.first;  // Степени переменных для первого члена
		double coef1 = term1.second;  // Коэффициент первого члена

		// Проходим по всем членам второго многочлена
		for (const auto& term2 : other.coefficients)
		{
			const std::vector<int>& powers2 = term2.first;  // Степени переменных для второго члена
			double coef2 = term2.second;  // Коэффициент второго члена

			// Умножаем коэффициенты
			double newCoef = coef1 * coef2;

			// Складываем степени соответствующих переменных
			std::vector<int> newPowers;
			for (size_t i = 0; i < powers1.size(); ++i)
			{
				newPowers.push_back(powers1[i] + powers2[i]);
			}

			// Добавляем новый член в результат (используем метод setCoefficient)
			double currentCoef = result.getCoefficient(newPowers);
			result.setCoefficient(newPowers, currentCoef + newCoef);  // Сложение коэффициентов для одинаковых степеней
		}
	}

	return result;  // Возвращаем результат
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

// Оператор деления
std::pair<MultivariatePolynomial, MultivariatePolynomial> MultivariatePolynomial::operator/(const MultivariatePolynomial& other) const {
	MultivariatePolynomial quotient;  // Частное
	MultivariatePolynomial remainder = *this;  // Остаток, начинаем с самого делимого

	// Проверяем, что делитель не равен нулю
	if (other.isZero())
	{
		throw std::invalid_argument("Cannot divide by zero polynomial.");
	}

	// Алгоритм деления с остатком
	while (!remainder.isZero() && remainder.getDegree() >= other.getDegree())
	{
		// Получаем старшие члены у делимого и делителя
		auto highestTermRemainder = remainder.coefficients.rbegin();  // Старший член остатка
		auto highestTermOther = other.coefficients.rbegin();  // Старший член делителя

		// Степени и коэффициенты старших членов
		std::vector<int> powersRemainder = highestTermRemainder->first;
		double coefRemainder = highestTermRemainder->second;

		std::vector<int> powersOther = highestTermOther->first;
		double coefOther = highestTermOther->second;

		// Проверка, чтобы деление было возможно
		if (coefRemainder == 0 || coefOther == 0 || powersRemainder.size() != powersOther.size())
		{
			throw std::invalid_argument("Cannot divide: incompatible degrees or zero coefficients.");
		}

		// Вычисление нового члена частного
		double newCoef = coefRemainder / coefOther;
		std::vector<int> newPowers;
		for (size_t i = 0; i < powersRemainder.size(); ++i)
		{
			newPowers.push_back(powersRemainder[i] - powersOther[i]);  // Степени переменных для частного
		}

		// Добавляем этот новый член в частное
		quotient.setCoefficient(newPowers, newCoef);

		// Формируем новый остаток после вычитания
		MultivariatePolynomial termToSubtract;
		termToSubtract.setCoefficient(newPowers, newCoef);

		remainder = remainder - (other * termToSubtract);  // Вычитаем полученный член из остатка
	}

	return std::make_pair(quotient, remainder);  // Возвращаем пару (частное, остаток)
}