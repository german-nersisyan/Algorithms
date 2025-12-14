#include <iostream>
#include <stack>

void mergeAndSort(std::stack<int>& S1, std::stack<int>& S2)
{
    while (!S2.empty()) {
        S1.push(S2.top());
        S2.pop();
    }

    std::stack<int> T;

    while (!S1.empty()) {
        int x = S1.top();
        S1.pop();

        while (!T.empty() && T.top() > x) {
            S1.push(T.top());
            T.pop();
        }
        T.push(x);
    }

    while (!T.empty()) {
        S1.push(T.top());
        T.pop();
    }
}

void printStack(std::stack<int> S)
{
    while (!S.empty()) {
        std::cout << S.top() << " ";
        S.pop();
    }
    std::cout << std::endl;
}

int main() {
    std::stack<int> S1, S2;

    S1.push(3);
    S1.push(1);
    S1.push(4);

    S2.push(2);
    S2.push(5);

    std::cout << "Stack S1 (top to bottom): ";
    printStack(S1);

    std::cout << "Stack S2 (top to bottom): ";
    printStack(S2);

    mergeAndSort(S1, S2);

    std::cout << "Merged & Sorted Stack (top to bottom): ";
    printStack(S1);

    return 0;
}