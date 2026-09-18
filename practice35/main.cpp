#include <iostream>
#include <string>
#include <climits> 
#include <ctype.h>
#include <exception>
using namespace std;

//завдання1
int stringToInt(string s) {
    if (s.empty()) {
        throw "Empty string!";
    }
    if (s[0] == '-') {
        throw "Negative numbers!";
    }
    long long int result = 0;
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            throw "Invalid character!";
        }
        int digit = s[i] - '0';
        result = result * 10 + digit;
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
            throw "Out of range!";
        }
    }
    return result;
}
int main() {
    string input;
    cout << "Input number: ";
    cin >> input;
    try {
        int res = stringToInt(input);
        cout << "Result: " << res << endl;
    }
    catch (const char* exp) {
        cerr << "Error: " << exp << endl;
    }
    catch (...) {
        cerr << "Error: Unknown exception" << endl;
    }
    return 0;
}


//завдання2
class Stack_error : public exception
{
public:
    Stack_error(const string& message) : message{ message }
    {
    }
    const char* what() const noexcept override
    {
        return message.c_str();
    }
private:
    string message;
};
class Stack
{
public:
    Stack(int size)
    {
        if (size <= 0) {
            throw Stack_error("Stack capacity must be positive!");
        }
        capacity = size;
        arr = new int[capacity];
        if (arr == nullptr) {
            throw Stack_error("Failed to allocate memory!");
        }
        index = -1;
    }
    ~Stack()
    {
        delete[] arr;
    }
    void push(int value)
    {
        if (index >= capacity - 1) {
            throw Stack_error("Stack Overflow!");
        }
        arr[++index] = value;
    }
    int pop()
    {
        if (isEmpty()) {
            throw Stack_error("Stack Underflow!");
        }
        return arr[index--];
    }
    int look() const
    {
        if (isEmpty()) {
            throw Stack_error("Stack is empty!");
        }
        return arr[index];
    }
    bool isEmpty() const
    {
        return index == -1;
    }
private:
    int* arr;
    int capacity;
    int index;
};
int main()
{
    try {
        cout << "Test 1" << endl;
        Stack badStack(-5);
    }
    catch (const Stack_error& err) {
        cerr << "Stack error: " << err.what() << endl;
    }
    try {
        cout << "\nTest 2" << endl;
        Stack myStack(2);
        myStack.push(10);
        myStack.push(20);
        cout << "Top element: " << myStack.look() << endl;
        myStack.push(30);
    }
    catch (const Stack_error& err) {
        cerr << "Stack error: " << err.what() << endl;
    }
    try {
        cout << "\nTest 3" << endl;
        Stack myStack(2);
        myStack.pop();
    }
    catch (const Stack_error& err) {
        cerr << "Stack error: " << err.what() << endl;
    }
    catch (const std::exception& err) {
        cerr << "General error: " << err.what() << endl;
    }
    system("pause");
    return 0;
}
