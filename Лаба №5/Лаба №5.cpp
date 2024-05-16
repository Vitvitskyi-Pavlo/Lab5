// OOPLab5T.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <string>
#include <cstring>


using namespace std;


// Task 1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// Базовий клас Animal
class Animal {
protected:
    string classification; // Класифікація тварини
    int limbs; // Число кінцівок
    int offspring; // Число нащадків

public:
    // Конструктор з параметрами
    Animal(const string& cls, int limbs_count, int offspring_count)
        : classification(cls), limbs(limbs_count), offspring(offspring_count) {}

    // Віртуальний деструктор
    virtual ~Animal() {}

    // Віртуальна функція для друку
    virtual void print() const {
        cout << "Класифiкацiя: " << classification << endl;
        cout << "Кiлькiсть кiнцiвок: " << limbs << endl;
        cout << "Кiлькiсть потомства: " << offspring << endl;
    }
};

// Похідний клас Pet, успадковує від Animal
class Pet : public Animal {
private:
    string name; // Кличка

public:
    // Конструктор з параметрами
    Pet(const string& cls, int limbs_count, int offspring_count, const string& pet_name)
        : Animal(cls, limbs_count, offspring_count), name(pet_name) {}

    // Конструктор за замовчуванням, встановлює класифікацію "Pet", 4 кінцівки і 0 нащадків
    Pet(const string& pet_name) : Animal("Pet", 4, 0), name(pet_name) {}

    // Деструктор
    ~Pet() {}

    // Функція для зміни клички тварини
    void rename(const string& new_name) {
        name = new_name;
    }

    // Функція для зміни числа нащадків
    void setOffspring(int offspring_count) {
        offspring = offspring_count;
    }

    // Перевизначена функція друку, виводить інформацію про класифікацію, кінцівки, нащадків і кличку
    void print() const override {
        Animal::print();
        cout << "Name: " << name << endl;
    }
};

void Task1() {
    setlocale(LC_CTYPE, "Ukr");
    // Створення об'єкта класу Animal з параметрами
    Animal lion("Корова", 4, 2);
    // Друк інформації про тварину
    lion.print();
    cout << "---------------------" << endl;

    // Створення об'єкта класу Pet з параметрами
    Pet cat("Кiт", 4, 4, "Тiммi");
    // Друк інформації про домашню тварину
    cat.print();
    cout << "---------------------" << endl;

    // Зміна клички тварини
    cat.rename("Пухнастий");
    // Зміна числа нащадків
    cat.setOffspring(5);
    // Повторний друк інформації про домашню тварину зі зміненими параметрами
    cat.print();
    cout << "---------------------" << endl;

}




// Task 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class Tail {
private:
    int length;

public:
    // Конструктор з параметрами
    Tail(int len) : length(len) {}

    // Метод доступу для отримання довжини хвоста
    int getLength() const {
        return length;
    }
};

class Dog {
private:
    Tail tail; // Композиція: клас Dog містить об'єкт класу Tail
    char* color; // Колір собаки
    int age; // Вік собаки

public:
    // Конструктор з параметрами
    Dog(int tailLength, const char* dogColor, int dogAge) : tail(tailLength), age(dogAge) {
        // Виділення пам'яті для кольору та копіювання рядка
        color = new char[strlen(dogColor) + 1];
        strcpy_s(color, strlen(dogColor) + 1, dogColor);
    }

    // Деструктор
    ~Dog() {
        delete[] color; // Звільнення пам'яті для кольору
    }

    // Функція для друку
    void print() const {
        cout << "Довжина хвоста: " << tail.getLength() << endl;
        cout << "Колiр: " << color << endl;
        cout << "Вiк: " << age << endl;
    }
};

class NamedDog : public Dog {
private:
    char* name; // Кличка собаки

public:
    // Конструктор з параметрами
    NamedDog(int tailLength, const char* dogColor, int dogAge, const char* dogName)
        : Dog(tailLength, dogColor, dogAge) {
        // Виділення пам'яті для клички та копіювання рядка
        name = new char[strlen(dogName) + 1];
        strcpy_s(name, strlen(dogName) + 1, dogName);
    }

    // Деструктор
    ~NamedDog() {
        delete[] name; // Звільнення пам'яті для клички
    }

    // Перевизначена функція для друку
    void print() const {
        Dog::print(); // Виклик функції друку базового класу Dog
        cout << "Iм'я: " << name << endl;
    }
};

void Task2() {
    setlocale(LC_CTYPE, "ukr");
    // Створення об'єкту собаки з параметрами
    Dog dog1(30, "Коричневий", 5);
    cout << "Пес 1:" << endl;
    dog1.print();
    cout << endl;

    // Створення об'єкту іменованої собаки з параметрами
    NamedDog dog2(25, "Чорний", 3, "РЕКС");
    cout << "Пес 2:" << endl;
    dog2.print();


}



// Task 3 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



class Education {
protected:
    string institution;

public:
    // Конструктор за замовчуванням
    Education() : institution("Невiдомий") {}

    // Конструктор з параметрами
    Education(const string& inst) : institution(inst) {}

    // Конструктор копіювання
    Education(const Education& other) : institution(other.institution) {}

    // Оператор присвоювання
    Education& operator=(const Education& other) {
        if (this != &other) {
            institution = other.institution;
        }
        return *this;
    }

    // Оператор перенесення
    Education(Education&& other) noexcept : institution(move(other.institution)) {}

    // Функція для виведення в потік
    friend ostream& operator<<(ostream& out, const Education& edu) {
        out << "Заклад: " << edu.institution;
        return out;
    }

    // Функція для введення з потоку
    friend istream& operator>>(istream& in, Education& edu) {
        cout << "ВВедiть заклад: ";
        in >> edu.institution;
        return in;
    }
};

class HigherEducation : public Education {
private:
    string degree;

public:
    // Конструктор за замовчуванням
    HigherEducation() : Education(), degree("Невiдомий") {}

    // Конструктор з параметрами
    HigherEducation(const string& inst, const string& deg) : Education(inst), degree(deg) {}

    // Конструктор копіювання
    HigherEducation(const HigherEducation& other) : Education(other), degree(other.degree) {}

    // Оператор присвоювання
    HigherEducation& operator=(const HigherEducation& other) {
        if (this != &other) {
            Education::operator=(other);
            degree = other.degree;
        }
        return *this;
    }

    // Оператор перенесення
    HigherEducation(HigherEducation&& other) noexcept : Education(move(other)), degree(move(other.degree)) {}

    // Функція для виведення в потік
    friend ostream& operator<<(ostream& out, const HigherEducation& hedu) {
        out << static_cast<const Education&>(hedu) << ", Ступiнь: " << hedu.degree;
        return out;
    }

    // Функція для введення з потоку
    friend istream& operator>>(istream& in, HigherEducation& hedu) {
        in >> static_cast<Education&>(hedu);
        cout << "Введiть ступiнь: ";
        in >> hedu.degree;
        return in;
    }
};

void Task3() {
    setlocale(LC_CTYPE, "ukr");
    // Приклад використання
    Education edu1("Школа");
    HigherEducation hedu1("Унiверситет", "Бакалавр");

    cout << "Освiта 1: " << edu1 << endl;
    cout << "Вища освiта 1: " << hedu1 << endl;

    cout << "Введiть данi для Освiта 1:" << endl;
    cin >> edu1;
    cout << "Введiть данi для Вища освiта 1:" << endl;
    cin >> hedu1;

    cout << "Оновлена ​​освiта 1: " << edu1 << endl;
    cout << "Оновлена ​​вища освiта 1: " << hedu1 << endl;


}


void main() {
    int TaskN;
    setlocale(LC_CTYPE, "ukr");


    do {
        cout << "\n\nВведiть свiй вибiр: ";
        cin >> TaskN;

        switch (TaskN) {
        case 1:
            Task1();
            break;
        case 2:
            Task2();
            break;
        case 3:
            Task3();
            break;
        case 0:
            cout << "Вихiд з програми\n";
            break;
        default:
            cout << "Невiрний вибiр! Будь ласка, введiть число вiд 0 до 3.\n";
        }
    } while (TaskN != 0);


}