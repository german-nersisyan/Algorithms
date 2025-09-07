# Exponentiation by Squaring Method for Power Calculation

Exponentiation by squaring is an optimized approach for calculating powers, especially for large exponents. It takes advantage of the properties of exponents to reduce the number of multiplications.

## How It Works

The key idea is to break down the problem into smaller sub-problems by exploiting the following rules:

1. If `n` is even:
   - `x^n = (x^(n//2))^2`
   
2. If `n` is odd:
   - `x^n = x * (x^((n-1)//2))^2`

This method allows us to reduce the number of multiplications to approximately `log(n)` instead of `n`.

- **Time Complexity**: O(log n)