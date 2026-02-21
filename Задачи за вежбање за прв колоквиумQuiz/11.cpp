using namespace std;
#include <iostream>
#include <cstring>

class Maraton;

class Ucesnik {
    friend class Maraton;

    char *name;
    bool pol;
    int vozrast;

public:
    Ucesnik() {
        name = nullptr;
        pol = false;
        vozrast = 0;
    }

    Ucesnik(char *name, bool pol, int vozrast) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->pol = pol;
        this->vozrast = vozrast;
    }

    Ucesnik(const Ucesnik &other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        pol = other.pol;
        vozrast = other.vozrast;
    }

    Ucesnik &operator=(const Ucesnik &other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            pol = other.pol;
            vozrast = other.vozrast;
        }
        return *this;
    }

    ~Ucesnik() {
        delete[] name;
    }

    bool operator>(const Ucesnik &u) const {
        return vozrast > u.vozrast;
    }

    friend ostream &operator<<(ostream &os, const Ucesnik &u) {
        os << u.name << endl;
        os << (u.pol ? "mashki" : "zhenski") << endl;
        os << u.vozrast << endl;
        return os;
    }
};

class Maraton {
private:
    char lokacija[100];
    Ucesnik *ucesnici;
    int broj;

public:
    Maraton() {
        strcpy(lokacija, "");
        ucesnici = nullptr;
        broj = 0;
    }

    Maraton(char *lokacija) {
        strcpy(this->lokacija, lokacija);
        broj = 0;
        ucesnici = nullptr;
    }

    ~Maraton() {
        delete[] ucesnici;
    }

    Maraton(const Maraton &m) {
        strcpy(this->lokacija, m.lokacija);
        broj = m.broj;
        ucesnici = new Ucesnik[broj];
        for (int i = 0; i < broj; i++) {
            ucesnici[i] = m.ucesnici[i];
        }
    }

    Maraton &operator=(const Maraton &m) {
        if (this != &m) {
            delete[] ucesnici;
            strcpy(this->lokacija, m.lokacija);
            broj = m.broj;
            ucesnici = new Ucesnik[broj];
            for (int i = 0; i < broj; i++) {
                ucesnici[i] = m.ucesnici[i];
            }
        }
        return *this;
    }

    Maraton &operator+=(const Ucesnik &u) {
        Ucesnik *temp = new Ucesnik[broj + 1];
        for (int i = 0; i < broj; i++) {
            temp[i] = ucesnici[i];
        }
        temp[broj++] = u;
        delete[] ucesnici;
        ucesnici = temp;
        return *this;
    }

    float prosecnoVozrast() {
        int zbir = 0;
        for (int i = 0; i < broj; i++) {
            zbir += ucesnici[i].vozrast;
        }
        return broj ? (float)zbir / broj : 0;
    }

    void pecatiPomladi(Ucesnik &u) {
        for (int i = 0; i < broj; i++) {
            if (ucesnici[i].vozrast < u.vozrast) {
                cout << ucesnici[i];
            }
        }
    }
};
int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
    	u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
	m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
	return 0;
}
