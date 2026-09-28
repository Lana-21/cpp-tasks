#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


//завдання1
//void add_constant(int& value) {
//    value += 5; 
//}
//void sub_constant(int& value) {
//    value -= 9; 
//}
//int main() {
//    vector<int> numbers = { 41, 25, 10, -8, 15, 2, -11, 7 };
//    cout << "vector: ";
//    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;
//
//    auto min_it = min_element(numbers.begin(), numbers.end());
//    cout << "Minimum value: " << *min_it << "\n";
//    
//    sort(numbers.begin(), numbers.end());
//    cout << "sorting: ";
//    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;
//
//    for_each(numbers.begin(), numbers.end(), add_constant);
//    cout << "After increasing: ";
//    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;
//
//    for_each(numbers.begin(), numbers.end(), sub_constant);
//    cout << "After decreasing: ";
//    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;
//
//    int numb = 11;
//    auto it = find(numbers.begin(), numbers.end(), numb);
//    while (it != numbers.end()) {
//        numbers.erase(it);
//        it = find(numbers.begin(), numbers.end(), numb);
//    }
//    cout << "After removing " << numb << ": ";
//    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;


//завдання2
struct Time {
    int hours = 0;
    int minutes = 0;
    bool isValid() const {
        return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
    }
    int toMinutes() const {
        return hours * 60 + minutes;
    }
    friend istream& operator>>(istream& is, Time& t) {
        char colon;
        while (!(is >> t.hours >> colon >> t.minutes && colon == ':' && t.isValid())) {
            cout << "Invalid time! Try again (HH:MM): ";
            is.clear();
            is.ignore(1000, '\n'); 
        }
        return is;
    }
    friend ostream& operator<<(ostream& os, const Time& t) {
        if (t.hours < 10) os << '0';
        os << t.hours << ':';
        if (t.minutes < 10) os << '0';
        os << t.minutes;
        return os;
    }
};
class Train {
public:
    Train() = default;
    Train(string num, Time depTime, Time arrTime, string dest)
        : number{ num }, departureTime{ depTime },
        arrivalTime{ arrTime }, destination{ dest } {
    }
    string getNumber() const { return number; }
    string getDestination() const { return destination; }
    Time getDepartureTime() const { return departureTime; }
    Time getArrivalTime() const { return arrivalTime; }
    int getTravelTime() const {
        int dep = departureTime.toMinutes();
        int arr = arrivalTime.toMinutes();
        if (arr < dep) {
            arr += 24 * 60;
        }
        return arr - dep;
    }
    string getFormattedTime() const {
        int total = getTravelTime();
        return to_string(total / 60) + "h " + to_string(total % 60) + "m";
    }
    friend istream& operator>>(istream& is, Train& train) {
        cout << "Enter train number: ";
        while (!(is >> train.number) || train.number.empty()) {
            cout << "Invalid train number! Enter again: ";
            is.clear();
            is.ignore(1000, '\n');
        }
        cout << "Enter departure time (HH:MM): ";
        is >> train.departureTime;
        cout << "Enter arrival time (HH:MM): ";
        is >> train.arrivalTime;
        is.ignore(1000, '\n');
        cout << "Enter destination station: ";
        while (true) {
            getline(is, train.destination);
            if (!train.destination.empty()) {
                break;
            }
            cout << "Destination cannot be empty! Enter again: ";
        }
        return is;
    }
    friend ostream& operator<<(ostream& os, const Train& train) {
        os << "Train: " << train.number
            << "Departure: " << train.departureTime
            << "Arrival: " << train.arrivalTime
            << "Duration: " << train.getFormattedTime()
            << "Destination: " << train.destination;
        return os;
    }
private:
    string number;
    Time departureTime;
    Time arrivalTime;
    string destination;
};
class RailwayStation {
public:
    void addTrain() {
        Train train;
        cin >> train;
        trains.push_back(train);
        cout << "Train successfully added!" << endl;
    }
    void showAllTrains() const {
        if (trains.empty()) {
            cout << "There are no trains" << endl;
            return;
        }
        cout << "\nTrain list" << endl;
        for (auto it = trains.begin(); it != trains.end(); ++it) {
            cout << *it << endl;
        }
    }
    void searchByDestination() const {
        if (trains.empty()) {
            cout << "There are no trains" << endl;
            return;
        }
        string searchStation;
        cout << "Enter destination station to search: ";
        getline(cin, searchStation);
        bool found = false;
        cout << "\nTrains to station " << searchStation << endl;
        for (auto it = trains.begin(); it != trains.end(); ++it) {
            if (it->getDestination() == searchStation) {
                cout << *it << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No trains found" << endl;
        }
    }
    void searchByNumber() const {
        if (trains.empty()) {
            cout << "There are no trains" << endl;
            return;
        }
        string searchNum;
        cout << "Enter train number to search: ";
        cin >> searchNum;
        bool found = false;
        for (auto it = trains.begin(); it != trains.end(); ++it) {
            if (it->getNumber() == searchNum) {
                cout << "\nInformation for train #" << searchNum << endl;
                cout << *it << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Train " << searchNum << " was not found" << endl;
        }
    }
private:
    vector<Train> trains;
};
int main() {
    RailwayStation station;
    int choice;
    do {
        cout << "\nRAILWAY STATION" << endl
            << "1. Add a train to the system" << endl
            << "2. Display all trains" << endl
            << "3. Search trains by destination station" << endl
            << "4. Search train by number" << endl
            << "0. Exit" << endl
            << "Select an option: ";
        if (!(cin >> choice)) {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (choice) {
        case 1:
            station.addTrain();
            break;
        case 2:
            station.showAllTrains();
            break;
        case 3:
            cin.ignore(1000, '\n');
            station.searchByDestination();
            break;
        case 4:
            station.searchByNumber();
            break;
        case 0:
            cout << "Exiting the system" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (choice != 0);
    return 0;
}
