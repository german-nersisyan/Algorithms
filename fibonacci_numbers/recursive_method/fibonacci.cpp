#include <iostream>

int fibonacci(int n)
{
    if(n == 0) {
        return 0;
    }
    if(n == 1) {
        return 1;
    }
    
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    int n;
    std::cout << "Enter the index of the Fibonacci number ";
    std::cin >> n;
    while(n < 0) {
        std::cout << "Invalid input. Please enter a non-negative number ";
        std::cin >> n;
    }
    int result = fibonacci(n);
    std::cout << "The " << n << "th Fibonacci number is " << result << std::endl;
    return 0;
}