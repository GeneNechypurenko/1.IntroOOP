#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

/*
==========================================================================================================================================
                                                Аксесори: інспектори та модифікатори
==========================================================================================================================================

  Так як поля закриті (private), тому для роботи з ними класу необхідні спеціальні відкриті методи — АКСЕСОРИ (методи доступу).

  ІНСПЕКТОР (getter, «геттер») — метод, який повертає значення поля або обчислене значення і НЕ змінює об'єкт, за домовленостю зазвичай
  починається с get: getAge(), getName(), isExcellent(), getArea().

  МОДИФІКАТОР (setter, «сеттер», мутатор) — метод, який змінює поле об'єкта. За домовленістю починається з set: setAge(...), setName(...).
  Головне завдання модифікатора — ПЕРЕВІРИТИ нове значення і не допустити некоректного стану об'єкта. Тому модифікатор може повідомити про
  результат: повернути bool (true — значення прийнято, false — відхилено).

  Не кожне поле потребує сеттера: якщо поле не можна змінювати ззовні, сеттер для нього не пишуть. Гетер також може повертати значення,
  якого немає серед полів, наприклад обчислення операцій (площа прямокутника обчислюється з ширини й висоти).
*/

class Student
{
private:
    char name[50];
    int age;
    double averageGrade;

public:
    // ---------- Модифікатори (Сеттери) ----------
    void setName(const char* newName)
    {
        // Копіюємо, лише якщо ім'я вміщується в масив (разом з '\0')
        if (strlen(newName) < sizeof(name))
        {
            strcpy_s(name, 50, newName);
        }
    }

    bool setAge(int newAge)
    {
        if (newAge < 16 || newAge > 100)
        {
            return false;   // значення відхилено, поле не змінилося
        }
        age = newAge;
        return true;
    }

    bool setAverageGrade(double newGrade)
    {
        if (newGrade < 0 || newGrade > 12)
        {
            return false;
        }
        averageGrade = newGrade;
        return true;
    }

    // ---------- Інспектори (Геттери) ----------
    const char* getName()     // покажчик на константу: змінити ім'я ззовні не вийде
    {
        return name;
    }

    int getAge()
    {
        return age;
    }

    double getAverageGrade()
    {
        return averageGrade;
    }

    bool isExcellent()        // обчислене значення, окремого поля немає
    {
        return averageGrade >= 10;
    }
};

class Rect
{
private:
    double width;
    double height;

public:
    bool setSize(double newWidth, double newHeight)
    {
        if (newWidth <= 0 || newHeight <= 0)
        {
            return false;
        }
        width = newWidth;
        height = newHeight;
        return true;
    }

    double getWidth() { return width; }
    double getHeight() { return height; }

    // Інспектори, що обчислюють значення
    double getArea() { return width * height; }
    double getPerimeter() { return 2 * (width + height); }
};

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Student s;
    s.setName("Олена");
    s.setAge(20);
    s.setAverageGrade(10.5);

    // Перевіряємо результат роботи модифікатора
    if (!s.setAge(200))
    {
        cout << "Вік 200 відхилено" << endl;
    }

    cout << s.getName() << ", вік: " << s.getAge()
        << ", бал: " << s.getAverageGrade()
        << ", відмінниця: " << (s.isExcellent() ? "так" : "ні") << endl;

    Rect r;
    r.setSize(3, 4);
    if (!r.setSize(-1, 5))
    {
        cout << "Від'ємний розмір відхилено" << endl;
    }
    cout << "Прямокутник " << r.getWidth() << " x " << r.getHeight()
        << ": площа = " << r.getArea()
        << ", периметр = " << r.getPerimeter() << endl;

    return 0;
}

/*
  ІНСАЙТИ / BEST PRACTICES

  1. Сеттер без перевірки руйнує ІНКАПСУЛЯЦІЮ - фактично робить поле public. Тому не пишіть get/set «автоматично» для кожного поля, а
    відкривайте лише те, що справді потрібно.

  2. Інспектор (геттер) НІКОЛИ не повинен змінювати об'єкт. 

  3. Повертати з геттера покажчик на поле можна лише як const char*: інакше зовнішній код змінить приватні дані в обхід перевірок.

  4. В коді все ще лишається то саме слабке місце: доки не викликано сеттери, поля містять сміття. А якщо перший виклик setAge(200)
    відхилено — у полі так і залишиться сміття. Розв'язок — це конструктор класу.

  ==========================================================================================================================================

 ПРАКТИКА
  1. Клас Point (точка на екрані).
     - private-поля: int x, int y.
     - Інспектори: getX(), getY().
     - Модифікатори: setX(newX), setY(newY). Приймають лише значення від 0 до 100:
       якщо значення в межах — змінюють поле і повертають true,
       інакше — нічого не змінюють і повертають false.
     - У main: задайте точку (10; 20), спробуйте встановити x = 150,
       виведіть повідомлення про помилку і поточні координати.

  2. Клас Car (автомобіль).
     - private-поля: char brand[30], int speed.
     - Модифікатор setBrand(newBrand) — копіює марку (як setName у Student).
     - Модифікатор setSpeed(newSpeed) — швидкість лише від 0 до 300,
       повертає true або false, як setAge у Student.
     - Інспектори: getBrand(), getSpeed().
     - Інспектор isMoving() — повертає true, якщо швидкість більша за 0.
     - У main: створіть авто, задайте марку і швидкість 0, виведіть «стоїть»
       чи «їде» за допомогою isMoving(); потім задайте швидкість 90 і перевірте ще раз.
*/
