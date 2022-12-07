#include "first.h"
#include <iostream>

using namespace std;

class Animal {
protected:
    int age = 0;
public:
    Animal() {
        cout << "Animal()" << endl;
    }

    virtual ~Animal() { //виртуальный деструктор
        cout << "~Animal()" << endl;
    }

    void firstMethod() {
        age *= 10;
        cout << "Animal::firstMethod\tage = " << age << endl;
    }

    virtual void secondMethod() {
        age = 10;
        cout << "Animal::secondMethod\tage = " << age << endl;
    }

    void firstSound() {
        cout << "Sound of Animal" << endl;
    }

    virtual void secondSound() { // Виртуальный метод, который далее перекрывается
        cout << "Virtual sound of Animal" << endl;
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

    void secondMethod() {
        age = 1;
        cout << "Cat::secondMethod\t" << age << endl;
    }

    void firstSound() {
        cout << "Sound of Cat" << endl;
    }

    void secondSound() override {
        cout << "override secondSound of Cat" << endl;
    }

};

void invokeFirstProgram() {
    Animal *cat1 = new Cat();
    delete cat1;
    cout << endl;

    // что если метод 2 в Базовом классе virtual/ не virtual
    Animal *cat2 = new Cat();
    cat2->firstMethod(); // не virtual
    cat2->secondMethod(); // virtual
    cout << endl;

    // обращение через указатель на базовый класс/класс наследника (не virtual)
    Animal *cat3 = new Cat();
    cat3->firstSound();
    Cat *cat4 = new Cat();
    cat4->firstSound();
    cout << endl;

    // Обращение через указатель на базовый класс/класс наследника (virtual)
    Animal *cat5 = new Cat();
    cat5->secondSound();
    Cat *cat6 = new Cat();
    cat6->secondSound();
    cout << endl;
}