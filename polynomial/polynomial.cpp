#include <iostream>
#include <map>
#include <string>
#include <cctype>

void parseTerm(const std::string& term, std::map<int, int>& poly) {
    int coef = 0;
    int power = 0;
    int i = 0;

    while (i < (int)term.size() && isdigit(term[i])) {
        coef = coef * 10 + (term[i] - '0');
        i++;
    }

    if (coef == 0)
        coef = 1;

    if (i == term.size()) {
        poly[0] += coef;
        return;
    }

    i++;

    if (i < (int)term.size() && term[i] == '^') {
        i++;
        while (i < (int)term.size()) {
            power = power * 10 + (term[i] - '0');
            i++;
        }
    } else {
        power = 1;
    }

    poly[power] += coef;
}

void printPolynomial(const std::map<int, int>& poly) {
    bool first = true;

    for (auto it = poly.rbegin(); it != poly.rend(); ++it) {
        int power = it->first;
        int coef  = it->second;

        if (coef == 0) {
            continue;
        }

        if (!first)
            std::cout << " + ";
        first = false;

        if (power == 0) {
            std::cout << coef;
        } else {
            if (coef != 1) {
                std::cout << coef;
            }
            std::cout << "x";
            if (power != 1) {
                std::cout << "^" << power;
            }
        }
    }

    if (first) {
        std::cout << "0";
    }

    std::cout << std::endl;
}

int main() {
    std::map<int, int> poly;
    std::string term;

    std::cout << "Enter polynomial terms (end with Ctrl+D):\n";
    
    while (std::cin >> term) {
        parseTerm(term, poly);
    }

    printPolynomial(poly);
    return 0;
}