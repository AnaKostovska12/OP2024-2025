/* Да се дефинира класа Ekipa што содржи информации за име на екипата, година на формирање и градот од каде потекнува.
Да се дефинира класа Natprevar што содржи информации за домаќин, гостин (објекти од класата Ekipa), голови кои ги
постигнал домаќинот и голови кои ги постигнал гостинот.
Dа се дефинира посебна функција revans што како аргументи прима два објекта од класата Natprevar и проверува дали
едниот натпревар е реванш на другиот. Еден натпревар е реваш на друг ако гостинот и домаќинот од првиот натпревар
се истите екипи со домаќинот и гостинот од вториот натпревар, соодветно.
Да се дефинира функцијата duel која што како аргументи прима два објекта од класата Natprevar и ако едниот натпревар
е ревашн на другиот функцијата треба да ја врати екипата која е подобра во меѓусебниот дуел. Во спротивно да испечати
порака дека натпреварите не се совпаѓаат. Во случајот кога е нерешено функцијата враќа 0.*/

#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

class Ekipa {
    char name[10];
    int year;
    char city[10];
    public:
    Ekipa() {
        strcpy(name, "");
        year = 0;
        strcpy(city, "");
    }
    Ekipa(char *name,int year,char *city) {
        strcpy(this->name,name);
        this->year = year;
        strcpy(this->city, city);
    }
    char *getname() {
        return name;
    }
    void print() {
        cout<<name<<" "<<year<<" "<<city<<endl;
    }

};

class Natprevar {
private:
    Ekipa home;
    Ekipa away;
    int gol_dom;
    int gol_gos;
    public:
    Natprevar(){}
    Natprevar(Ekipa home,Ekipa away,int gol_dom,int gol_gos) {
        this->home = home;
        this->away = away;
        this->gol_dom = gol_dom;
        this->gol_gos = gol_gos;
    }
    Ekipa gethome() {
        return home;
    }
    Ekipa getaway() {
        return away;
    }
    int getgol_dom() {
        return gol_dom;
    }
    int getgol_gos() {
        return gol_gos;
    }

};

bool revans(Natprevar n1,Natprevar n2) {
    if (!(strcmp(n1.gethome().getname(),n2.getaway().getname()))) {
        if (!(strcmp(n2.gethome().getname(),n1.getaway().getname()))) {
            return true;
        }
    }
    return false;
}

void duel(Natprevar n1,Natprevar n2) {
    if (revans(n1,n2)) {
        int zbirekipa1=0;
        int zbirekipa2=0;
        zbirekipa1=n1.getgol_dom()+n2.getgol_gos();
        zbirekipa2=n2.getgol_dom()+n1.getgol_gos();
        if (zbirekipa1>zbirekipa2) {
             n1.gethome().print();
             return;
        }
        if (zbirekipa2>zbirekipa1) {
             n2.getaway().print();
             return;
        }
        else cout<<"0";
    }
    else {
        cout<<"Ne se sofpagjaat"<<endl;
    }
}

int main() {
    Ekipa e1("Real Madrid",1880,  "Madrid");
    Ekipa e2("FC Barcelona",1880,  "Barcelona");

    Natprevar n1(e1, e2, 1, 2);
    Natprevar n2(e2, e1, 1, 0);

    duel(n1, n2);

    return 0;
}