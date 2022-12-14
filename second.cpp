#include "second.h"
#include <iostream>
#include <ctime>

using namespace std;

class Animal {
public:
    Animal() {
        cout << "Animal()" << endl;
    }

    virtual ~Animal() {
        cout << "~Animal()" << endl;
    }

    virtual void sound() {
        cout << "Animal sound" << endl;
    }

    virtual string classname() {
        return "Animal";
    }

    virtual bool isA(const string &who) {
        return who == "Animal";
    }
};

class Dog : public Animal {
public:
    Dog() {
        cout << "Dog()" << endl;
    }

    ~Dog() {
        cout << "~Dog()" << endl;
    }

    void sound() override {
        cout << "Dog sound" << endl;
    }

    string classname() override {
        return "Dog";
    }

    void dog_method() {
        cout << "Dog Method" << endl;
    }

    virtual bool isA(const string &who) {
        return (who == "Dog") || (Animal::isA(who));
    }
};

class Cat : public Animal {
public:
    Cat() {
        cout << "Cat()" << endl;
    }

    ~Cat() {
        cout << "~Cat()" << endl;
    }

    void sound() override {
        cout << "Cat sound" << endl;
    }

    string classname() override {
        return "Cat";
    }

    void cat_method() {
        cout << "Cat Method" << endl;
    }

    virtual bool isA(const string &who) {
        return (who == "Cat") || (Animal::isA(who));
    }
};

class Manul : public Cat {
public:
    Manul() {
        cout << "Manul()" << endl;
    }

    ~Manul() {
        cout << "~Manul()" << endl;
    }

    void sound() override {
        cout << "Manul sound" << endl;
    }

    string classname() {
        return "Manul";
    }

    void manul_method() {
        cout << "Manul Method" << endl;
    }

    virtual bool isA(const string &who) {
        return (who == "Manul") || (Cat::isA(who));
    }
};

void invokeSecondProgram() {
    srand(time(nullptr));

    // Почему classname плох в использовании
    Animal *cat_or_manul;
    if (rand() % 2 == 0)
        cat_or_manul = new Cat();
    else
        cat_or_manul = new Manul();

    if (cat_or_manul->classname() == "Cat" || cat_or_manul->classname() == "Manul")
        static_cast<Manul *>(cat_or_manul)->cat_method();
    //	((Cat*)cat_or_manul)->cat_method();		//аналогичен static_cast



    // Использование isA
    if (cat_or_manul->isA("Cat"))
        static_cast<Manul *>(cat_or_manul)->cat_method();



    // Почему небезопасное привидение - не безопасно
    cout << "-------------------------------" << endl;
    Animal *realDog = new Dog();
    if (static_cast<Cat *>(realDog))
        static_cast<Cat *>(realDog)->cat_method();
    cout << "-------------------------------" << endl;



    //Использование dynamic_cast
    Animal *zoo[20];
    for (auto & i : zoo) {
        if (rand() % 2 == 0)
            i = new Cat();
        else
            i = new Dog();
    }

    for (auto & i : zoo) {
        auto n = dynamic_cast<Cat *>(i);
        if (n)
            n->cat_method();
        else if (dynamic_cast<Dog *>(i))
            dynamic_cast<Dog *>(i)->dog_method();
        else if (dynamic_cast<Manul *>(i))
            dynamic_cast<Manul *>(i)->manul_method();
    }
}