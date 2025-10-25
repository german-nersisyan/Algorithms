# Deque Implementation using Dynamic Array (ArrayDeque)

This repository contains an implementation of a **Deque** (Double-Ended Queue) data structure using a dynamic array in C++. The `Deque` class is abstract and defines basic operations that are implemented in the `ArrayDeque` class. This data structure allows efficient insertion and deletion of elements at both ends of the container.

## Features

- **Push Front**: Adds an element to the front of the deque.
- **Push Back**: Adds an element to the back of the deque.
- **Pop Front**: Removes an element from the front of the deque.
- **Pop Back**: Removes an element from the back of the deque.
- **Front**: Returns the element at the front of the deque.
- **Back**: Returns the element at the back of the deque.
- **Resize**: The deque dynamically resizes when it reaches capacity.
- **Move Semantics**: Efficient memory management through move constructor and move assignment operator.
- **Copy Semantics**: Provides copy constructor and copy assignment operator.

## Overview

This implementation uses a dynamic array to store elements of the deque. When the array reaches its capacity, it resizes (doubles in size) to accommodate more elements. The `front` and `back` pointers are managed in a circular manner to ensure efficient access and manipulation at both ends.

### Key Methods:
1. `push_front(const T&)` - Adds an element at the front of the deque.
2. `push_back(const T&)` - Adds an element at the back of the deque.
3. `pop_front()` - Removes the front element of the deque.
4. `pop_back()` - Removes the back element of the deque.
5. `front()` - Returns a reference to the front element.
6. `back()` - Returns a reference to the back element.
7. `empty()` - Checks if the deque is empty.
8. `size()` - Returns the number of elements in the deque.