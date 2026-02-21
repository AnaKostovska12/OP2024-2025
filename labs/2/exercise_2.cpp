/*Да се креира класа Date со податоци: year, month, day - сите int. Во класата да има default constructor, constructor so parametri,
geteri dokolku se potrebni. Функција print() - ќе го печати датумот во формат: [year].[month].[day]
Да се креира класа Person со податоци: име и презиме - од типот char. Да се креира конструктор со параметри. Функција print() - ќе го
печати инфото во формат: [име] [презиме]
Да се креира класа Car со податоци: сопственик (типот Person), датум (типот Date), и мислам модел (типот char). Да се креира конструктор
со параметри. Функција print() - ќе го печати инфото на следниот начин:
    owner.print()
    date.print()
    cout << model << endl;
Потоа, да се креира надворешна функција, мислам дека беше void cheapCars(Car *cars, int numberOfCars, int price) - да ги печати
сите коли на кои цената им е помала од price.
*/
#include <iostream>
#include <string.h>
using namespace std;

class Date {
private:
    int year, month, day;
public:
    Date() { year = month = day = 0; }
    Date(int year, int month, int day) {
        this->year = year;
        this->month = month;
        this->day = day;
    }
    void print() { cout<<"["<<year<<"].["<<month<<"].["<<day<<"]"; }
};

class Person {
private:
    char name[100], surname[100];
public:
    Person() {}
    Person(char *name, char *surname) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }
    void print() { cout<<"["<<name<<"]  ["<<surname<<"]"; }
};

class Car {
private:
    Person owner;
    Date date;
    char model[20];
    int price;
public:
    Car() {}
    Car(Person ownerr, Date datee, char *model, int pricee) {
        owner = ownerr;
        date = datee;
        strcpy(this->model, model);
        price = pricee;
    }
    void print() {
        owner.print();
        date.print();
        cout << model << endl;
    }
    int getPrice() { return price; }
};

void cheapestCars(Car *cars, int numberOfCars, int price) {
    for (int i = 0; i < numberOfCars; i++) {
        if (cars[i].getPrice() < price) {
            cars[i].print();
        }
    }
}

int main() {
    Person p("Ana", "K");
    Date d(2025, 3, 24);
    Car c(p, d, "Tesla", 50000);
    Car koli[1] = {c};
    cheapestCars(koli, 1, 60000);
    return 0;
}