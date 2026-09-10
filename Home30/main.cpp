#include <iostream>
#include <string>
using namespace std;

//завдання2
template <class T>
class Node {
public:
    T user;
    T doc;
    int priority;
    int order;
    Node<T>* next;
    Node(T u, T d, int p) : user{ u }, doc{ d }, priority{ p }, order{ 0 }, next{ nullptr } {}
};
template <class T>
class PrinterQueue {
public:
    void push(T user, T doc, int priority) {
        Node<T>* buf = new Node<T>(user, doc, priority);
        if (printHead == nullptr || priority > printHead->priority) {
            buf->next = printHead;
            printHead = buf;
        }
        else {
            Node<T>* cur = printHead;
            while (cur->next != nullptr && cur->next->priority >= priority) {
                cur = cur->next;
            }
            buf->next = cur->next;
            cur->next = buf;
        }
        cout << "Added: " << user << doc << " priority: " << priority << endl;
    }
    void pop() {
        if (printHead == nullptr) {
            cout << "Queue empty!" << endl;
            return;
        }
        Node<T>* buf = printHead;
        printHead = printHead->next;
        buf->order = counter++;
        cout << "Printing: " << buf->doc  << buf->user << endl;
        buf->next = nullptr;
        if (statsHead == nullptr) {
            statsHead = buf;
        }
        else {
            Node<T>* cur = statsHead;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = buf;
        }
    }
    void showStats() const {
        cout << "STATS" << endl;
        Node<T>* cur = statsHead;
        while (cur != nullptr) {
            cout << "No: " << cur->order << "User: " << cur->user << "Doc: " << cur->doc << endl;
            cur = cur->next;
        }
        cout << endl;
    }
private:
    Node<T>* printHead{ nullptr };
    Node<T>* statsHead{ nullptr };
    int counter{ 1 };
};
int main() {
    PrinterQueue<string> printer;
    printer.push("Oleg", "Report.pdf", 1);
    printer.push("Director", "Contract.docx", 5);
    printer.push("Anna", "Photo.jpg", 2);
    printer.push("Accountant", "Balance.xlsx", 5);
    cout << endl << " Printing " << endl;
    printer.pop(); 
    printer.pop(); 
    printer.pop(); 
    printer.pop(); 
    printer.showStats();
    system("pause");
    return 0;
}


//завдання1
template <class T>
class Node {
public:
    T value;
    Node<T>* next;
    Node(T val) : value{ val }, next{ nullptr } {}
};
template <class T>
class Stack {
public:
    ~Stack() {
        while (topNode != nullptr) {
            Node<T>* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = topNode;
        topNode = newNode;
    }
    T pop() {
        if (isEmpty()) {
            return T();
        }
        Node<T>* temp = topNode;
        T val = temp->value;
        topNode = topNode->next;
        delete temp;
        return val;
    }
    bool isEmpty() const {
        return topNode == nullptr;
    }
private: 
    Node<T>* topNode{ nullptr };
};
int checkBrackets(const string& str) {
    Stack<char> brackets;
    string open = "({[";
    string close = ")}]";
    for (int i = 0; i < str.length() && str[i] != ';'; i++) {
        char ch = str[i];
        size_t openPos = open.find(ch);
        size_t closePos = close.find(ch);
        if (openPos != string::npos) {
            brackets.push(ch);
        }
        else if (closePos != string::npos) {
            if (brackets.isEmpty() || brackets.pop() != open[closePos]) {
                return i;
            }
        }
    }
    return brackets.isEmpty() ? -1 : str.length() - 1;
}
int main() {
    string input;
    cout << "Enter a string (ending with ';'): ";
    getline(cin, input);
    int errPos = checkBrackets(input);
    if (errPos == -1) {
        cout << "String is valid!" << endl;
    }
    else {
        cout << "Error in bracket placement!" << endl;
        cout << input.substr(0, errPos + 1) << endl;
    }
    system("pause");
    return 0;
}
