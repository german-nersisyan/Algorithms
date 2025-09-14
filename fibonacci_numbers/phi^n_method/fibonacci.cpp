#include <iostream>
#include <cmath>

double fibonacci(int n)
{
    double phi = (1 + sqrt(5)) / 2;
    double psi = (1 - sqrt(5)) / 2;
    
    int m = n;
    
    double phi_result = 1;
    double psi_result = 1;
    if(m%2 == 1) {
        phi_result = phi;
        psi_result = psi;
    }
    
    m = m/2;
    double phi_square = phi*phi;
    double psi_square = psi*psi;
    for(int i = 0; i < m; i++) {
        phi_result *= phi_square;
        psi_result *= psi_square;
    }
    
    double result = (phi_result - psi_result) * sqrt(5) / 5;
    
    return result;
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
    double result = fibonacci(n);
    std::cout << "The " << n << "th Fibonacci number is " << result << std::endl;
    return 0;
}