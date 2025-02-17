#include <iostream>
#include <vector>
#include <map>
#include <cmath>

class MultivariatePolynomial {
public:
    // �����������, ����������� ������������ ��� ������, ��� ������ ������� - ��� ���� (�������, �����������)
    MultivariatePolynomial(const std::vector<std::pair<std::vector<int>, double>>& terms) {
        for (const auto& term : terms) {
            coefficients[term.first] = term.second;
        }
    }

    // ����� ��� ������ ����������
    void print() const {
        bool firstTerm = true; // ����, ����� �� �������� ���� "+" � ������

        // ���������� ����� � ������� �������� �������� (�� �������)
        for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
            const auto& degrees = it->first;
            double coef = it->second;

            if (coef != 0.0) { // ���������� ����� � ������������� 0
                if (!firstTerm) {  // ������ ����� ������� �����
                    if (coef > 0.0)
                        std::cout << " + ";
                    else
                        std::cout << " - ";
                    coef = std::abs(coef);
                }
                else if (coef < 0.0) {  // ��� ������� �������������� �����
                    std::cout << " - ";
                    coef = std::abs(coef);
                }

                // ������� ����������� (���� �� 1)
                if (std::abs(coef - 1.0) > 1e-6 || degrees == std::vector<int>(degrees.size(), 0)) {
                    std::cout << coef;
                }

                // ������� ������� ��� ������ ����������
                for (size_t i = 0; i < degrees.size(); ++i) {
                    if (degrees[i] > 0) {
                        std::cout << char('a' + i); // ����������, ��������, 'a', 'b', 'c', ...
                        if (degrees[i] > 1)
                            std::cout << "^" << degrees[i];
                    }
                }

                firstTerm = false;  // ����� ������� ����� ������ �� ������� ����
            }
        }

        // ���� ������ �� ����������, ������ ��� ����
        if (firstTerm) {
            std::cout << "0";
        }

        std::cout << std::endl;
    }

private:
    std::map<std::vector<int>, double> coefficients;
};

int main() {
    // ������ 1: 3a^2 + 2b^2 + 5c + 4
    std::vector<std::pair<std::vector<int>, double>> terms1 = {
        {{2, 0, 0}, 3.0},  // 3a^2
        {{0, 2, 0}, 2.0},  // 2b^2
        {{0, 0, 1}, 5.0},  // 5c
        {{0, 0, 0}, 4.0}   // 4 (��������� ����)
    };
    MultivariatePolynomial poly1(terms1);
    poly1.print();  // ��������� �����: 3a^2 + 2b^2 + 5c + 4

    // ������ 2: 4x^3 + 3x^2y + 2xy^2 + y^3
    std::vector<std::pair<std::vector<int>, double>> terms2 = {
        {{3, 0}, 4.0},  // 4x^3
        {{2, 1}, 3.0},  // 3x^2y
        {{1, 2}, 2.0},  // 2xy^2
        {{0, 3}, 1.0}   // y^3
    };
    MultivariatePolynomial poly2(terms2);
    poly2.print();  // ��������� �����: 4x^3 + 3x^2y + 2xy^2 + y^3

    // ������ 3: 7a^3 + 2b^3 + 3c^2 + 8d
    std::vector<std::pair<std::vector<int>, double>> terms3 = {
        {{3, 0, 0,0}, 7.0},  // 7a^3
        {{0, 3, 0,0}, 2.0},  // 2b^3
        {{0, 0, 2,0}, 3.0},  // 3c^2
        {{0, 0, 0, 1}, 8.0}   // 8d
    };
    MultivariatePolynomial poly3(terms3);
    poly3.print();  // ��������� �����: 7a^3 + 2b^3 + 3c^2 + 8

    // ������ 4: x^2y + xy^2 + 2xy + 1
    std::vector<std::pair<std::vector<int>, double>> terms4 = {
        {{2, 1}, 1.0},  // x^2y
        {{1, 2}, 1.0},  // xy^2
        {{1, 1}, 2.0},  // 2xy
        {{0, 0}, 1.0}   // 1 (��������� ����)
    };
    MultivariatePolynomial poly4(terms4);
    poly4.print();  // ��������� �����: x^2y + xy^2 + 2xy + 1

    // ������ 5: 6a^2 + 4b^2 + 3ab + 1
    std::vector<std::pair<std::vector<int>, double>> terms5 = {
        {{2, 0}, 6.0},  // 6a^2
        {{0, 2}, 4.0},  // 4b^2
        {{1, 1}, 3.0},  // 3ab
        {{0, 0}, 1.0}   // 1 (��������� ����)
    };
    MultivariatePolynomial poly5(terms5);
    poly5.print();  // ��������� �����: 6a^2 + 4b^2 + 3ab + 1

    // ������ 6: 10x^2 + 5xy + 4y^2 - 3x + 7
    std::vector<std::pair<std::vector<int>, double>> terms6 = {
        {{2, 0}, 10.0},  // 10x^2
        {{1, 1}, 5.0},   // 5xy
        {{0, 2}, 4.0},   // 4y^2
        {{1, 0}, -3.0},  // -3x
        {{0, 0}, 7.0}    // 7 (��������� ����)
    };
    MultivariatePolynomial poly6(terms6);
    poly6.print();  // ��������� �����: 10x^2 + 5xy + 4y^2 - 3x + 7

    // ������ 7: x^3 - 3x^2y + 4xy - 2y^2 + 6
    std::vector<std::pair<std::vector<int>, double>> terms7 = {
        {{3, 0}, 1.0},   // x^3
        {{2, 1}, -3.0},  // -3x^2y
        {{1, 1}, 4.0},   // 4xy
        {{0, 2}, -2.0},  // -2y^2
        {{0, 0}, 6.0}    // 6 (��������� ����)
    };
    MultivariatePolynomial poly7(terms7);
    poly7.print();  // ��������� �����: x^3 - 3x^2y + 4xy - 2y^2 + 6

    // ������ 8: a^2 + b^2 + c^2
    std::vector<std::pair<std::vector<int>, double>> terms8 = {
        {{2, 0, 0}, 1.0},  // a^2
        {{0, 2, 0}, 1.0},  // b^2
        {{0, 0, 2}, 1.0}   // c^2
    };
    MultivariatePolynomial poly8(terms8);
    poly8.print();  // ��������� �����: a^2 + b^2 + c^2

    // ������ 9: 2ab + 3ac + bc
    std::vector<std::pair<std::vector<int>, double>> terms9 = {
        {{1, 1, 0}, 2.0},  // 2ab
        {{1, 0, 1}, 3.0},  // 3ac
        {{0, 1, 1}, 1.0}   // bc
    };
    MultivariatePolynomial poly9(terms9);
    poly9.print();  // ��������� �����: 2ab + 3ac + bc

    // ������ 10: x^4 + 2x^2y + 3xy^3 - y^4
    std::vector<std::pair<std::vector<int>, double>> terms10 = {
        {{4, 0}, 1.0},    // x^4
        {{2, 1}, 2.0},    // 2x^2y
        {{1, 3}, 3.0},    // 3xy^3
        {{0, 4}, -1.0}    // -y^4
    };
    MultivariatePolynomial poly10(terms10);
    poly10.print();  // ��������� �����: x^4 + 2x^2y + 3xy^3 - y^4

    return 0;
}