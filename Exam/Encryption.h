#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Encryption {
public:
    bool isRegistered() {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) return false;
        char ch;
        if (file.get(ch)) {
            return true; 
        }
        return false;
    }
    bool registerUser(const string& username, const string& password) {
        if (username.find(' ') != string::npos) {
            cout << "Error: username cannot contain spaces" << endl;
            return false;
        }
        string data = username + " " + hashPassword(password);
        encryptDecrypt(data);
        ofstream fout(filename, ios::binary);
        if (!fout.is_open()) return false;
        fout.write(data.c_str(), data.size());
        return true;
    }
    bool login(const string& username, const string& password) {
        ifstream fin(filename, ios::binary);
        if (!fin.is_open()) return false;
        string data = "";
        char ch;
        while (fin.get(ch)) {
            data += ch;
        }
        fin.close();
        encryptDecrypt(data);
        string savedUsername = "";
        string savedHash = "";
        bool spaceFound = false;
        for (char c : data) {
            if (c == ' ') {
                spaceFound = true;
            }
            else if (!spaceFound) {
                savedUsername += c;
            }
            else {
                savedHash += c;
            }
        }
        return (username == savedUsername && hashPassword(password) == savedHash);
    }
private:
    const string filename = "user.bin";
    const char secretKey = 'S';
    string hashPassword(const string& password) {
        unsigned long hash = 5381;
        for (char c : password) {
            hash = ((hash << 5) + hash) + c;
        }
        return to_string(hash);
    }
    void encryptDecrypt(string& data) {
        for (char& c : data) {
            c ^= secretKey;
        }
    }
};
