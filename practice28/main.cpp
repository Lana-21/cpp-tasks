#include "Header.h"

int main() {
    Array arr1(3);
    arr1.setElement(0, 15);
    arr1.setElement(1, 45);
    arr1.setElement(2, 50);

    Array arr2(3);
    arr2.randomize();

    cout << "arr1: " << arr1 << endl;
    cout << "arr2: " << arr2 << endl;

    arr1[0] = 99;
    arr1(5);
    arr1.sortArray();
    cout << "sorted arr1: " << arr1 << endl;
    cout << "Min: " << arr1.getMin() << ", Max: " << arr1.getMax() << endl;

    int sum = (int)arr1;
    cout << "Sum of arr1 elements: " << sum << endl;
    char* strRepr = arr1; 
    cout << "String representation of arr1: " << strRepr << endl;
    delete[] strRepr;

    if (arr1 > arr2) {
        cout << "arr1 sum is greater than arr2 sum" << endl;
    }
    if (arr1 < arr2) {
        cout << "arr1 has fewer elements > 31 than arr2" << endl;
    }

    return 0;
}
