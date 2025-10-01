#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

bool isoperand(char c)
{
    return std::isalpha(c) || std::isdigit(c);
}

bool isoperator(char c)
{
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

int priority(char c)
{
    switch(c) {
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

std::string infixtopostfix(const std::string& infix)
{
    std::stack<char> st;
    std::string postfix;
    
    for(char c : infix) {
        if(std::isspace(c)) {
            continue;
        }
        
        if(isoperand(c)) {
            postfix.push_back(c);
        }
        else if(c == '(') {
            st.push(c);
        }
        else if(c == ')') {
            while(!st.empty() && st.top() != '(') {
                postfix.push_back(st.top());
                st.pop();
            }
            if(st.empty()) {
                throw std::runtime_error("Error: Mismatched parentheses");
            }
            st.pop();
        }
        else if(isoperator(c)) {
            while(!st.empty() && priority(c) <= priority(st.top())) {
                postfix.push_back(st.top());
                st.pop();
            }
            st.push(c);
        }
        else {
            throw std::runtime_error(std::string("Error: Invalid character '") + c + "'");
        }
    }
    
    while(!st.empty()) {
        if(st.top() == '(' || st.top() == ')') {
            throw std::runtime_error("Error: Mismatched parentheses");
        }
        postfix.push_back(st.top());
        st.pop();
    }
    
    if(postfix.empty()) {
        throw std::runtime_error("Error: Empty or invalid input");
    }
    
    return postfix;
}

int main()
{
    try {
        std::string str = "(a+b)*(c+d)";
        std::string newstr = infixtopostfix(str);
    
        std::cout << newstr << std::endl;
    
        str = "a*b+c";
        newstr = infixtopostfix(str);
    
        std::cout << newstr << std::endl;
    
        str = "a*(b+c";
        newstr = infixtopostfix(str);
    
        std::cout << newstr << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}