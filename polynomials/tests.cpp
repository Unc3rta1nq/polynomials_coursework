#include "UnivariatePolynomial.hpp"
#include "MultivariatePolynomial.hpp"
#include <iostream>
#include <cassert>
#include <stdexcept>

// Вспомогательная функция для проверки результата с погрешностью
static void assertApprox(double actual, double expected, const std::string& testName) {
    if (std::abs(actual - expected) < 1e-6)
    {
        std::cout << testName << ": PASSED\n";
    }
    else
    {
        std::cout << testName << ": FAILED (expected " << expected << ", got " << actual << ")\n";
    }
}

// Тесты для UnivariatePolynomial
static void testUnivariateBasics() {
    std::cout << "--- UnivariatePolynomial Basics ---\n";

    // Тест 1: Арифметика
    UnivariatePolynomial poly1({ 1, 4, 10, 12, 9 }); // 9x^4 + 12x^3 + 10x^2 + 4x + 1
    UnivariatePolynomial poly2({ 9, -12, 4 });       // 4x^2 - 12x + 9
    std::cout << "poly1: "; poly1.print();
    std::cout << "poly2: "; poly2.print();

    UnivariatePolynomial sum = poly1 + poly2;
    std::cout << "Sum: "; sum.print();

    UnivariatePolynomial sub = poly1 - poly2;
    std::cout << "Sub: "; sub.print();

    UnivariatePolynomial mul = poly1 * poly2;
    std::cout << "Mul: "; mul.print();

    auto div = poly1 / poly2;
    std::cout << "Div Quotient: "; div.first.print();
    std::cout << "Div Remainder: "; div.second.print();
}

static void testUnivariateSqrt() {
    std::cout << "--- UnivariatePolynomial Sqrt ---\n";

    // Тест 2: Корень из многочлена (x^2 + 2x + 1) = (x + 1)^2
    UnivariatePolynomial poly({ 1, 2, 1 });
    std::cout << "Poly: "; poly.print();
    try
    {
        auto sqrtPoly = poly.sqrt();
        std::cout << "Sqrt: "; sqrtPoly.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Тест 3: Корень из несовершенного квадрата
    UnivariatePolynomial poly2({ 1, 2, 0, 1 });
    std::cout << "Poly (not a square): "; poly2.print();
    try
    {
        auto sqrtPoly2 = poly2.sqrt();
        std::cout << "Sqrt: "; sqrtPoly2.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Тест 4: Сложный многочлен (x^2 + 2x + 1)^2
    UnivariatePolynomial poly3({ 9, -12, 10, -4, 1 }); // x^4 - 4x^3 + 10x^2 - 12x + 9
    std::cout << "Poly: "; poly3.print();
    try
    {
        auto sqrtPoly3 = poly3.sqrt();
        std::cout << "Sqrt: "; sqrtPoly3.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Тест 5: Очень длинный многочлен (проверка больших степеней)
    UnivariatePolynomial test_poly({ 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
    std::cout << "Complex Poly: "; test_poly.print();
    try
    {
        auto sqrtPoly4 = test_poly.sqrt();
        std::cout << "Sqrt: "; sqrtPoly4.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Тесты для MultivariatePolynomial
static void testMultivariateBasics() {
    std::cout << "--- MultivariatePolynomial Basics ---\n";

    // Тест 6: Арифметика
    MultivariatePolynomial p1({ {{2, 0, 0}, 3}, {{0, 2, 0}, 2}, {{0, 0, 1}, 5} }); // 3a^2 + 2b^2 + 5c
    MultivariatePolynomial p2({ {{2, 0, 0}, 4}, {{0, 1, 0}, 3}, {{0, 0, 1}, 2} }); // 4a^2 + 3b + 2c
    std::cout << "p1: "; p1.print();
    std::cout << "p2: "; p2.print();

    MultivariatePolynomial sum = p1 + p2;
    std::cout << "Sum: "; sum.print();

    MultivariatePolynomial diff = p1 - p2;
    std::cout << "Diff: "; diff.print();

    MultivariatePolynomial mul = p1 * p2;
    std::cout << "Mul: "; mul.print();

    // Тест 7: Деление
    MultivariatePolynomial p11({ {{3, 2}, 6}, {{2, 1}, 3}, {{1, 2}, 9} }); // 6a^3b^2 + 3a^2b + 9ab^2
    MultivariatePolynomial p22({ {{1, 1}, 3} });                           // 3ab
    std::cout << "p11: "; p11.print();
    std::cout << "p22: "; p22.print();
    auto div = p11 / p22;
    std::cout << "Div Quotient: "; div.first.print();
    std::cout << "Div Remainder: "; div.second.print();
}

static void testMultivariateEvaluate() {
    std::cout << "--- MultivariatePolynomial Evaluate ---\n";

    // Тест 8: Вычисление значения
    MultivariatePolynomial p1({ {{2, 1}, 3}, {{0, 1}, -2}, {{0, 0}, 1} }); // 3a^2b - 2b + 1
    std::cout << "p1: "; p1.print();
    double result1 = p1.evaluate({ 2.0, 3.0 });
    std::cout << "Evaluate at (a=2, b=3): " << result1 << std::endl;
    assertApprox(result1, 31.0, "Test p1 evaluate");

    MultivariatePolynomial p2({ {{0, 0, 0}, 5} }); // 5
    std::cout << "p2: "; p2.print();
    double result2 = p2.evaluate({ 1.0, -1.0, 0.0 });
    std::cout << "Evaluate at (a=1, b=-1, c=0): " << result2 << std::endl;
    assertApprox(result2, 5.0, "Test p2 evaluate");

    MultivariatePolynomial p3({ {{3, 2}, 1}, {{1, 0}, -4}, {{0, 5}, 1} }); // a^3b^2 - 4a + b^5
    std::cout << "p3: "; p3.print();
    double result3 = p3.evaluate({ 2.0, 1.5 });
    std::cout << "Evaluate at (a=2, b=1.5): " << result3 << std::endl;
    assertApprox(result3, 17.59375, "Test p3 evaluate");

    // Тест 9: Вычисление для другого многочлена
    MultivariatePolynomial p4({ {{1, 1, 0}, 2}, {{1, 0, 1}, 3}, {{0, 1, 1}, 1} }); // 2ab + 3ac + bc
    std::cout << "p4: "; p4.print();
    double result4 = p4.evaluate({ 1.0, 2.0, 3.0 });
    std::cout << "Evaluate at (a=1, b=2, c=3): " << result4 << std::endl;
    assertApprox(result4, 15.0, "Test p4 evaluate"); // 2*1*2 + 3*1*3 + 1*2*3 = 4 + 9 + 6 = 15
}

static void testMultivariateSqrt() {
    std::cout << "--- MultivariatePolynomial Sqrt ---\n";

    // Тест 10: Корень из (2a + b)^2 = 4a^2 + 4ab + b^2
    MultivariatePolynomial poly({ {{2, 0}, 4}, {{1, 1}, 4}, {{0, 2}, 1} });
    std::cout << "Poly: "; poly.print();
    try
    {
        auto sqrtPoly = poly.sqrt();
        std::cout << "Sqrt: "; sqrtPoly.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Тест 11: Корень из a^4b^2
    MultivariatePolynomial poly2({ {{4, 2}, 1} });
    std::cout << "Poly: "; poly2.print();
    try
    {
        auto sqrtPoly2 = poly2.sqrt();
        std::cout << "Sqrt: "; sqrtPoly2.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Тест 12: Сложный многочлен с несколькими переменными
    MultivariatePolynomial poly3({
        {{4, 0, 0}, 1}, {{2, 1, 0}, 2}, {{2, 0, 3}, 2},
        {{0, 2, 0}, 1}, {{0, 1, 3}, 2}, {{0, 0, 6}, 1}
        });
    std::cout << "Poly: "; poly3.print();
    try
    {
        auto sqrtPoly3 = poly3.sqrt();
        std::cout << "Sqrt: "; sqrtPoly3.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

static void testMultivariateAdvanced() {
    std::cout << "--- MultivariatePolynomial Advanced ---\n";

    // Тест 13: Корень из (a + b + c + d)^2
    MultivariatePolynomial poly({
        {{2, 0, 0, 0}, 1}, {{1, 1, 0, 0}, 2}, {{1, 0, 1, 0}, 2}, {{1, 0, 0, 1}, 2},
        {{0, 2, 0, 0}, 1}, {{0, 1, 1, 0}, 2}, {{0, 1, 0, 1}, 2}, {{0, 0, 2, 0}, 1},
        {{0, 0, 1, 1}, 2}, {{0, 0, 0, 2}, 1}
        });
    std::cout << "Poly: "; poly.print();
    try
    {
        auto sqrtPoly = poly.sqrt();
        std::cout << "Sqrt: "; sqrtPoly.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Тест 14: Очень сложный многочлен с 6 переменными
    MultivariatePolynomial poly2({
        {{2, 0, 0, 0, 0, 0}, 1}, {{1, 1, 0, 0, 0, 0}, 2}, {{1, 0, 1, 0, 0, 0}, 2},
        {{1, 0, 0, 1, 0, 0}, 2}, {{1, 0, 0, 0, 0, 1}, 4000}, {{0, 2, 0, 0, 0, 0}, 1},
        {{0, 1, 1, 0, 0, 0}, 2}, {{0, 1, 0, 1, 0, 0}, 2}, {{0, 1, 0, 0, 0, 1}, 4000},
        {{0, 0, 2, 0, 0, 0}, 1}, {{0, 0, 1, 1, 0, 0}, 2}, {{0, 0, 1, 0, 0, 1}, 4000},
        {{0, 0, 0, 2, 0, 0}, 1}, {{0, 0, 0, 1, 0, 1}, 4000}, {{0, 0, 0, 0, 0, 2}, 4000000}
        });
    std::cout << "Poly: "; poly2.print();
    try
    {
        auto sqrtPoly2 = poly2.sqrt();
        std::cout << "Sqrt: "; sqrtPoly2.print();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Тест 15: Проверка isZero
    MultivariatePolynomial zeroPoly({ {{0, 0, 0}, 0}, {{0, 0, 0}, 0}, {{0, 0, 0}, 0} });
    std::cout << "Zero Poly: "; zeroPoly.print();
    std::cout << "Is zero: " << (zeroPoly.isZero() ? "Yes" : "No") << std::endl;

    // Тест 16: Геттеры и сеттеры
    MultivariatePolynomial testSetGet({ {{2, 0, 0}, 3}, {{0, 2, 0}, 2}, {{0, 0, 1}, 5} });
    std::cout << "Initial: "; testSetGet.print();
    std::cout << "Coefficient a^2: " << testSetGet.getCoefficient({ 2, 0, 0 }) << std::endl;
    testSetGet.setCoefficient({ 3, 0, 0 }, 7.0);
    std::cout << "After set a^3 = 7: "; testSetGet.print();
    testSetGet.setCoefficient({ 0, 2, 0 }, 0.0);
    std::cout << "After remove b^2: "; testSetGet.print();

    // Тест 17: Сравнение многочленов
    MultivariatePolynomial eq1({ {{2, 0, 0}, 3}, {{0, 2, 0}, 2}, {{0, 0, 1}, 5} });
    MultivariatePolynomial eq2({ {{2, 0, 0}, 3}, {{0, 2, 0}, 2}, {{0, 0, 1}, 5} });
    MultivariatePolynomial eq3({ {{2, 0, 0}, 3}, {{0, 1, 0}, 2}, {{0, 0, 1}, 5} });
    std::cout << "eq1: "; eq1.print();
    std::cout << "eq2: "; eq2.print();
    std::cout << "eq3: "; eq3.print();
    std::cout << "eq1 == eq2: " << (eq1 != eq2 ? "No" : "Yes") << std::endl;
    std::cout << "eq1 != eq3: " << (eq1 != eq3 ? "Yes" : "No") << std::endl;
}

// Главная функция для запуска тестов
static void runTests() {
    testUnivariateBasics();
    testUnivariateSqrt();
    testMultivariateBasics();
    testMultivariateEvaluate();
    testMultivariateSqrt();
    testMultivariateAdvanced();
    std::cout << "All tests completed!\n";
}