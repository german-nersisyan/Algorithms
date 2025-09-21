#include <iostream>

template <typename T>
T power_recursive(T x, int n)
{
    if(n == 0) {
        return 1;
    }
    
    return x*power_recursive(x, n-1);
}

template <typename T>
T power(T x, int n)
{
    int m = n;
    if(n < 0) {
        m = -n;
    }
    
    T result = 1;
    
    if (m % 2 == 1) {
        result = x;
    }
    
    result = result*power_recursive(x*x, m/2);
    
    if(n < 0) {
        result = 1 / result;
    }
    
    return result;
}

int main()
{
    double x; 
    int n;
    std::cout << "Enter the number: "; std::cin >> x;
    std::cout << "Enter the power: "; std::cin >> n;
    double result = power(x, n);
    std::cout << "The " << n << " power of "<< x << " is: "<< result;
    return 0;
}