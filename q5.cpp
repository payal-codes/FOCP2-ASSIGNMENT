#include <iostream>
#include <map>
#include <set>
using namespace std;

class MovieTicket {

    map<int, set<int> > booked;
    map<int, int> countTickets;

public:

    bool BOOK(int x, int y) {

        if (booked[y].count(x) || countTickets[y] == 100)
            return false;

        booked[y].insert(x);
        countTickets[y]++;

        return true;
    }

    bool CANCEL(int x, int y) {

        if (booked[y].count(x) == 0)
            return false;

        booked[y].erase(x);
        countTickets[y]--;

        return true;
    }

    bool IS_BOOKED(int x, int y) {

        if (booked[y].count(x))
            return true;

        return false;
    }

    int AVAILABLE_TICKETS(int y) {

        return 100 - countTickets[y];
    }
};

int main() {

    int Q;
    cin >> Q;

    MovieTicket m;

    while (Q--) {

        string query;
        cin >> query;

        if (query == "BOOK") {

            int x, y;
            cin >> x >> y;

            if (m.BOOK(x, y))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }

        else if (query == "CANCEL") {

            int x, y;
            cin >> x >> y;

            if (m.CANCEL(x, y))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }

        else if (query == "IS_BOOKED") {

            int x, y;
            cin >> x >> y;

            if (m.IS_BOOKED(x, y))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }

        else if (query == "AVAILABLE_TICKETS") {

            int y;
            cin >> y;

            cout << m.AVAILABLE_TICKETS(y) << endl;
        }
    }

    return 0;
}
