#include <iostream>
#include <cstring>
using namespace std;

enum tip {
    mobilen, laptop
};

class InvalidProductionDate {
public:
    InvalidProductionDate() {}
    void print() {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
protected:
    char model[101];
    tip ured;
    int godinaProizvodstvo;
    static float osnovnaProverka;

public:
    Device() {
        strcpy(model, "");
        ured = laptop;
        godinaProizvodstvo = 0;
    }

    Device(char *model, tip ured, int godinaProizvodstvo) {
        strcpy(this->model, model);
        this->ured = ured;
        this->godinaProizvodstvo = godinaProizvodstvo;

    }

    Device(const Device &n) {
        strcpy(this->model, n.model);
        this->ured = n.ured;
        this->godinaProizvodstvo = n.godinaProizvodstvo;
    }

    Device &operator=(const Device &n) {
        if (this != &n) {
            strcpy(this->model, n.model);
            this->ured = n.ured;
            this->godinaProizvodstvo = n.godinaProizvodstvo;
        }
        return *this;
    }

    int getGodina() const {
        return godinaProizvodstvo;
    }

    static void setPocetniCasovi(float n) {
        osnovnaProverka = n;
    }

    float proverka() const {
        float check = osnovnaProverka;
        if (godinaProizvodstvo > 2015)
            check += 2;
        if (ured == laptop)
            check += 2;
        return check;
    }

    friend ostream &operator<<(ostream &os, const Device &n) {
        os << n.model << endl;
        os << (n.ured == laptop ? "Laptop" : "Mobilen") << " " << n.proverka() << endl;
        return os;
    }
};

float Device::osnovnaProverka = 1;

class MobileServis {
private:
    char adresa[100];
    Device *niza;
    int broj;

public:
    MobileServis() {
        strcpy(adresa, "");
        broj = 0;
        niza = nullptr;
    }

    MobileServis(char *adresa) {
        strcpy(this->adresa, adresa);
        broj = 0;
        niza = nullptr;
    }

    MobileServis(const MobileServis &m) {
        strcpy(adresa, m.adresa);
        broj = m.broj;
        niza = new Device[broj];
        for (int i = 0; i < broj; ++i) {
            niza[i] = m.niza[i];
        }
    }

    MobileServis &operator=(const MobileServis &m) {
        if (this != &m) {
            delete[] niza;
            strcpy(adresa, m.adresa);
            broj = m.broj;
            niza = new Device[broj];
            for (int i = 0; i < broj; ++i) {
                niza[i] = m.niza[i];
            }
        }
        return *this;
    }

    ~MobileServis() {
        delete[] niza;
    }

    MobileServis &operator+=(const Device &d) {
        if (d.getGodina() > 2019 || d.getGodina() < 2000) {
            throw InvalidProductionDate();
        }

        Device *tmp = new Device[broj + 1];
        for (int i = 0; i < broj; ++i) {
            tmp[i] = niza[i];
        }
        tmp[broj++] = d;
        delete[] niza;
        niza = tmp;

        return *this;
    }

    void pecatiCasovi() const {
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < broj; ++i) {
            cout << niza[i];
        }
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime >> tipDevice >> godina;
        Device ig(ime, (tip)tipDevice, godina);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; ++i) {
            cin >> ime >> tipDevice >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; ++i) {
            cin >> ime >> tipDevice >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; ++i) {
            cin >> ime >> tipDevice >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; ++i) {
            cin >> ime >> tipDevice >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }
    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; ++i) {
            cin >> ime >> tipDevice >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;
}
