# Recursive Method for Power Calculation

The recursive method calculates `x^n` by dividing the problem into smaller sub-problems. It works by calling the function itself with smaller exponents until the base case is reached.

## How It Works

The recursive function works by breaking down the power calculation:

1. **Base Case**: If `n == 0`, return 1.
2. **Recursive Case**: If `n > 0`, return `x * power(x, n-1)`.
3. **Recursive Case**: If `n > 0`, return `1 / (x * power(x, n-1))`

The function will keep calling itself with `n` decreased by 1 until it reaches the base case (`n == 0`).

- **Time Complexity**: O(n)