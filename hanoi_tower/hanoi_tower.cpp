#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector<int> A, B, C;

void printState(int n) {
    cout << "\nCurrent state:\n\n";

    for (int level = n - 1; level >= 0; level--) {
        if (level < A.size()) cout << setw(3) << A[level];
        else cout << "  |";

        cout << "      ";

        if (level < B.size()) cout << setw(3) << B[level];
        else cout << "  |";

        cout << "      ";

        if (level < C.size()) cout << setw(3) << C[level];
        else cout << "  |";

        cout << endl;
    }

    cout << " ---      ---      ---\n";
    cout << "  A        B        C\n";
}

void moveDisk(vector<int>& from, vector<int>& to, char fName, char tName, int n) {
    int disk = from.back();
    from.pop_back();
    to.push_back(disk);

    cout << "\nMove disk " << disk << " from " << fName << " to " << tName << endl;
    printState(n);
}

void hanoi(int n, vector<int>& from, vector<int>& to, vector<int>& aux, char fName, char tName, char aName, int totalDisks) {

    if (n == 1) {
        moveDisk(from, to, fName, tName, totalDisks);
        return;
    }

    hanoi(n - 1, from, aux, to, fName, aName, tName, totalDisks);
    moveDisk(from, to, fName, tName, totalDisks);
    hanoi(n - 1, aux, to, from, aName, tName, fName, totalDisks);
}

int main() {
    int n;
    
    cout << "Enter number of disks: ";
    cin >> n;

    for (int i = n; i >= 1; i--) {
        A.push_back(i);
    }

    printState(n);

    hanoi(n, A, C, B, 'A', 'C', 'B', n);

    return 0;
}