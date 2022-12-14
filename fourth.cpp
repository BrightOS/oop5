#include "fourth.h"
#include <iostream>
#include <memory>

using namespace std;

class FourthAnimal {
private:
    int age;
    string name;
public:
    FourthAnimal() {
        cout << "FourthAnimal()" << endl;
    }

    ~FourthAnimal() {
        cout << "~FourthAnimal()" << endl;
    }

    int getAge() {
        return age;
    }
};


void invokeFourthProgram() {
    {
        cout << "--------------------" << endl;
        auto *dog1 = new FourthAnimal();
        cout << "При использовании стандартного указателя, при выходе из области видимости dog1 не удалился" << endl;
    }
    cout << "--------------------" << endl;

    cout << endl;
    cout << "----------unique_ptr----------" << endl;
    {
        unique_ptr<FourthAnimal> unique_dog1(new FourthAnimal());
    }
    cout << "А тут, как мы видим, динамический объект FourthAnimal удалился, когда вышел из своей области видимости" << endl;
    cout << "--------------------" << endl;
    {
        auto unique_dog2 = make_unique<FourthAnimal>();
    }
    cout << "make_unique позволяет отказаться от использования оператора new" << endl;
    // А это не создаст утечку памяти, если при исп. new было вызвано исключение
    cout << "--------------------" << endl;

    cout << endl;
    cout << "----------shared_ptr----------" << endl;
    // Но unique_ptr не позволяет нескольким объектам работать с собой, для этого есть shared_ptr
    shared_ptr<FourthAnimal> shared_ptr1 = make_shared<FourthAnimal>(); // Создаётся объект
    {
        const shared_ptr<FourthAnimal>& shared_ptr2 = shared_ptr1;
        // Теперь у объекта два владельца, выраженных в виде shared_ptr и shared_ptr2
    }
    // shared_ptr2 выходит из области видимости,
    cout << "Уничтожение объекта произойдет тогда, когда shared_ptr1 выйдет из области видимости(т.е. ниже:)" << endl;
}