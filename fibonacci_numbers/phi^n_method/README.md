# ⚡ Fast Fibonacci Number Calculator using Binet's Formula (C++)

This C++ program calculates the **n-th Fibonacci number** using a mathematical **closed-form expression** known as **Binet's Formula**.

---

## 📋 Description

Instead of computing Fibonacci numbers step-by-step, this implementation uses the mathematical formula:

\[
F(n) = \frac{{\phi^n - \psi^n}}{\sqrt{5}}
\]

Where:
- \(\phi = \frac{1 + \sqrt{5}}{2}\) (the golden ratio)
- \(\psi = \frac{1 - \sqrt{5}}{2}\)

The program avoids using the standard `pow()` function for exponentiation and instead multiplies values manually for performance and precision reasons.

---