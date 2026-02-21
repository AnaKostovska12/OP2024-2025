#include<iostream>
#include<string.h>

using namespace std;

class OutOfBoundException {
public:
    void print() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char *smetka, int pin) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    Karticka(const Karticka &k) {
        strcpy(this->smetka, k.smetka);
        this->pin = k.pin;
        this->povekjePin = k.povekjePin;
    }

    virtual int tezinaProbivanje() {
        int tezina = 0, tmp = pin;
        while (tmp) {
            tmp /= 10;
            ++tezina;
        }
        return tezina;
    }

    const char *getSmetka() const {
        return smetka;
    }

    int getPin() const {
        return pin;
    }

    void setPin(int pin) {
        Karticka::pin = pin;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }

    void setPovekjePin(bool povekjePin) {
        Karticka::povekjePin = povekjePin;
    }

    virtual ~Karticka() {}

    friend ostream &operator<<(ostream &o, Karticka &k) {
        o << k.smetka << ": " << k.tezinaProbivanje()<<endl;
        return o;
    }
};

class SpecijalnaKarticka : public Karticka {
private:
    int *extraPin;
    int n;
    const static int p;
public:
    SpecijalnaKarticka(char *smetka = "", int pin = 0, int *extraPin = 0, int n = 0)
            : Karticka(smetka, pin), n(n) {
        this->extraPin = new int[n];
        for (int i = 0; i < n; ++i) {
            this->extraPin[i] = extraPin[i];
        }
        this->povekjePin = true;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka &o) : Karticka(o) {
        n = o.n;
        extraPin = new int[n];
        for (int i = 0; i < n; ++i) {
            extraPin[i] = o.extraPin[i];
        }
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &sk) {
        if (this != &sk) {
            Karticka::operator=(sk);
            delete[] extraPin;
            this->n = sk.n;
            this->extraPin = new int[n];
            for (int i = 0; i < n; ++i) {
                extraPin[i] = sk.extraPin[i];
            }
        }
        return *this;
    }

    ~SpecijalnaKarticka() override {
        delete[] extraPin;
    }

    int *getExtraPin() const {
        return extraPin;
    }

    void setExtraPin(int *extraPin) {
        SpecijalnaKarticka::extraPin = extraPin;
    }

    int getN() const {
        return n;
    }

    void setN(int n) {
        SpecijalnaKarticka::n = n;
    }

    static const int getP() {
        return p;
    }

    int tezinaProbivanje() {
        return (Karticka::tezinaProbivanje() + n);
    }

    friend ostream &operator<<(ostream &os, SpecijalnaKarticka &karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje();
        return os;
    }

    SpecijalnaKarticka &operator+=(int pin) {
        if (n >= p) {
            throw OutOfBoundException();
        } else {
            int *tmp = new int[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = extraPin[i];
            }
            tmp[n++] = pin;
            delete[] extraPin;
            extraPin = tmp;
            return *this;
        }
    }
};

const int SpecijalnaKarticka::p = 4;


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka **karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(karticki[i]));
            } else this->karticki[i] = new Karticka(*karticki[i]);
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) delete karticki[i];
    }

    static int getLimit() {
        return LIMIT;
    }

    static void setLIMIT(int limit) {
        LIMIT = limit;
    }

    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:"<<endl;
        for (int i = 0; i < broj; ++i) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i];
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin) {
        for (int i = 0; i < broj; ++i) {
            if(karticki[i]->getDopolnitelenPin()){
                if(strcmp(smetka,karticki[i]->getSmetka())==0){
                    try{
                        *dynamic_cast<SpecijalnaKarticka*>(karticki[i])+=novPin;
                    }
                    catch (OutOfBoundException e){
                        e.print();
                    }
                }
            }
        }
    }
};

int Banka::LIMIT = 7;


int main() {

    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;

        komercijalna.dodadiDopolnitelenPin(smetka, pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}