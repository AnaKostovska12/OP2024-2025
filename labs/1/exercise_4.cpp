/* Да се дефинира класа MobilePhone во која ќе се чуваат податоци за еден мобилен телефон:

модел (низа од карактери не подолга од 20 карактери)
број на модел (цел број)
година на издавање (цел број)

За класата да се дефинира default конструктор, конструктор со аргументи, copy конструктор,
 деструктор и доколку има потреба get методи. Исто така да се дефинира и фунцкија за печатење на
 информации за класата која ќе печати во следниот формат
 „(модел) (број на модел) release year: (година на издавање)“.

Потоа да се дефинира класа Owner во која се чуваат следните информации:
име (низа од карактери не подолга од 20 карактери)
презиме (низа од карактери не подолга од 20 карактери)
мобилен телефон (објект од класа MobilePhone)

Да се креира default конструктор, конструктор со аргументи, деструктор и доколку има потреба get методи.

 Исто така да се дефинира и функција за печатење на информации за класата која ќе печати во следниот формат:

„(име) (презиме) has a mobile phone:(информации за мобилен телефон)“
 */

#include <cstdio>
#include <iostream>
#include <ostream>
#include <string.h>
using namespace std;

class MobilePhone {
private:
 char model[20];
 int model_broj;
 int year;
public:
 MobilePhone() {};
 MobilePhone(char *modell, int model_brojj, int yearr) {
  strcpy(model, modell);
  model_broj = model_brojj;
  year = yearr;
 }
 ~MobilePhone() {};

 void print() {
  cout << "( " << model <<" ) ( "<<model_broj<<" ) release year : ( " << year << " )"<< endl;}
};

class Owner {
private:
 char name[20];
 char surname[20];
 MobilePhone mobile;
public:
 Owner() {};
 Owner(char *namee, char *surnamee,MobilePhone mobilee) {
  strcpy(name, namee);
  strcpy(surname, surnamee);
  mobile = mobilee;
 }
 ~Owner() {};
 MobilePhone get_mobile(){
  return mobile;
 }
 void print() {
  cout << "( " << name <<" ) ( "<<surname <<" ) has a mobile phone : ( ";
  get_mobile().print();
 }
};

int main() {
 char namee[20], surnamee[20],model[20];
 int year,broj;
 cin.getline(namee, sizeof(namee));
 cin.getline(surnamee, sizeof(surnamee));
 cin.getline(model, sizeof(model));
 cin >> year;
 cin >> broj;
 MobilePhone mobile_phone(model,broj,year);
 Owner covek(namee,surnamee,mobile_phone);
 covek.print();
 return 0;
}