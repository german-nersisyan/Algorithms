# CyclicList - Circular Linked List Implementation in C++

## Overview

`CyclicList` is a template class that implements a circular singly linked list. The list allows you to add and remove elements at both the front and the back of the list. The structure of the list is cyclic, meaning the tail node points to the head, which allows for circular iteration.

The class provides a variety of standard operations such as pushing and popping elements, as well as supporting move and copy semantics. It also includes advanced features such as `swap` functionality, making it suitable for use in various scenarios that involve circular data structures.

## Features

- **Circular Behavior**: The last node points back to the first, creating a cyclic structure.
- **Dynamic Memory Management**: Memory is automatically managed through dynamic allocation and deallocation.
- **Copy and Move Semantics**: Full support for both copy and move constructors, as well as assignment operators.
- **Swap Support**: Swap operation to exchange the contents of two lists.