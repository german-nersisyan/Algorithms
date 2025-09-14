# 🧮 Recursive Fibonacci Number Calculator (C++)

This C++ program calculates the **n-th Fibonacci number** using a **recursive approach**. It also includes **input validation** to ensure that the user provides a non-negative integer.

---

## 📋 Description

The program prompts the user to enter an index `n` and then computes the `n`-th number in the Fibonacci sequence using recursion:

- Fibonacci(0) = 0  
- Fibonacci(1) = 1  
- Fibonacci(n) = Fibonacci(n - 1) + Fibonacci(n - 2), for n ≥ 2

The recursive approach mimics the mathematical definition of the Fibonacci sequence but can be inefficient for large values of `n` due to repeated calculations.

---

## 📦 Sample Fibonacci Sequence

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|-------|---|---|---|---|---|---|---|---|---|---|
| Value | 0 | 1 | 1 | 2 | 3 | 5 | 8 |13 |21 |34 |