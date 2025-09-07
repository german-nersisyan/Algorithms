#include <iostream>

template <typename T>
T power(T x, int n) 
{
    if(n == 0) {
        return 1;
    }
    else if(n > 0) {
        return x * power(x, n-1);
    }
    
    else if(n < 0) {
        return 1 / (x * power(x, -n-1));
    }
    
    return 1;
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