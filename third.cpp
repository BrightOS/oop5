#include "third.h"
#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout << "Base()" << endl;
    }

    Base(Base const &object) {
        cout << "Base(object)" << endl;
    }

    Base(Base *object) {
        cout << "Base(* object)" << endl;
    }

    Base(Base &object) {
        cout << "Base(& object)" << endl;
    }

    virtual ~Base() {
        cout << "~Base()" << endl;
    }

    void Crush() { cout << "WTF, it's working......" << endl; }
};

class Desk : public Base {
public:
    Desk() {
        cout << "Desk()" << endl;
    }

    Desk(Desk *object) {
        cout << "Desk(* object)" << endl;
    }

    Desk(Desk &object) {
        cout << "Desk(& object)" << endl;
    }

    ~Desk() {
        cout << "~Desk()" << endl;
    }
};

void func1(Base object) {
    cout << "func1(Base object)" << endl;
}

void func2(Base *object) {
    if (dynamic_cast<Desk *>(object))
        cout << "func2(Base* object) (Desk as Base)" << endl;
    else
        cout << "func2(Base* object)" << endl;
}

void func3(Base &object) {
    if (dynamic_cast<Desk *>(&object))
        cout << "func3(Base& object) (Desk as Base)" << endl;
    else
        cout << "func3(Base& object)" << endl;
}

// Динамические объекты внутри функций
Base output1() {
    cout << "Base output1()" << endl;
    Base *object = new Base();
    return *object;
}

Base *output2() {
    cout << "Base* output2()" << endl;
    Base *object = new Base();
    return object;
}

Base &output3() {
    cout << "Base& output3()" << endl;
    Base *object = new Base();
    return *object;
}

// Статические объекты внутри функций
Base output4() {
    cout << "Base output4()" << endl;
    Base object;
    return object;
}

Base *output5() {
    cout << "Base* output5()" << endl;
    Base object;
    return &object;
}

Base &output6() {
    cout << "Base& output6()" << endl;
    Base object;
    return object;
}

void invokeThirdProgram() {
    cout << "----------Смотрим на передачу в функцию для Base:----------" << endl;

    Base pb1;
    cout << "-----------------------" << endl;
    func1(pb1); // В данном случае создается копия b1 и передается в func1
    cout << "-----------------------" << endl;
    func2(&pb1);
    cout << "-----------------------" << endl;
    func3(pb1);

    cout << endl;
    cout << "----------Смотрим на передачу в функцию для Desk:----------" << endl;
    Desk pd1;;
    cout << "-----------------------" << endl;
    func1(pd1);
    cout << "-----------------------" << endl;
    func2(&pd1);
    cout << "-----------------------" << endl;
    func3(pd1);


    cout << endl;

    cout << "----------Смотрим на возвращение из функции для Base:----------" << endl;
    Base baza1 = output1(); // Видим, что динамический объект из func1 НЕ уничтожился;

    cout << "------------------------" << endl;
    Base baza2 = output2(); // никакого копирования, все отлично

    cout << "-----------------------" << endl;
    Base &baza3 = output3(); // в данном случае проблема в том, что baza3 - это ссылка, и ее удаление не удалит сам объект
    delete &baza3; // Пробуем удалить в первый раз
    delete &baza3; // Удаляем во второй
    delete &baza3; // В третий
    delete &baza3; // И всё время удаляются копии

    cout << "----------Возвращаем статические объекты:----------" << endl;
    Base baza4 = output4(); // На удивление всё проходит максимально гладко

    cout << "------------------------" << endl;
    Base *baza5 = output5(); // Тут мы обратимся к несуществующей памяти(в процессе копирования), следовательно...
    delete baza5; // Ничего не произойдёт

    cout << "-----------------------" << endl;
    Base &baza6 = output6(); // Объект создастся и удалится в функции, вернётся адрес
    delete &baza6; // Ничего не произойдёт

    cout << "----------Ниже удалятся статические объекты: baza1, baza2, baza4, pd1, pb1----------" << endl;
}