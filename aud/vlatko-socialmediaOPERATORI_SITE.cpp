//
// Created by Ana Kostovska on 9.4.2025.
//
/*Дефинирај класа Profile за репрезентација на профил на социјалните мрежи
 * Секој профил е репрезентиран со
 * -име -низа од макс 15 знаци
 * -број на пријатели(цел бр)
 * -година на раѓање
 * Да се имплементираат потребните конструктори деструктори и функции во класата
 * Преоптоварување на класата со следните оператори
 * == за проверка на еднаквост на два профила според бр на пријатели
 * > за споредба на два профила според година на раѓање
 * ++ во префикс и постфикс нотација за зголемување на бр на пријатели
 * >> за печатење на податоците
 *  << за читање на податоците
 *   + за собирање на два профила (името ќе биде кованица ,пријателите се собираат ,а за
 *   годината се зима поголемата година
 * Дефинирај класа SocialMedia за која ќе има низа од макс 15 знаци и динамичка алоцирана низа од елементи од класа Профил и бр на профили */
using namespace std;
#include <iostream>
#include <cstring>
class Profile {
private:
    char name[15];
    int br_prijateli;
    int godina;
public:
    friend ostream& operator<<(ostream &o,Profile &p) ;
    friend  istream& operator>>(istream &o,Profile &p);

    Profile(){
        strcpy(name," ");
        br_prijateli=0;
        godina=0;
    }
    Profile(char *name,int br_prijateli,int godina) {
        strcpy(this->name,name);
        this->br_prijateli=br_prijateli;
        this->godina=godina;
    }
    void print() {
        cout<<name<<" "<<br_prijateli<<" "<<godina<<endl;
    }
    bool operator==(Profile m) {
        if (br_prijateli==m.br_prijateli) return true;
        else return false;
    }
    bool operator>(Profile m) {
        if (godina<m.godina) return true;
        else return false;
    }
    // postfix p++;
    Profile operator++(int) {
        Profile temp(*this);
        br_prijateli++;
        return temp;//vrakjash profilot pred da mu se izmenat prijatelite
    }
    //tipot na fukncijata e Profile a ne void za da mozhe da se napravat
    // stvari kao Profile p3=p++; i da se dodeli direktno na p3;
    //a ako beshe void nisho nema da vrakjashe
    //prefix ++p
    //ima & zasto go vrakash this so * i direktno vlijaesh na objektot
    Profile& operator++() {
        br_prijateli++;
        return *this;
    }
    Profile& operator+=(int n){
        br_prijateli+=n;
        return *this;
    }
    // gi zgolemuva br na prijateli pritoa toa go pravi
    // gradejki kopija,originalot ne go chepka,
    //za da mozhe da napravi p3=(p+1)
    //istovo nema da fukncionira so p3=1+p
   Profile operator+(int m) {
        Profile tmp(name,br_prijateli+m,godina);
        return tmp;
    }
    friend Profile operator+(int m,Profile k);
    friend Profile operator&(Profile k,Profile m);
};
Profile operator&(Profile k,Profile m) {
  char name[30];
    int pogolema_godina;
    if (m.godina<k.godina) pogolema_godina=m.godina;
    else pogolema_godina=k.godina;
    strcat(k.name,m.name);
    strcpy(name,k.name);
    Profile temp(name,k.br_prijateli+m.br_prijateli,pogolema_godina);
    return temp;

}
Profile operator+(int m,Profile k)
{
    Profile tmp(k.name,k.br_prijateli+m,k.godina);
    return tmp;

}
 ostream& operator<<(ostream &o,Profile &p) {
    o<<p.name<<" "<<p.br_prijateli<<" "<<p.godina<<endl;
    return o;
}
  istream& operator>>(istream &o,Profile &p) {
    cout<<"Vnesi ime ";
    o>>p.name;
    cout<<endl;
    cout<<"Vnesi br na prijateli ";
    o>>p.br_prijateli;
    cout<<endl;
    cout<<"Vnesi godina na ragjanje :";
    o>>p.godina;
    return o;
}
int main() {
  Profile p1("Mitre",200,1999);
    Profile p2("Katerina",300,2000);
    Profile p3;
    cin>>p3;
    p3=(8+p2);//vaka na p3 mu se prenesuva i imeto od p2;
    cout<<p3;
    (p1+3).print();
    if (p1==p2) {
        cout<<"Isti se"<<endl;
    }
    else cout<<"Ne se isti"<<endl;
    if (p1>p2) {
        cout<<"Prviot korisnik e postar"<<endl;
        cout<<p1<<endl;
    }
    else {
        cout<<"Vtoriot korisnik e postar"<<endl;
        cout<<p2<<endl;
    }
    (p1&p2).print();
    return 0;
}