#include "first.h"
#include <iostream>

using namespace std;

class FirstAnimal {
protected:
    int age = 0;
public:
    FirstAnimal() {
        cout << "FirstAnimal()" << endl;
    }

    virtual ~FirstAnimal() { //виртуальный деструктор
        cout << "~FirstAnimal()" << endl;
    }

    void firstMethod() {
        age *= 10;
        cout << "FirstAnimal::firstMethod\tage = " << age << endl;
    }

    virtual void secondMethod() {
        age = 10;
        cout << "FirstAnimal::secondMethod\tage = " << age << endl;
    }

    void firstSound() {
        cout << "Sound of FirstAnimal" << endl;
    }

    virtual void secondSound() { // Виртуальный метод, который далее перекрывается
        cout << "Virtual sound of FirstAnimal" << endl;
    }
};

class FirstCat : public FirstAnimal {
public:
    FirstCat() {
        cout << "FirstCat()" << endl;
    }

    ~FirstCat() {
        cout << "~FirstCat()" << endl;
    }

    void secondMethod() {
        age = 1;
        cout << "FirstCat::secondMethod\t" << age << endl;
    }

    void firstSound() {
        cout << "Sound of FirstCat" << endl;
    }

    void secondSound() override {
        cout << "override secondSound of FirstCat" << endl;
    }

};

void invokeFirstProgram() {
    FirstAnimal *cat1 = new FirstCat();
    delete cat1;
    cout << endl;

    // что если метод 2 в Базовом классе virtual/ не virtual
    FirstAnimal *cat2 = new FirstCat();
    cat2->firstMethod(); // не virtual
    cat2->secondMethod(); // virtual
    cout << endl;

    // обращение через указатель на базовый класс/класс наследника (не virtual)
    FirstAnimal *cat3 = new FirstCat();
    cat3->firstSound();
    FirstCat *cat4 = new FirstCat();
    cat4->firstSound();
    cout << endl;

    // Обращение через указатель на базовый класс/класс наследника (virtual)
    FirstAnimal *cat5 = new FirstCat();
    cat5->secondSound();
    FirstCat *cat6 = new FirstCat();
    cat6->secondSound();
    cout << endl;
}