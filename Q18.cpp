#include <iostream>
using namespace std;

int main() {
    int n, rev = 0, temp;

    cout << "Enter ID (number): ";
    cin >> n;

    temp = n;
    while (temp > 0) {
        rev = rev * 10 + (temp % 10);
        temp /= 10;
    }

    if (rev == n)
        cout << "Palindrome ID";
    else
        cout << "Not a Palindrome ID";

    return 0;
}
