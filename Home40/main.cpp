#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<string, string> users;
const string ADMIN_NAME = "admin";
const string ADMIN_PASS = "admin123asd";
string curUser;
bool isAdmin = false;
void loadUsers() {
    ifstream f("users.txt");
    string u, p, r;
    while (f >> u >> p >> r) {
        if (r != "admin") {
            users[u] = p; 
        }
    }
}
void saveUser(const string& u, const string& p) {
    ofstream f("users.txt", ios::app);
    f << u << " " << p << " user\n";
    users[u] = p;
}
void test() {
    string qFile, aFile;
    cout << "Questions file: ";
    cin >> qFile;
    cout << "Answers file: ";
    cin >> aFile;
    ifstream qf(qFile), af(aFile);
    if (!qf || !af) {
        cout << "Error opening files!\n";
        return;
    }
    string question;
    vector<string> options(4);
    int correct, choice, count = 0, total = 0;
    map<string, vector<int>> userAnswers;
    while (getline(qf, question)) {
        if (question.empty()) continue;
        for (int i = 0; i < 4; i++) {
            getline(qf, options[i]);
        }
        if (!(af >> correct)) break;
        af.ignore();
        total++;
        cout << "\nQuestion " << total << ": " << question << "\n";
        for (int i = 0; i < 4; i++) {
            cout << "  " << i + 1 << ". " << options[i] << "\n";
        }
        cout << "Your answer (1-4): ";
        cin >> choice;
        string key = "Question " + to_string(total);
        userAnswers[key] = { choice };
        if (choice == correct) count++;
    }
    if (!total) {
        cout << "Test is empty!\n";
        return;
    }
    int score = (count * 12) / total;
    cout << "\nResult: " << count << "/" << total << "Score: " << score << "/12\n";
    cout << "\nYour Answers:\n";
    for (const auto& [ques, ans] : userAnswers) {
        cout << ques << " -> Chosen: ";
        for (int a : ans) {
            cout << a << " ";
        }
        cout << "\n";
    }
    ofstream rf("results.txt", ios::app);
    rf << "User: " << curUser << "Test: " << qFile << "Score: " << score << "/12\n";
    cout << "Results saved to file.\n";
}
void addTest() {
    string qFile, aFile; int n;
    cout << "Questions filename: ";
    cin >> qFile;
    cout << "Answers filename: ";
    cin >> aFile;
    cout << "Number of questions: "; 
    cin >> n;
    cin.ignore();
    ofstream qf(qFile), af(aFile);
    for (int i = 1; i <= n; i++) {
        string q, el; 
        int correct;
        cout << "\nQuestion " << i << ": "; 
        getline(cin, q);
        qf << q << "\n";
        for (int j = 1; j <= 4; j++) {
            cout << "  Option " << j << ": ";
            getline(cin, el); 
            qf << el << "\n";
        }
        cout << "Correct answer (1-4): "; 
        cin >> correct; 
        cin.ignore();
        af << correct << "\n";
    }
    cout << "Test created!\n";
}
bool authUser() {
    cout << "1. Login\n2. Register\n Choice: ";
    int choice;
    cin >> choice;
    string u, p;
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;
    if (choice == 2) {
        if (u == ADMIN_NAME || users.count(u)) {
            cout << "Username taken!\n";
            return false;
        }
        saveUser(u, p);
    }
    if (u == ADMIN_NAME && p == ADMIN_PASS) {
        curUser = u;
        isAdmin = true;
        return true;
    }
    if (users.count(u) && users[u] == p) {
        curUser = u;
        isAdmin = false;
        return true;
    }
    cout << "Invalid credentials!\n";
    return false;
}
void showMenu() {
    cout << "\nWelcome, " << curUser << "!\n";
    while (true) {
        cout << "\n1. Take test\n";
        if (isAdmin) cout << "2. Add test\n";
        cout << "0. Exit\nChoice: ";
        int choice;
        cin >> choice;
        if (choice == 1)  test();
        else if (choice == 2 && isAdmin) addTest();
        else break;
    }
}
int main() {
    loadUsers();
    if (authUser()) {
        showMenu();
    }
    return 0;
}
