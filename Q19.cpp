#include <iostream>
using namespace std;

int main() {
    int start, end;

    cout << "Enter starting number: ";
    cin >> start;

    cout << "Enter ending number: ";
    cin >> end;

    cout << "Prime numbers in the range are:\n";

    for (int n = start; n <= end; n++) {
        if (n <= 1)
            continue;

        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (n % i == 0)
                count++;
        }

        if (count == 2)
            cout << n << " ";
    }

    return 0;
}
