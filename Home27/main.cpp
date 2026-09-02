#include "Header.h"

//завдання1
int main() {
    Drib d1, d2;

    cout << "Input Drib 1 ";
    cin >> d1;
    cout << "Input Drib 2 ";
    cin >> d2;
    cout << "\nd1 = " << d1 << endl;
    cout << "d2 = " << d2 << endl;

    cout << "\nArithmetic\n";
    cout << "d1 + d2 = " << (d1 + d2) << endl;
    cout << "d1 - d2 = " << (d1 - d2) << endl;
    cout << "d1 * d2 = " << (d1 * d2) << endl;
    cout << "d1 / d2 = " << (d1 / d2) << endl;

    cout << "\nComparison\n";
    cout << "d1 == d2: " << (d1 == d2 ? "True" : "False") << endl;
    cout << "d1 != d2: " << (d1 != d2 ? "True" : "False") << endl;
    cout << "d1 > d2:  " << (d1 > d2 ? "True" : "False") << endl;
    cout << "d1 < d2:  " << (d1 < d2 ? "True" : "False") << endl;

    return 0;
}

//завдання2
int main() {
    Flat f1(60.5, 1200.0, 2);
    Flat f2(60.5, 1500.0, 3);
    Flat f3(45.0, 1000.0, 1);
    cout << "f1: " << f1 << endl;
    cout << "f2: " << f2 << endl;
    cout << "f3: " << f3 << endl;
    cout << endl;

    cout << "\n1. Area Comparison" << endl;
    cout << (f1 == f2 ? "f1 and f2: EQUAL area\n" : "f1 and f2: DIFFERENT area\n");
    cout << (f1 != f3 ? "f1 and f3: DIFFERENT area\n" : "");

    cout << "\n2. Changing Rooms" << endl;
    cout << "f1 rooms before ++: " << f1.getRooms() << endl;
    ++f1; 
    cout << "f1 rooms after ++f1: " << f1.getRooms() << endl;
    --f1; 
    cout << "f1 rooms after --f1: " << f1.getRooms() << endl;

    cout << "\n3. Price Comparison" << endl;
    cout << "Total price of f1: $" << f1.getTotalPrice() << endl;
    cout << "Total price of f2: $" << f2.getTotalPrice() << endl;

    if (f2 > f1) {
        cout << "f2 is MORE EXPONSIVE than f1" << endl;
    }
    if (f3 < f1) {
        cout << "f3 is CHEAPER than f1" << endl;
    }
    return 0;
}
