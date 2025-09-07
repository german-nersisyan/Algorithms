#include <iostream>

template <typename T>
T power(T x, int n) 
{
    int m = n;
    T result = 1;
    
    if(n < 0) {
        m = -n;
    }
    
    for(int i = 0; i < m; i++) {
        result *= x;
    }
    
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