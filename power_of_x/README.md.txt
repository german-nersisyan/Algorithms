# Power Calculation Methods with C++

This repository contains three different methods to compute the power of a number `x` raised to the power of `n` (i.e., `x^n`). The three methods are:

1. **Iterative Method**  
2. **Recursive Method**  
3. **Exponentiation by Squaring**

Each of these methods is implemented in C++, and their time complexities vary, making them useful in different scenarios.

## Methods

### 1. Iterative Method
In this method, the power is calculated using a simple loop. It works by multiplying the base number `x` repeatedly `n` times.

### 2. Recursive Method
This method uses recursion to calculate the power of a number. It works by dividing the problem into smaller sub-problems, making it an elegant approach, though not the most efficient in terms of time complexity.

### 3. Exponentiation by Squaring
This method is a more optimized approach that reduces the number of multiplications needed. It exploits the properties of exponents and is more efficient than both the iterative and recursive methods, especially for large exponents.