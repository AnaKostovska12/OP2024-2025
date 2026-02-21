/*Да се дефинира класа Country во која ќе се чуваат информации за:
name(низа од максимум 100 карактери) име на државата
capital(низа од максимум 100 карактери) главен град
area(децимален број) - површина во илјада km2
population(децимален број) - популација во милиони.
Сите променливи внатре во класата треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:
 конструктор (без и со параметри)
деструктор
set методи
get методи
Да се дефинираат следните методи во класата:
display() која што ќе ги печати информациите за сметката во следниот формат:
Country: Guyana
Capital: Georgetown
Area: 214
Population: 0.8
Надвор од класата:

 sortCountries(Country *countries, int n) која што ќе ги сортира државите растечки по нивната површина.*/

#include <iostream>
#include <cstring>
using namespace std;

class Country {
private:
 char name[100];
 char capital[100];
 float area;
 float population;
public:
Country(){
    strcpy(name,"nema");
  strcpy(capital,"nema");
    area=0;
    population=0;
};
Country(char *namee,char *capitall,float areaa,float populationn) {
 strcpy(name,namee);
 strcpy(capital,capitall);
 area=areaa;
 population=populationn;
};
 ~Country(){cout<<"destruction";}
 void set_name(char *namee) {
  strcpy(name,namee);
 }
 void set_capital(char *capitall) {
  strcpy(capital,capitall);
 }
 void set_area(float areaa) {
  area = areaa;
 }
 void set_population(float populationn) {
  population = populationn;
 }
 void get_name() {
 cout<<name<<endl;
 }
 void get_capital() {
  cout<<capital<<endl;
 }
 float get_area() {
    return area;
 }
 float get_population() {
  return population;
 }
 void display() {
  cout<<"Name: "<<name<<endl;
  cout<<"Capital: "<<capital<<endl;
  cout<<"Area: "<<area<<endl;
  cout<<"Population: "<<population<<endl;
 }
};
void sort(Country *niza,int n) {
 Country temp;
 for (int i = 0; i < n; i++) {
  for (int j = 0; j < n-i-1; j++) {
    if (niza[j].get_area()>niza[j+1].get_area()) {
    temp=niza[j];
    niza[j]=niza[j+1];
    niza[j+1]=temp;
    }

  }
 }
}

int main() {
 int n;
 char namee[100],capitall[100];
 float areaa,populationn;
 cin>>n;
 cin.ignore();
 Country niza[n];
 for (int i = 0; i < n; i++) {
  cin.getline(namee,100);
  niza[i].set_name(namee);
  cin.getline(capitall,100);
  niza[i].set_capital(capitall);
  cin>>populationn;
  niza[i].set_population(populationn);
  cin>>areaa;
  cin.ignore();
  niza[i].set_area(areaa);
 }
 sort(niza,n);
 for (int i = 0; i < n; i++) {
  niza[i].display();
 }
 return 0;
}