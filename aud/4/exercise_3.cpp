/* Да се напише класа Student која треба да чува информации за името на студентот, број на индекс и просек.
Да се дефинираат статички членови кои ќе даваат информации за бројот на студенти и вкупниот просек. Да се
имплементираат статички функции кои ќе го враќаат вкупниот просек и бројот на студенти. Секогаш кога ќе
се креира објект, статичките членови треба да се ажурираат. */

#include <iostream>
#include <cstring>
using namespace std;

class Student {
    char name[100];
    int index;
    float prosek;
    static int broj_studenti;
    static float vkupen_prosek;
public:
    Student() {}
    ~Student() {}
    Student(const char* name, int index, float prosek) {
        strcpy(this->name, name);
        this->index = index;
        this->prosek = prosek;
        broj_studenti ++;
        vkupen_prosek += prosek;
    }

    static void print() {
        cout<<"broj_studenti: "<<broj_studenti<<endl;
        cout<<"vkupen_prosek: "<<vkupen_prosek<<endl;

    }
    void printanje() {
        cout<<name<<" "<<index<<" "<<prosek<<endl;
    }

};

int Student :: broj_studenti=0;
float Student :: vkupen_prosek=0;

int main() {
    Student studenti[100];
    Student student;
    char ime[20];
    int index;
    float prosek;
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>ime>>index>>prosek;
        student=Student(ime,index,prosek);
        studenti[i]=student;
    }
    for(int i=0;i<n;i++) {
        studenti[i].printanje();
    }
    cout<<endl;
    cout<<"sevkupno"<<endl;
    Student::print();

    return 0;
}