#include <cstring>
#include <iostream>
using namespace std;

class Vozac {
protected:
    char name[100];
    int vozrast;
    int brojTrki;
    bool veteran;

public:
    Vozac(char *name = "", int vozrast = 0, int brojTrki = 0, bool veteran = false) {
        strcpy(this->name, name);
        this->vozrast = vozrast;
        this->brojTrki = brojTrki;
        this->veteran = veteran;
    }

    Vozac(const Vozac &n) {
        strcpy(this->name, n.name);
        this->vozrast = n.vozrast;
        this->brojTrki = n.brojTrki;
        this->veteran = n.veteran;
    }

    Vozac &operator=(const Vozac &n) {
        if (this != &n) {
            strcpy(this->name, n.name);
            this->vozrast = n.vozrast;
            this->brojTrki = n.brojTrki;
            this->veteran = n.veteran;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Vozac& v) {
        os << v.name << endl;
        os << v.vozrast << endl;
        os << v.brojTrki << endl;
        if (v.veteran) {
            os << "VETERAN" << endl;
        }
        return os;
    }

    bool operator==(const Vozac& other) {
        return this->zarabotuvackapoTrka() == other.zarabotuvackapoTrka();
    }

    virtual double zarabotuvackapoTrka() const = 0;
    virtual double zarabotuvacka() const = 0;
    virtual double danok() const = 0;
    virtual ~Vozac() {}
};

class Avtomobilist : public Vozac {
private:
    double cenaAvtomobil;

public:
    Avtomobilist(char *name = "", int vozrast = 0, int brojTrki = 0, bool veteran = false, double cenaAvtomobil = 0)
        : Vozac(name, vozrast, brojTrki, veteran), cenaAvtomobil(cenaAvtomobil) {}

    double zarabotuvackapoTrka() const override {
        return cenaAvtomobil / 5.0;
    }

    double zarabotuvacka() const override {
        return brojTrki * zarabotuvackapoTrka();
    }

    double danok() const override {
        if (brojTrki > 10)
            return zarabotuvackapoTrka() * 0.15;
        else
            return zarabotuvackapoTrka() * 0.10;
    }
};

class Motociklist : public Vozac {
private:
    int moknostMotor;

public:
    Motociklist(char *name = "", int vozrast = 0, int brojTrki = 0, bool veteran = false, int moknostMotor = 0)
        : Vozac(name, vozrast, brojTrki, veteran), moknostMotor(moknostMotor) {}

    double zarabotuvackapoTrka() const override {
        return moknostMotor * 20.0;
    }

    double zarabotuvacka() const override {
        return brojTrki * zarabotuvackapoTrka();
    }

    double danok() const override {
        if (veteran)
            return zarabotuvackapoTrka() * 0.25;
        else
            return zarabotuvackapoTrka() * 0.20;
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *target) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (vozaci[i]->zarabotuvackapoTrka() == target->zarabotuvackapoTrka()) {
            count++;
        }
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;

    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }

    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }

    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);

    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);

    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;

    return 0;
}