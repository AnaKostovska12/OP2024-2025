#include <iostream>
#include <cstring>
using namespace std;

class Transport {
protected:
    char destinacija[21];
    int cena;
    int rastojanie;
public:
    Transport() {
        strcpy(destinacija, "");
        cena = 0;
        rastojanie = 0;
    }
    Transport(char *destinacija, int cena, int rastojanie) {
        strcpy(this->destinacija, destinacija);
        this->cena = cena;
        this->rastojanie = rastojanie;
    }
    Transport(const Transport &n) {
        strcpy(this->destinacija, n.destinacija);
        this->cena = n.cena;
        this->rastojanie = n.rastojanie;
    }
    Transport &operator=(const Transport &n) {
        if (this != &n) {
            strcpy(this->destinacija, n.destinacija);
            this->cena = n.cena;
            this->rastojanie = n.rastojanie;
        }
        return *this;
    }
    virtual float cenaTransport() = 0;
    virtual ~Transport() {}
    bool operator<(const Transport &n) {
        return this->rastojanie < n.rastojanie;
    }
    int getRastojanie() const {
        return rastojanie;
    }
    const char* getDestinacija() const {
        return destinacija;
    }
};

class AvtomobilTransport : public Transport {
private:
    bool privaten_vozac;
public:
    AvtomobilTransport() {
        privaten_vozac = false;
    }
    AvtomobilTransport(char *destinacija, int cena, int rastojanie, bool privaten_vozac)
        : Transport(destinacija, cena, rastojanie) {
        this->privaten_vozac = privaten_vozac;
    }
    AvtomobilTransport &operator=(const AvtomobilTransport &n) {
        if (this != &n) {
            Transport::operator=(n);
            this->privaten_vozac = n.privaten_vozac;
        }
        return *this;
    }
    AvtomobilTransport(const AvtomobilTransport &n)
        : Transport(n) {
        this->privaten_vozac = n.privaten_vozac;
    }
    float cenaTransport() override {
        if (privaten_vozac) {
            return cena * 1.2;
        } else {
            return cena;
        }
    }
};

class KombeTransport : public Transport {
private:
    int br_lugje;
public:
    KombeTransport() {
        br_lugje = 0;
    }
    KombeTransport(char *destinacija, int cena, int rastojanie, int br_lugje)
        : Transport(destinacija, cena, rastojanie) {
        this->br_lugje = br_lugje;
    }
    KombeTransport &operator=(const KombeTransport &n) {
        if (this != &n) {
            Transport::operator=(n);
            this->br_lugje = n.br_lugje;
        }
        return *this;
    }
    KombeTransport(const KombeTransport &n) : Transport(n) {
        this->br_lugje = n.br_lugje;
    }
    float cenaTransport() override {
        return cena - (200 * br_lugje);
    }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, AvtomobilTransport nov) {
    Transport **poskapi = new Transport *[n];
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (ponudi[i]->cenaTransport() > nov.cenaTransport()) {
            poskapi[m++] = ponudi[i];
        }
    }

    // manual sorting by rastojanie
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (*poskapi[j] < *poskapi[i]) {
                Transport* temp = poskapi[i];
                poskapi[i] = poskapi[j];
                poskapi[j] = temp;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        cout << poskapi[i]->getDestinacija() << " " << poskapi[i]->getRastojanie() << " " << poskapi[i]->cenaTransport() << endl;
    }

    delete[] poskapi;
}

int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
