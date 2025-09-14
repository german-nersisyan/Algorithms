#include <iostream>
#include <vector>

std::vector<std::vector<int>> multiplication(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
    std::vector<std::vector<int>> result(2, std::vector<int>(2));
    result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
    return result;
}

int fibonacci(int n)
{
    if(n == 0) {
        return 0;
    }
    if(n == 1) {
        return 1;
    }
    
    std::vector<std::vector<int>> matrix = {{1, 1}, {1, 0}};
    
    std::vector<std::vector<int>> result = {{1, 0}, {0, 1}};
 
    for(int i = 0; i < n; i++) {
       result = multiplication(result, matrix); 
    }
    
    std::vector<std::vector<int>> final_result(2, std::vector<int>(1));
    final_result[0][0] = result[0][0]*1 + result[0][1]*0;
    final_result[1][0] = result[1][0]*1 + result[1][1]*0;
    return final_result[1][0];
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