/* Да се дефинира класа Momche која содржи информации за име, презиме и години.
Да се дефинира класа Devojche со истите атрибути.
Креирајте класа Sredba која содржи податоци за едно момче и едно девојче.
Напишете функција daliSiOdgovaraat() која печати “Si odgovaraat” доколку
разликата на нивните години е помала или еднаква на 5. */

#include <iostream>
#include <cstring>
using namespace std;

class Momche {
private:
    char name[20];
    char surname[20];
    int age;
public:
    Momche(){}
    ~Momche(){}
    Momche(char *namee,char *surnamee,int agee) {
        strcpy(name,namee);
        strcpy(surname,surnamee);
        age=agee;
    }
    void print() {
        cout<<" Momche : "<<name<<" "<<surname<<" "<<age<<endl;
    }

    int getage() {
        return age;
    }
};

class Devojche {
private:
    char name[20];
    char surname[20];
    int age;
public:
    Devojche(){}
    ~Devojche(){}
    Devojche(char *namee,char *surnamee,int agee) {
        strcpy(name,namee);
        strcpy(surname,surnamee);
        age=agee;
    }
    void print() {
        cout<<" Devojche : "<<name<<" "<<surname<<" "<<age<<endl;
    }
    int getage() {
        return age;
    }
};

class Sredba {
private:
    Momche m;
    Devojche d;
public:
    Sredba() {}
    ~Sredba() {}
    Sredba( Momche ma,Devojche da) {
        m=ma;
        d=da;
    }
    void print() {
        cout<<"Sredba: ";
        m.print();
        cout<<" ";
        d.print();
    }
    bool daliSiOdgovaraat() {
        if(abs(m.getage()-d.getage())>5) {
            cout<<"Ne si odgovaraat "<<endl;
        }
        else
            cout<<"Si odgovaraat "<<endl;
    }
};

int main() {
    char mname[20],msurname[20],dname[20],dsurname[20];
    int dage,mage;
    cin>>mname>>msurname>>mage;
    Momche ma(mname,msurname,mage);

    cin>>dname>>dsurname>>dage;
    Devojche da(dname,dsurname,dage);
    Sredba sredba(ma,da);
    sredba.print();
    sredba.daliSiOdgovaraat();
}