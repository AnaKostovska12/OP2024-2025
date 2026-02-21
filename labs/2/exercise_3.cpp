/*Да се дефинира класа MobilePhone во која ќе се чуваат податоци за еден мобилен телефон:

модел (низа од карактери не подолга од 20 карактери)
број на модел (цел број)
година на издавање (цел број)
За класата да се дефинира default конструктор, конструктор со аргументи, copy конструктор, деструктор и доколку има
потреба get методи.
Исто така да се дефинира и фунцкија за печатење на информации за класата која ќе печати во следниот формат „(модел) (број на модел)
release year: (година на издавање)“.

Потоа да се дефинира класа Owner во која се чуваат следните информации:

име (низа од карактери не подолга од 20 карактери)
презиме (низа од карактери не подолга од 20 карактери)
мобилен телефон (објект од класа MobilePhone)
Да се креира default конструктор, конструктор со аргументи, деструктор и доколку има потреба get методи. Исто така да се дефинира и
функција за печатење на информации за класата која ќе печати во следниот формат:

„(име) (презиме) has a mobile phone:

(информации за мобилен телефон)“*/
#include <iostream>
#include <cstring>
using namespace std;

class MobilePhone {
private:
    char model[20];
    int broj, godina;
public:
    MobilePhone() { strcpy(this->model,""); broj=0; godina=0; }
    MobilePhone(char *modell, int brojj, int godinaa) {
        strcpy(model, modell);
        broj=brojj;
        godina=godinaa;
    }
    MobilePhone(MobilePhone &other) {
        strcpy(this->model, other.model);
        this->broj = other.broj;
        this->godina = other.godina;
    }
    void print() {
        cout << "( " << model <<" ) ( "<<broj<<" ) release year : ( " << godina << " )"<< endl;
    }
};

class Owner {
private:
    char name[100], surname[100];
    MobilePhone mobilen;
public:
    Owner() {}
    Owner(char *namee, char *surnamee, MobilePhone mobilenn) {
        strcpy(name, namee);
        strcpy(surname, surnamee);
        mobilen=mobilenn;
    }
    void print() {
        cout<<"["<<name<<"] ["<<surname<<"]";
        mobilen.print();
    }
};

int main() {
    MobilePhone mp("Samsung", 123, 2022);
    Owner ow("Petar", "P", mp);
    ow.print();
    return 0;
}