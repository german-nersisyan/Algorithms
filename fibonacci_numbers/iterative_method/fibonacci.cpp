#include <iostream>

int fibonacci(int n)
{
    int previous = 0;
    int next = 1;
    
    if(n == 0) {
        return previous;
    }
    if(n == 1) {
        return next;
    }
    
    int current;
    
    for(int i = 0; i < n - 1; i++) {
        current = next;
        next += previous;
        previous = current;
    }
    
    return next;
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