#include <iostream>
#include "types.h"

using namespace std;

// Визначення методу поза класом: Student:: вказує, чий це метод
void Student::init(const char* newName, int newAge, double newGrade)
{
    strcpy_s(name, newName);
    age = newAge;
    averageGrade = newGrade;
}

void Student::print()
{
    // Поля класу доступні так само, як усередині класу
    cout << name << ", вік: " << age << ", середній бал: " << averageGrade << endl;
}

