#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n, temp, digit, sum = 0;

    cout << "Enter a number: ";
    cin >> n;

    int perfectSum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0)
            perfectSum += i;
    }

    if (perfectSum == n)
        cout << "Perfect Number\n";
    else
        cout << "Not a Perfect Number\n";

    temp = n;
    int count = 0;

    while (temp > 0) {
        count++;
        temp /= 10;
    }

    temp = n;
    sum = 0;

    while (temp > 0) {
        digit = temp % 10;
        sum += pow(digit, count);
        temp /= 10;
    }

    if (sum == n)
        cout << "Armstrong Number";
    else
        cout << "Not an Armstrong Number";

    return 0;
}
