# Fibonacci Matrix Multiplication

This program calculates the nth Fibonacci number using matrix exponentiation. The matrix representation of the Fibonacci sequence is used to compute the result efficiently, with a time complexity of \(O(\log n)\).

## Explanation

The Fibonacci sequence can be represented using the following matrix relation:

\[
\begin{bmatrix}
F(n+1) \\
F(n)
\end{bmatrix}
=
\left(
\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}
\right)^n
\cdot
\begin{bmatrix}
1 \\
0
\end{bmatrix}
\]

Where \( F(n) \) is the nth Fibonacci number.