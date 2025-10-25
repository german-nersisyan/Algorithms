#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
#include <cmath>
#include <cctype>

bool isoperand(char c) {
    return std::isdigit(c) || std::isalpha(c);
}

bool isoperator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '/':
        case '*':
        case '^':
            return true;
    }
    return false;
}

int priority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '/':
        case '*':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

std::string infixtopostfix(const std::string& infix) {
    std::stack<char> st;
    std::string postfix;
    std::string currentNumber;

    for (char c : infix) {
        if (std::isspace(c)) {
            continue;
        }

        if (std::isdigit(c)) {
            currentNumber += c;
        }
        else {
            if (!currentNumber.empty()) {
                postfix += currentNumber + ' ';
                currentNumber.clear();
            }

            if (isoperand(c)) {
                postfix += c;
            }
            else if (c == '(') {
                st.push(c);
            }
            else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    st.pop();
                }
                if (st.empty()) {
                    throw std::runtime_error("Error: Mismatched parentheses");
                }
                st.pop();
            }
            else if (isoperator(c)) {
                while (!st.empty() && priority(c) <= priority(st.top())) {
                    postfix += st.top();
                    st.pop();
                }
                st.push(c);
            }
            else {
                throw std::runtime_error(std::string("Error: Invalid character '") + c + "'");
            }
        }
    }

    if (!currentNumber.empty()) {
        postfix += currentNumber + ' ';
    }

    while (!st.empty()) {
        if (st.top() == '(' || st.top() == ')') {
            throw std::runtime_error("Error: Mismatched parentheses");
        }
        postfix += st.top();
        st.pop();
    }

    if (postfix.empty()) {
        throw std::runtime_error("Error: Empty or invalid input");
    }

    return postfix;
}

double evaluatePostfix(const std::string& postfix) {
    std::stack<double> st;
    std::string currentNumber;

    for (char c : postfix) {
        if (std::isdigit(c)) {
            currentNumber += c;
        }
        else if (c == ' ' && !currentNumber.empty()) {
            st.push(std::stod(currentNumber));
            currentNumber.clear();
        }
        else if (isoperator(c)) {
            if (st.size() < 2) {
                throw std::runtime_error("Error: Invalid expression.");
            }

            double b = st.top();
            st.pop();
            double a = st.top();
            st.pop();

            switch (c) {
                case '+': 
                    st.push(a + b); break;
                case '-':
                    st.push(a - b); break;
                case '*': 
                    st.push(a * b); break;
                case '/': 
                    if (b == 0) {
                        throw std::runtime_error("Error: Division by zero.");
                    }
                    st.push(a / b); break;
                case '^': 
                    st.push(std::pow(a, b)); break;
                default: 
                    throw std::runtime_error("Error: Invalid operator.");
            }
        }
    }

    if (st.size() != 1) {
        throw std::runtime_error("Error: Invalid postfix expression.");
    }

    return st.top();
}

int main() {
    try {
        std::string str = "(10+5)*(2+3)";
        std::string postfix = infixtopostfix(str);
        std::cout << "Postfix: " << postfix << std::endl;
        std::cout << "Result: " << evaluatePostfix(postfix) << std::endl;

        str = "100+5";
        postfix = infixtopostfix(str);
        std::cout << "Postfix: " << postfix << std::endl;
        std::cout << "Result: " << evaluatePostfix(postfix) << std::endl;

        str = "10*5+3^2";
        postfix = infixtopostfix(str);
        std::cout << "Postfix: " << postfix << std::endl;
        std::cout << "Result: " << evaluatePostfix(postfix) << std::endl;

        str = "3000+5*(2^3)";
        postfix = infixtopostfix(str);
        std::cout << "Postfix: " << postfix << std::endl;
        std::cout << "Result: " << evaluatePostfix(postfix) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}