#include <iostream>
#include <stack>
#include <string>
#include <vector>

template <typename T>
bool isPalindrome(const T& value)
{
    auto first = std::begin(value);
    auto last = std::end(value);
    
    size_t size = std::distance(first, last);
    
    if(size <= 1) {
        return true;
    }
    
    std::stack<typename T::value_type> st;
    auto it = first;
    
    for(size_t i = 0; i < size / 2; i++) {
        st.push(*it);
        it++;
    }
    
    if(size % 2 != 0) {
        it++;
    }
    
    while(!st.empty()) {
        if(st.top() != *it) {
            return false;
        }
        st.pop();
        it++;
    }
    
    return true;
}

template <>
bool isPalindrome<int> (const int& value)
{
    std::string s = std::to_string(value);
    return isPalindrome(s);
}

int main()
{
    std::string s = "madam";
    int number = 12321;
    std::vector<int> v = {1, 2, 3, 2, 1};
    int number2 = 1;
    std::vector<int> v2 = {1, 2, 3, 3, 1};
    std::string s2 = "apple";

    std::cout << s << (isPalindrome(s) ? " is" : " is not") << " a palindrome.\n";
    std::cout << number << (isPalindrome(number) ? " is" : " is not") << " a palindrome.\n";
    std::cout << "Vector " << (isPalindrome(v) ? "is" : "is not") << " a palindrome.\n";
    std::cout << number2 << (isPalindrome(number) ? " is" : " is not") << " a palindrome.\n";
    std::cout << "Vector2 " << (isPalindrome(v2) ? "is" : "is not") << " a palindrome.\n";
    std::cout << s2 << (isPalindrome(s2) ? " is" : " is not") << " a palindrome.\n";
    return 0;
}