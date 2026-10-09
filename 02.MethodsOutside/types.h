#pragma once
class Student
{
private:
    char name[50];
    int age;
    double averageGrade;

public:
    // Лише оголошення (прототипи) методів
    void init(const char* newName, int newAge, double newGrade);
    void print();
    bool isExcellent();

    // Тіло всередині класу — метод автоматично inline
    int getAge()
    {
        return age;
    }
};

// Короткий метод поза класом робимо inline явно
inline bool Student::isExcellent()
{
    return averageGrade >= 10;
}