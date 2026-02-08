#include <iostream>
using namespace std;

int main() {

    for (int i = 5; i >= 1; i--) {      // rows
        for (int j = 5; j >= i; j--) {  // columns
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}
