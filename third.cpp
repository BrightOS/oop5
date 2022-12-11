#include "third.h"
#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout << "Base()" << endl;
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

void func1(Base object) { cout << "func1(Base object)" << endl; }

void func2(Base *object) { cout << "func2(Base* object)" << endl; }

void func3(Base &object) { cout << "func3(Base& object)" << endl; }

//Динамические объекты внутри функций
Base Output_1() {
    cout << "Base Output_1()" << endl;
    Base *object = new Base();
    return *object;
}

Base *Output_2() {
    cout << "Base* Output_2()" << endl;
    Base *object = new Base();
    return object;
}

Base &Output_3() {
    cout << "Base& Output_3()" << endl;
    Base *object = new Base();
    return *object;
}

//Статические объекты внутри функций
Base Output_4() {
    cout << "Base Output_4()" << endl;
    Base object;
    return object;
}

Base *Output_5() {
    cout << "Base* Output_5()" << endl;
    Base object;
    return &object;
}

Base &Output_6() {
    cout << "Base& Output_6()" << endl;
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
    Base baza1;
    baza1 = Output_1(); // Видим, что динамический объект из func1  НЕ уничтожился" << endl;

    cout << "------------------------" << endl;
    Base baza2 = Output_2(); // никакого копирования и прочего прочего, все отлично

    cout << "-----------------------" << endl;
    Base &baza3 = Output_3(); // в данном случае проблема в том, что baza3 - это ссылка, и ее удаление не удалит сам объект
    delete &baza3;

    cout << "----------Возвращаем статические объекты:----------" << endl;
    Base baza4;
    baza4 = Output_4(); // Видим огромное количество созданий и удалений объектов

    cout << "------------------------" << endl;
    Base *baza5 = Output_5(); // Тут мы обратимся к несуществующей памяти(в процессе копирования), следовательно, краш
    baza5->Crush();
    delete baza5; // именно тут мы попытаемся удалить объект, которого нет

    cout << "-----------------------" << endl;
    Base &baza6 = Output_6(); // объект не скопируется
    delete& baza6; // И вновь, пытаемся копировать уже удаленный объект


    cout << endl;

    cout << "----------Ниже смотрим на возвращение из функции для Desk:----------" << endl;
    Base *desk1 = new Desk();
    *desk1 = Output_1(); // Скопировал, но не удалил динамический объект
    delete desk1;

    cout << "-----------------------" << endl;
    Base *desk2 = new Desk();
    desk2 = Output_2(); // Скопировал, но динамический объект из функции НЕ удалился
    delete desk2;

    cout << "-----------------------" << endl;
    Base *desk3 = new Desk();
    *desk3 = Output_3(); // передали Адресс созданного в функции объекта, но старый так и остался в стеке;
    delete desk3;

    cout << "----------Возвращаем статические объекты:----------" << endl;
    Base *desk4 = new Desk();
    *desk4 = Output_4(); // Объекты удалились и передались, оставив за собой след из кучи созданий/удалений
    delete desk4;

    cout << "-----------------------" << endl;
    Base *desk5 = new Desk();
    desk5 = Output_5(); // Объект в функции удалился до копирования
    delete desk5;

    cout << "-----------------------" << endl;
    Base *desk6 = new Desk();
    *desk6 = Output_6(); // Объект в функции удалился до копирования
    delete desk6; // удалить можем, ибо работает как бы "присваивание по ссылке"

    cout << "----------Ниже удалятся статические объекты: baza1, baza2, baza4, pd1, pb1----------" << endl;
}