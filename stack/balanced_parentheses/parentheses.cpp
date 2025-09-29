#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

bool areParenthesesBalanced(const std::string value)
{
    std::stack<char> st;
    std::unordered_map<char, char> matchingvalue = 
    {
        { ')', '(' },
        { '}', '{' },
        { ']', '[' }
    };
    
    for(char ch : value) {
        if(ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        }
        
        if(ch == ')' || ch == '}' || ch == ']') {
            if(st.empty() || matchingvalue[ch] != st.top()) {
                return false;
            }
            
            st.pop();
        }
    }
    
    return st.empty();
}

int main() 
{
    std::string s = "{(a + b) * (b + c)} + [c + d]";
    std::cout << s << (areParenthesesBalanced(s) ? " is" : " is not") << " balanced" << std::endl;
    return 0;
}