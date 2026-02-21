#include <iostream>
#include <cstring>
using namespace std;

class Zichara {
private:
    char *mesto;
    int karta;
public:
    Zichara() {
        mesto = new char[1];
        mesto[0] = '\0';
        karta = 0;
    }

    Zichara(char *mesto, int karta) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
        this->karta = karta;
    }

    Zichara(const Zichara &n) {
        this->mesto = new char[strlen(n.mesto) + 1];
        strcpy(this->mesto, n.mesto);
        this->karta = n.karta;
    }

    Zichara &operator=(const Zichara &n) {
        if (this != &n) {
            delete[] this->mesto;
            this->mesto = new char[strlen(n.mesto) + 1];
            strcpy(this->mesto, n.mesto);
            this->karta = n.karta;
        }
        return *this;
    }

    ~Zichara() {
        delete[] mesto;
    }

    int getPrice() const {
        return karta;
    }
};

class PlaninarskiDom {
private:
    char name[15];
    int ceni[2];
    char klasa;
    bool zicaraPostoi;
    Zichara *zichara;

public:
    PlaninarskiDom() {
        strcpy(name, "");
        ceni[0] = ceni[1] = 0;
        klasa = 'A';
        zicaraPostoi = false;
        zichara = nullptr;
    }

    PlaninarskiDom(char *name, int *ceni, char klasa) {
        strcpy(this->name, name);
        this->ceni[0] = ceni[0];
        this->ceni[1] = ceni[1];
        this->klasa = klasa;
        zicaraPostoi = false;
        zichara = nullptr;
    }

    PlaninarskiDom(char *name, int *ceni, char klasa, Zichara *zichara) {
        strcpy(this->name, name);
        this->ceni[0] = ceni[0];
        this->ceni[1] = ceni[1];
        this->klasa = klasa;
        this->zichara = new Zichara(*zichara);
        this->zicaraPostoi = true;
    }

    PlaninarskiDom(const PlaninarskiDom &n) {
        strcpy(this->name, n.name);
        this->ceni[0] = n.ceni[0];
        this->ceni[1] = n.ceni[1];
        this->klasa = n.klasa;
        this->zicaraPostoi = n.zicaraPostoi;

        if (n.zicaraPostoi) {
            this->zichara = new Zichara(*n.zichara);
        } else {
            this->zichara = nullptr;
        }
    }

    PlaninarskiDom &operator=(const PlaninarskiDom &n) {
        if (this != &n) {
            strcpy(this->name, n.name);
            this->ceni[0] = n.ceni[0];
            this->ceni[1] = n.ceni[1];
            this->klasa = n.klasa;
            this->zicaraPostoi = n.zicaraPostoi;

            if (zicaraPostoi) {
                delete this->zichara;
                this->zichara = nullptr;
            }

            if (n.zicaraPostoi) {
                this->zichara = new Zichara(*n.zichara);
            } else {
                this->zichara = nullptr;
            }
        }
        return *this;
    }

    ~PlaninarskiDom() {
        if (zicaraPostoi)
            delete zichara;
    }

    void setZichara(const Zichara &zichara) {
        if (zicaraPostoi) delete this->zichara;
        this->zichara = new Zichara(zichara);
        this->zicaraPostoi = true;
    }

    PlaninarskiDom &operator--() {
        if (klasa < 'F') {
            klasa++;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const PlaninarskiDom &n) {
        os << n.name << " klasa:" << n.klasa;
        if (n.zicaraPostoi) {
            os << " so Zichara" << endl;
        } else {
            os << endl;
        }
        return os;
    }

    bool operator<=(const char n) const {
        return klasa >= n;
    }

    void presmetajDnevenPrestoj(int day, int month, int &pr) {
        pr = 0;

        if (month < 1 || month > 12 || day < 1 || day > 31)
            throw -1;

        if (zicaraPostoi)
            pr += zichara->getPrice();

        if ((month >= 4 && month <= 8) || (month == 9 && day == 1))
            pr += ceni[0]; // letna sezona
        else
            pr += ceni[1]; // zimska sezona
    }
};


int main() {
    PlaninarskiDom p;

    char imePlaninarskiDom[15], mestoZichara[30], klasa;
    int ceni[2];
    int dnevnakartaZichara;
    bool daliZichara;
    cin >> imePlaninarskiDom;
    for (int i = 0; i < 2; i++) cin >> ceni[i];
    cin >> klasa;
    cin >> daliZichara;

    if (daliZichara) {
        cin >> mestoZichara >> dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom, ceni, klasa);
        Zichara r(mestoZichara, dnevnakartaZichara);
        pom.setZichara(r);
        p = pom;
    } else {
        PlaninarskiDom *pok = new PlaninarskiDom(imePlaninarskiDom, ceni, klasa);
        p = *pok;
        delete pok;
    }

    --p;
    --p;

    int cena, den, mesec;
    cin >> den >> mesec;

    try {
        p.presmetajDnevenPrestoj(den, mesec, cena);
        cout << "Informacii za PlaninarskiDomot:" << endl;
        cout << p;
        if (p <= 'D')
            cout << "Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";
        cout << "Cenata za " << den << "." << mesec << " e " << cena;
    } catch (int) {
        cout << "Mesecot ili denot e greshno vnesen!";
    }
}
