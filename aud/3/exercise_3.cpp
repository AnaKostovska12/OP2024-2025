/* Да се напише класа Datum (ден, месец, година).
Да се напише класа Vraboten (име, плата, датум на раѓање).
Да се напишат функции кои го враќаат вработениот со најголема плата
и најмладиот вработен во фирмата. */

#include <iostream>
#include <cstring>
using namespace std;

class Datum {
private:
    int den;
    int mesec;
    int godina;
    public:
    Datum() {
        den=0;
        mesec=0;
        godina=0;
    };
    Datum(int denn, int mesecc, int godinaa) {
        this->den = denn;
        this->mesec = mesecc;
        this->godina = godinaa;
    };
    void print() {
        cout << den << " " << mesec << " " << godina;
    }
    int getmesec() {
        return mesec;
    }
    int getgodina() {
        return godina;
    }
    int getden() {
        return den;
    }

};

class Vraboten {
    private:
    char name[20];
    int plata;
    Datum rodenden;
    public:
    Vraboten() {}
    Vraboten( char *namee,int plata, Datum rodenden) {
        this->plata = plata;
        this->rodenden = rodenden;
        strcpy(this->name,namee);
    }
    int get_plata() {
        return plata;
    }
    void print() {
        cout<<"Name: "<<name<<endl;
        cout<<"Plata: "<<plata<<endl;
        rodenden.print();
        cout << endl;
    }
    Datum getrodenden() {
        return rodenden;
    }
};

bool sporedba(Datum d1,Datum d2) {
    if (d1.getgodina()<d2.getgodina()) {
        return true;
    }
   else if (d1.getgodina()==d2.getgodina()) {
        if (d1.getmesec()<d2.getmesec()) {
            return true;
        }
    }
    if (d1.getgodina()==d2.getgodina()) {
        if (d1.getmesec()==d2.getmesec()) {
            if (d1.getden()<=d2.getden()) {
                return true;
            }
        }
    }
    return false;
}

Vraboten najmlad(Vraboten *niza,int n) {
    Datum temp = niza[0].getrodenden();
    Vraboten vraboten = niza[0];
    for(int i=1; i<n; i++) {
        if (sporedba(temp, niza[i].getrodenden())) {
            vraboten = niza[i];
            temp = niza[i].getrodenden();
        }
    }
    return vraboten;
}

Vraboten najgolemPlata(Vraboten *niza,int n) {
    int temp = niza[0].get_plata();
    Vraboten vraboten = niza[0];
    for(int i=1; i<n; i++) {
        if (niza[i].get_plata() >= temp) {
            temp = niza[i].get_plata();
            vraboten = niza[i];
        }
    }
    return vraboten;
}

int main() {
    Datum d1(1, 1, 1980);
    Datum d2(1, 2, 1983);
    Datum d3(11, 12, 1984);

    Vraboten v[3];
    Vraboten v1("Marjan", 40000, d1);
    Vraboten v2("Stefan", 30000, d2);
    Vraboten v3("Marko", 20000, d3);
    v[0] = v1;   v[1] = v2;   v[2] = v3;

    cout << "Najmlad vraboten: " << endl;
    najmlad(v, 3).print();

    cout << "Vraboten so najgolema plata: " << endl;
    najgolemPlata(v, 3).print();

    return 0;
}