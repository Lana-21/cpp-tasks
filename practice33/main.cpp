#include <iostream>
#include <string>
using namespace std;

class Pet
{
public:
    Pet(const string& name, const string& color, double weight, int age)
        : name(name), color(color) {
        setWeight(weight);
        setAge(age);
    }
    virtual ~Pet() {}
    void setName(const string& name) { this->name = name; }
    const string& getName() const { return name; }
    void setColor(const string& color) { this->color = color; }
    const string& getColor() const { return color; }
    void setWeight(double weight) { this->weight = weight < 0.0 ? 0.0 : weight; }
    double getWeight() const { return weight; }
    void setAge(int age) { this->age = age < 0 ? 0 : age; }
    int getAge() const { return age; }

    virtual void Sound() const = 0;
    virtual void Type() const = 0;
    virtual void Show() const
    {
        cout << "Name: " << getName()
            << " Color: " << getColor()
            << " Weight: " << getWeight() << " kg"
            << " Age: " << getAge() << " yrs" << endl;
    }
private:
    string name;
    string color;
    double weight;
    int age;
};

class Dog : public Pet
{
public:
    Dog(const string& name, const string& color, double weight, int age)
        : Pet(name, color, weight, age) {
    }
    void Sound() const { cout << "Sound: Woof" << endl; }
    void Type() const { cout << "Type: Dog" << endl; }
};

class Cat : public Pet
{
public:
    Cat(const string& name, const string& color, double weight, int age)
        : Pet(name, color, weight, age) {
    }
    void Sound() const { cout << "Sound: Meow" << endl; }
    void Type() const { cout << "Type: Cat" << endl; }
};

class Parrot : public Pet
{
public:
    Parrot(const string& name, const string& color, double weight, int age)
        : Pet(name, color, weight, age) {
    }
    void Sound() const { cout << "Sound: AA" << endl; }
    void Type() const { cout << "Type: Parrot" << endl; }
};

class Hamster : public Pet
{
public:
    Hamster(const string& name, const string& color, double weight, int age)
        : Pet(name, color, weight, age) {
    }
    void Sound() const { cout << "Sound: PI" << endl; }
    void Type() const { cout << "Type: Hamster" << endl; }
};
int main()
{
    Pet* pet = new Dog("Bob", "Black", 11.5, 3);
    pet->Type();
    pet->Show();
    pet->Sound();
    cout << string(15, '*') << endl;
    delete pet;

    Cat cat("Duda", "Grey", 5.2, 2);
    pet = &cat;
    pet->Type();
    pet->Show();
    pet->Sound();
    cout << string(15, '*') << endl;

    Parrot parrot("Kesha", "Green", 0.35, 1);
    pet = &parrot;
    pet->Type();
    pet->Show();
    pet->Sound();
    cout << string(15, '*') << endl;

    Pet* arr[] = {
        pet,
        &cat,
        &parrot,
        new Hamster("Khoma", "Grey", 0.55, 1)
    };
    cout << "\nArray\n";
    for (auto item : arr) {
        cout << "\n" << string(15, '*') << endl;
        item->Type();
        item->Show();
        item->Sound();
    }
    delete arr[3];
    return 0;
}
