#include "UnivariatePolynomial.hpp"
#include <iostream>
#include <stdexcept>
#include "MultivariatePolynomial.hpp"
//TODO:
// evavuate horner +
// operator []
//  basic arithmetic operations + - * \
// change basic methods change return value
// add constructor (const int degree)

int main(void) {

	/*UnivariatePolynomial poly1({ 1,4,10,12,9 });
	std::cout << "First polynomial: ";
	poly1.print();
	std::cout << std::endl;

	UnivariatePolynomial poly2({ 9, -12,4 });
	std::cout << "Second polynomial: ";
	poly2.print();
	std::cout << std::endl;

	UnivariatePolynomial sum = poly1 + poly2;
	std::cout << "Result sum of 2 poly: ";
	sum.print();

	UnivariatePolynomial sub = poly1 - poly2;
	std::cout << "Result sub of 2 poly: ";
	sub.print();

	UnivariatePolynomial mul = poly1 * poly2;
	std::cout << "Result mul of 2 poly: ";
	mul.print();

	std::pair <UnivariatePolynomial, UnivariatePolynomial> divide = poly1 / poly2;
	std::cout << "Result divide of 2 poly: " << std::endl << "Quotient: ";
	divide.first.print();

	std::cout << "Remainder: ";
	divide.second.print();

	std::cout << std::endl;*/

	/*UnivariatePolynomial poly({ 9,-12,10,-4,1 });;
	poly.print();
	std::cout << "Default poly: ";
	poly.print();
	std::cout << "sqrt(poly) is: ";
	auto roots = poly.findRoots();
	roots.print();
	try {
		UnivariatePolynomial poly2({ 1,2,0,1 });
		std::cout << "Default poly: ";
		poly2.print();
		std::cout << "sqrt(poly) is: ";
		auto roots1 = poly2.findRoots();
		roots1.print();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}*/
	// TESTS 
	// Пример 1: 3a^2 + 2b^2 + 5c + 4
	//std::vector<std::pair<std::vector<int>, double>> terms1 = {
	//	{{2, 0, 0}, 3.0},  // 3a^2
	//	{{0, 2, 0}, 2.0},  // 2b^2
	//	{{0, 0, 1}, 5.0},  // 5c
	//	{{0, 0, 0}, 4.0}   // 4 (свободный член)
	//};
	//MultivariatePolynomial poly1(terms1);
	//poly1.print();
	//auto value = poly1.evaluate_horner({ 1,2,3 });
	//std::cout << value << std::endl;
	//std::cout << "Degree is: " << poly1.getDegree() << std::endl;


	//// Пример 2: - 4a^3 + 3a^2b - 2ab^2 + b^3
	//std::vector<std::pair<std::vector<int>, double>> terms2 = {
	//	{{3, 0}, -4.0},  // -4a^3
	//	{{2, 1}, 3.0},  // 3a^2y
	//	{{1, 2}, -2.0},  // 2ab^2
	//	{{0, 3}, 1.0}   // b^3
	//};
	//MultivariatePolynomial poly2(terms2);
	//poly2.print();
	//try
	//{
	//	value = poly2.evaluate_horner({ 1,2,3 });
	//	std::cout << value << std::endl;
	//}
	//catch (std::exception& err)
	//{
	//	std::cout << err.what() << std::endl;
	//}
	//std::cout << "Degree is: " << poly2.getDegree() << std::endl;

	//// Пример 3: 7a^3 + 2b^3 + 3c^2 + 8d
	//std::vector<std::pair<std::vector<int>, double>> terms3 = {
	//	{{3, 0, 0,0}, 7.0},  // 7a^3
	//	{{0, 3, 0,0}, 2.0},  // 2b^3
	//	{{0, 0, 2,0}, 3.0},  // 3c^2
	//	{{0, 0, 0, 1}, 8.0}   // 8d
	//};
	//MultivariatePolynomial poly3(terms3);
	//poly3.print();
	//std::cout << "Degree is: " << poly3.getDegree() << std::endl;

	//// Пример 4: a^2b + ab^2 + 2ab + 1
	//std::vector<std::pair<std::vector<int>, double>> terms4 = {
	//	{{2, 1}, 1.0},  // a^2b
	//	{{1, 2}, 1.0},  // ab^2
	//	{{1, 1}, 2.0},  // 2ab
	//	{{0, 0}, 1.0}   // 1 (свободный член)
	//};
	//MultivariatePolynomial poly4(terms4);
	//poly4.print();
	//std::cout << "Degree is: " << poly4.getDegree() << std::endl;

	//// Пример 5: 6a^2 + 3ab + 4b^2 + 1
	//std::vector<std::pair<std::vector<int>, double>> terms5 = {
	//	{{2, 0}, 6.0},  // 6a^2
	//	{{0, 2}, 4.0},  // 4b^2
	//	{{1, 1}, 3.0},  // 3ab
	//	{{0, 0}, 1.0}   // 1 (свободный член)
	//};
	//MultivariatePolynomial poly5(terms5);
	//poly5.print();
	//std::cout << "Degree is: " << poly5.getDegree() << std::endl;

	//// Пример 6: 10a^2 + 5ab - 3a + 4b^2 + 7
	//std::vector<std::pair<std::vector<int>, double>> terms6 = {
	//	{{2, 0}, 10.0},  // 10a^2
	//	{{1, 1}, 5.0},   // 5ab
	//	{{0, 2}, 4.0},   // 4b^2
	//	{{1, 0}, -3.0},  // -3a
	//	{{0, 0}, 7.0}    // 7 (свободный член)
	//};
	//MultivariatePolynomial poly6(terms6);
	//poly6.print();
	//std::cout << "Degree is: " << poly6.getDegree() << std::endl;

	//// Пример 7: a^3 - 3a^2b + 4ab - 2b^2 + 6
	//std::vector<std::pair<std::vector<int>, double>> terms7 = {
	//	{{3, 0}, 1.0},   // a^3
	//	{{2, 1}, -3.0},  // -3a^2b
	//	{{1, 1}, 4.0},   // 4ab
	//	{{0, 2}, -2.0},  // -2b^2
	//	{{0, 0}, 6.0}    // 6 (свободный член)
	//};
	//MultivariatePolynomial poly7(terms7);
	//poly7.print();
	//std::cout << "Degree is: " << poly7.getDegree() << std::endl;

	//// Пример 8: a^2 + b^2 + c^2
	//std::vector<std::pair<std::vector<int>, double>> terms8 = {
	//	{{2, 0, 0}, 1.0},  // a^2
	//	{{0, 2, 0}, 1.0},  // b^2
	//	{{0, 0, 2}, 1.0}   // c^2
	//};
	//MultivariatePolynomial poly8(terms8);
	//poly8.print();
	//std::cout << "Degree is: " << poly8.getDegree() << std::endl;

	//// Пример 9: 2ab + 3ac + bc
	//std::vector<std::pair<std::vector<int>, double>> terms9 = {
	//	{{1, 1, 0}, 2.0},  // 2ab
	//	{{1, 0, 1}, 3.0},  // 3ac
	//	{{0, 1, 1}, 1.0}   // bc
	//};
	//MultivariatePolynomial poly9(terms9);
	//poly9.print();
	//value = poly9.evaluate_horner({ 1,2,3 });
	//std::cout << "eval horner is: " << value << std::endl;
	//std::cout << "Degree is: " << poly9.getDegree() << std::endl;

	//// Пример 10: a^4 + 2a^2b + 3ab^3 - b^4
	//std::vector<std::pair<std::vector<int>, double>> terms10 = {
	//	{{4, 0}, 1.0},    // a^4
	//	{{2, 1}, 2.0},    // 2a^2b
	//	{{1, 3}, 3.0},    // 3ab^3
	//	{{0, 4}, -1.0}    // -b^4
	//};
	//MultivariatePolynomial poly10(terms10);
	//poly10.print();
	//std::cout << "Degree is: " << poly10.getDegree() << std::endl;
	//std::cout << "Is zero: " << poly10.isZero() << std::endl;  // Вывод: 1 (нулевой многочлен)


	//std::vector<std::pair<std::vector<int>, double>> zero_terms = {
	//{{0, 0, 0}, 0.0},  // 0 (свободный член)
	//{{0, 0, 0}, 0.0},  // 0
	//{{0, 0, 0}, 0.0}   // 0
	//};
	//MultivariatePolynomial zero_poly(zero_terms);
	//std::cout << "Is zero: " << zero_poly.isZero() << std::endl;  // Вывод: 1 (нулевой многочлен)


	//std::vector<std::pair<std::vector<int>, double>> terms = {
	//{{2, 0, 0}, 3.0},  // 3a^2
	//{{0, 2, 0}, 2.0},  // 2b^2
	//{{0, 0, 1}, 5.0}   // 5c
	//};

	//MultivariatePolynomial test_set_get(terms);

	//// Получаем коэффициент для члена a^2
	//std::vector<int> powers1 = { 2, 0, 0 };
	//std::cout << "Coefficient for a^2: " << test_set_get.getCoefficient(powers1) << std::endl;  // 3.0

	//// Получаем коэффициент для члена b^2
	//std::vector<int> powers2 = { 0, 2, 0 };
	//std::cout << "Coefficient for b^2: " << test_set_get.getCoefficient(powers2) << std::endl;  // 2.0

	//// Получаем коэффициент для члена, которого нет (например, для c^3)
	//std::vector<int> powers3 = { 0, 0, 3 };
	//std::cout << "Coefficient for c^3: " << test_set_get.getCoefficient(powers3) << std::endl;  // 0.0

	//// Устанавливаем новый коэффициент для a^3
	//std::vector<int> powers4 = { 3, 0, 0 };
	//test_set_get.setCoefficient(powers4, 7.0);

	//// Проверяем, что новый коэффициент установлен правильно
	//std::cout << "Coefficient for a^3: " << test_set_get.getCoefficient(powers4) << std::endl;  // 7.0

	//// Удаляем коэффициент для b^2
	//test_set_get.setCoefficient(powers2, 0.0);
	//std::cout << "Coefficient for b^2 after removal: " << test_set_get.getCoefficient(powers2) << std::endl;  // 0.0


	//std::vector<std::pair<std::vector<int>, double>> terms_test_equals = {
	//{{2, 0, 0}, 3.0},  // 3a^2
	//{{0, 2, 0}, 2.0},  // 2b^2
	//{{0, 0, 1}, 5.0}   // 5c
	//};
	//MultivariatePolynomial test_poly1(terms_test_equals);

	//std::vector<std::pair<std::vector<int>, double>> terms_test_equals2 = {
	//	{{2, 0, 0}, 3.0},  // 3a^2
	//	{{0, 2, 0}, 2.0},  // 2b^2
	//	{{0, 0, 1}, 5.0}   // 5c
	//};
	//MultivariatePolynomial test_poly2(terms_test_equals2);

	//std::vector<std::pair<std::vector<int>, double>> terms_test_equals3 = {
	//	{{2, 0, 0}, 3.0},  // 3a^2
	//	{{0, 1, 0}, 2.0},  // 2b
	//	{{0, 0, 1}, 5.0}   // 5c
	//};
	//MultivariatePolynomial test_poly3(terms_test_equals3);

	//// Сравниваем многочлены
	//std::cout << (test_poly1 != test_poly2) << std::endl;  // Вывод: 0 (многочлены одинаковые)
	//std::cout << (test_poly1 != test_poly3) << std::endl;  // Вывод: 1 (многочлены разные)
	std::vector<std::pair<std::vector<int>, double>> terms1 = {
		{{2, 0, 0}, 3.0},  // 3a^2
		{{0, 2, 0}, 2.0},  // 2b^2
		{{0, 0, 1}, 5.0}   // 5c
	};

	std::vector<std::pair<std::vector<int>, double>> terms2 = {
		{{2, 0, 0}, 4.0},  // 4a^2
		{{0, 1, 0}, 3.0},  // 3b
		{{0, 0, 1}, 2.0}   // 2c
	};

	MultivariatePolynomial poly1(terms1);
	poly1.print();
	MultivariatePolynomial poly2(terms2);
	poly2.print();

	MultivariatePolynomial sumPoly = poly1 + poly2;
	std::cout << "sum polynomials is: ";
	sumPoly.print();

	MultivariatePolynomial diffPoly = poly1 - poly2;
	std::cout << "diff polynomials is: ";
	diffPoly.print();

	MultivariatePolynomial resultPoly = poly1 * poly2;
	std::cout << "mul polynomials is: ";

	resultPoly.print();

	std::vector<std::pair<std::vector<int>, double>> terms11 = {
	{{3, 2}, 6.0},  // 6a^3b^2
	{{2, 1}, 3.0},  // 3a^2b
	{{1, 2}, 9.0}   // 9ab^2
	};

	std::vector<std::pair<std::vector<int>, double>> terms22 = {
		{{1, 1}, 3.0}   // 3ab
	};


	MultivariatePolynomial poly11(terms11);
	MultivariatePolynomial poly22(terms22);

	// Деление многочленов
	poly11.print();
	poly22.print();
	auto result = poly11 / poly22;

	// Вывод частного и остатка
	std::cout << "Quotient: ";
	result.first.print();
	std::cout << "Remainder: ";
	result.second.print();

	return 0;
}