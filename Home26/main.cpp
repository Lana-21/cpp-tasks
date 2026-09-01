#include "Header.h"
void addReservoir(Reservoir*& arr, int& size, const Reservoir& res) {
    Reservoir* temp = new Reservoir[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i]; 
    }
    temp[size] = res;
    delete[] arr;
    arr = temp;
    size++;
}
void removeReservoir(Reservoir*& arr, int& size, int index) {
    if (index < 0 || index >= size) {
        cout << "Invalid indexl!" << endl;
        return;
    }
    Reservoir* temp = new Reservoir[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            temp[j] = arr[i];
            ++j;
        }
    }
    delete[] arr;
    arr = temp;
    size--;
}
int main()
{
    int size = 0;
    Reservoir* catalog = nullptr;

    addReservoir(catalog, size, Reservoir("Black Sea", "Sea", 1150000, 580000, 2212));
    addReservoir(catalog, size, Reservoir("Azov Sea", "Sea", 380000, 200000, 14));
    addReservoir(catalog, size, Reservoir("Svityaz", "Lake", 2750, 7800, 58.4));

    cout << "Catalog" << size << " reservoirs" << endl;
    for (int i = 0; i < size; i++) {
        cout << catalog[i];
    }

    cout << "\nChecks: " << endl;
    if (catalog[0].isSameType(catalog[1])) {
        cout << catalog[0].getName() << " and " << catalog[1].getName() << " have the same type." << endl;
        if (catalog[0].isAreaGreater(catalog[1])) {
            cout << catalog[0].getName() << " is larger than " << catalog[1].getName() << endl;
        }
    }

    ofstream fileOut("reservoirs.txt");
    for (int i = 0; i < size; i++) {
        catalog[i].saveText(fileOut);
    }
    fileOut.close();
    cout << "\nSaved to reservoirs.txt" << endl;
    removeReservoir(catalog, size, 1);

    cout << "\nCatalog after removal: " << size << " reservoirs" << endl;
    for (int i = 0; i < size; i++) {
        cout << catalog[i];
    }
    delete[] catalog;
    catalog = nullptr;

    return 0;
}
