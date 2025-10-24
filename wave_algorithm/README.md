# 🌀 Wave Algorithm in C++

This project demonstrates the **Wave Algorithm** (also known as **Lee's Algorithm**) for finding the **shortest path** in a 2D grid (matrix) from a **source** to a **destination**, avoiding obstacles.

---

## 📖 Overview

The **Wave Algorithm** is a **Breadth-First Search (BFS)**-based algorithm used to find the shortest path in a matrix where:
- `0` represents a **free cell** (you can move there),
- `1` represents an **obstacle** (you cannot move there).

The program traverses the matrix in all four directions (up, down, left, right) from the starting point and calculates the shortest distance to each reachable cell.  
Finally, it prints the shortest path length to the destination if one exists.

---

## 🧠 How It Works

1. The algorithm starts from the **source cell** and assigns it a distance of `0`.
2. It explores all reachable neighboring cells using a **queue** (BFS approach).
3. Each valid neighboring cell gets a distance value that is **one more** than the current cell.
4. The process continues until all reachable cells are visited or the **destination** is reached.
5. The algorithm prints the **shortest path length** if the destination is reachable.