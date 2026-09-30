#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
using namespace std;

//завдання3
//int main() {
//    set<string> all_ip;
//    set<string> day1_ip;
//    set<string> day2_ip;
//    string ip;
//    ifstream myFile1("day1.txt");
//    ifstream myFile1("day1.txt");
//    if (!myFile1.is_open()) {
//        cerr << "Error opening" << endl;
//        return 1;
//    }
//    else {
//        while (myFile1 >> ip) {
//            day1_ip.insert(ip);
//            all_ip.insert(ip);
//        }
//        myFile1.close();
//    }
//    ifstream myFile2("day2.txt");
//    if (!myFile2.is_open()) {
//        cerr << "Error opening" << endl;
//        return 1;
//    }
//    else {
//        while (myFile2 >> ip) {
//            day2_ip.insert(ip);
//            all_ip.insert(ip);
//        }
//        myFile2.close();
//    }
//    cout << "Total unique users: " << all_ip.size() << endl;
//    cout << "\nSorted list of IP:" << endl;
//    for (string unique : all_ip) {
//        cout << unique << endl;
//    }
//    cout << "\nRegular customers: " << endl;
//    bool regulars = false;
//    for (string d1 : day1_ip) {
//        if (day2_ip.count(d1) > 0) {
//            cout << d1 << endl;
//            regulars = true;
//        }
//    }
//    if (!regulars) {
//        cout << "No found" << endl;
//    }
//    string sum_ip = "192.168.1.5";
//    cout << "\nCheck" << endl;
//    if (all_ip.count(sum_ip) > 0) {
//        cout << "IP address " << sum_ip << " visited the site" << endl;
//    }
//    else {
//        cout << "IP address " << sum_ip << " not found" << endl;
//    }
//    return 0;
//}


//завдання1
//int main() {
//    ifstream myFIn("text.txt");
//    if (!myFIn.is_open()) {
//        cerr << "Error opening" << endl;
//        return 1;
//    }
//    map<string, int> myDictionary;
//    string word;
//    while (myFIn >> word) {
//        if (myDictionary.contains(word)) { 
//            myDictionary[word] += 1;
//        }
//        else {                          
//            myDictionary[word] = 1;
//        }
//    }
//    myFIn.close();
//    cout << "count:" << endl;
//    for (const auto& [ word, count] : myDictionary) {
//        cout << "key: " << word << " value: " << count << endl;
//    }
//    return 0;
//}


//завдання2
int main() {
    ifstream qFile("questions.txt");
    ifstream aFile("answers.txt");
    if (!qFile.is_open() || !aFile.is_open()) {
        cerr << "Error opening" << endl;
        return 1;
    }
    string question;           
    vector<string> options(4); 
    int correctAnswer;
    map<string, vector<int>> userAnswers;
    int count = 0;
    int index = 1;
    cout << "TESTING" << endl;
    while (getline(qFile, question)) {
        if (question.empty()) {
            continue;
        }
        for (int i = 0; i < 4; i++) {
            getline(qFile, options[i]);
        }
        aFile >> correctAnswer;
        aFile.ignore();
        cout << "Question " << index << ": " << question << endl;
        for (int j = 0; j < 4; j++) {
            cout << "  " << (j + 1) << ". " << options[j] << endl;
        }
        int choice;
        cout << "Your answer (1-4): ";
        cin >> choice;
        string key = "Question " + to_string(index);
        userAnswers[key] = { choice };
        if (choice == correctAnswer) {
            count++;
        }
        cout << endl;
        index++;
    }
    qFile.close();
    aFile.close();
    int totalQuestions = index - 1;
    if (totalQuestions == 0) {
        cout << "No questions found!" << endl;
        return 1;
    }
    int score = (count * 12) / totalQuestions;
    cout << "RESULTS" << endl;
    cout << "Correct answers: " << count << " / " << totalQuestions << endl;
    cout << "Final score: " << score << " / 12" << endl;
    cout << "Your Answers" << endl;
 for (const auto& [ques, ans] : userAnswers) {
        cout << ques << " -> Chosen: ";
        for (int ans : ans) {
            cout << ans << " ";
        }
        cout << endl;
    }
    return 0;
}
