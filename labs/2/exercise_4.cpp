/*Да се дефинира класа InvoiceItem во која што ќе се чуваат податоци за една ставка во фактура:

име на ставка (низа од максимум 100 карактери)
цена на ставка (цел број)
За класата да се дефинира copy конструктор, default конструктор и конструктор со аргументи.
Доколку е потребно да се креира и get методи.

Потоа да се креира класа Invoice во која што се чуваат следните податоци:

број на фактура (низа од максимум 10 карактери)
број на ставки во фактурата (цел број)
низа од ставки во фактурата (низа од објекти од InvoiceItem класата, max 100)
Да се креира конструктор со аргументи за класата.
Доколку е потребно да се креира и get методи.

Во класата да се креира метода totalPrice што ќе го пресметува вкупниот износ на фактурата. Вкупниот износ на фактурата се пресметува како збир од цените на сите ставки во нејзе.

ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.*/
#include<iostream>
#include <string.h>
using namespace std;

class InvoiceItem {
private:
    char name[100];
    int price;
public:
    InvoiceItem() {
        strcpy(name, "");
        price = 0;
    }
    ~InvoiceItem() {}
    InvoiceItem(char *name, int price) {
        strcpy(this->name, name);
        this->price = price;
    };
    InvoiceItem(const InvoiceItem& n) {
        strcpy(this->name, n.name);
        this->price = n.price;
    }
    char *getName() { return this->name; }
    int getPrice() { return this->price; }
};

class Invoice {
private:
    char broj[100];
    int broj_stavki;
    InvoiceItem items[100];
public:
    Invoice() {};
    ~Invoice() {};
    Invoice(char *broj, int broj_stavki, InvoiceItem *stavki) {
        strcpy(this->broj, broj);
        this->broj_stavki = broj_stavki;
        for(int i=0; i<broj_stavki; i++) {
            items[i] = stavki[i];
        }
    }
    int totalPrice() {
        int zbir=0;
        for(int i=0; i<broj_stavki; i++) {
            zbir += items[i].getPrice();
        }
        return zbir;
    }
};

int main() {
    InvoiceItem items[3];
    items[0] = InvoiceItem("Stavka1", 100);
    items[1] = InvoiceItem("Stavka2", 200);
    items[2] = InvoiceItem("Stavka3", 300);

    Invoice inv("12345", 3, items);
    cout << "Total Price: " << inv.totalPrice() << endl;
    return 0;
}