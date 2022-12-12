#include <iostream>
#include <windows.h>
#include "first.h"
#include "second.h"
#include "third.h"
#include "fourth.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Выберите номер программы (1-4)" << endl;
    int n;
    cin >> n;
    if (n == 1)
        invokeFirstProgram();
    else if (n == 2)
        invokeSecondProgram();
    else if (n == 3)
        invokeThirdProgram();
    else
        invokeFourthProgram();
    return 0;
}
