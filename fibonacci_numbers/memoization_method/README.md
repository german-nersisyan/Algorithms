# 📈 Fibonacci Number Calculator (C++ - Memoization)

This C++ program calculates the **n-th Fibonacci number** using a **memoized recursive approach** to optimize performance and avoid redundant calculations. It uses a **dynamic programming** technique known as **memoization**.

---

## 📋 Description

The Fibonacci sequence is calculated using a recursive approach, but with **memoization** to store intermediate results. This significantly improves performance by avoiding recalculating Fibonacci numbers that have already been computed.

### Fibonacci Sequence Formula:

\[
F(n) = F(n-1) + F(n-2)
\]

Where:
- Fibonacci(0) = 0  
- Fibonacci(1) = 1  

Memoization ensures that each Fibonacci number is calculated once and then reused when needed, leading to an efficient time complexity of **O(n)**.