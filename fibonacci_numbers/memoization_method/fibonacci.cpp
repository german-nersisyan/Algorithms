#include <iostream>
#include <vector>

int fibonacci(int n, std::vector<int>& numbers)
{
    if(numbers[n] != -1) {
        return numbers[n];
    }
    
    numbers[n] = fibonacci(n - 1, numbers) + fibonacci(n - 2, numbers);
    
    return numbers[n];
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
    std::vector<int> numbers(n + 1, -1);
    numbers[0] = 0;
    numbers[1] = 1;
    int result = fibonacci(n, numbers);
    std::cout << "The " << n << "th Fibonacci number is " << result << std::endl;
    return 0;
}