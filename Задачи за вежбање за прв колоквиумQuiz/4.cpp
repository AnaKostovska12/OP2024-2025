#include <iostream>
#include <cstring>
using namespace std;

class Patnik {
private:
    char name[100];
    int klasa;
    bool velosiped;

public:
    Patnik() {
        strcpy(name, "");
        klasa = 1;
        velosiped = false;
    }

    Patnik(const char *name, int klasa, bool velosiped) {
        strncpy(this->name, name, 99);
        this->name[99] = '\0';
        this->klasa = klasa;
        this->velosiped = velosiped;
    }

    int getKlasa() const {
        return klasa;
    }

    bool imaVelosiped() const {
        return velosiped;
    }

    friend ostream &operator<<(ostream &os, const Patnik &p) {
        os << p.name << endl;
        os << p.klasa << endl;
        os << p.velosiped << endl << endl;
        return os;
    }
};

class Voz {
private:
    char destinacija[100];
    Patnik *patnici;
    int broj;
    int dozvoleni_vel;

    // ново: бројач за велосипеди од внатре
    int vkupnoVelosipedi;
    int rejectedClass1;
    int rejectedClass2;

public:
    Voz() {
        strcpy(destinacija, "");
        broj = 0;
        dozvoleni_vel = 0;
        patnici = nullptr;
        vkupnoVelosipedi = 0;
        rejectedClass1 = 0;
        rejectedClass2 = 0;
    }

    Voz(const char *destinacija, int max_v) {
        strncpy(this->destinacija, destinacija, 99);
        this->destinacija[99] = '\0';
        broj = 0;
        dozvoleni_vel = max_v;
        patnici = nullptr;
        vkupnoVelosipedi = 0;
        rejectedClass1 = 0;
        rejectedClass2 = 0;
    }

    Voz(const Voz &v) {
        strncpy(destinacija, v.destinacija, 99);
        destinacija[99] = '\0';
        broj = v.broj;
        dozvoleni_vel = v.dozvoleni_vel;
        vkupnoVelosipedi = v.vkupnoVelosipedi;
        rejectedClass1 = v.rejectedClass1;
        rejectedClass2 = v.rejectedClass2;

        patnici = new Patnik[broj];
        for (int i = 0; i < broj; i++) {
            patnici[i] = v.patnici[i];
        }
    }

    Voz &operator=(const Voz &v) {
        if (this != &v) {
            delete[] patnici;
            strncpy(destinacija, v.destinacija, 99);
            destinacija[99] = '\0';
            broj = v.broj;
            dozvoleni_vel = v.dozvoleni_vel;
            vkupnoVelosipedi = v.vkupnoVelosipedi;
            rejectedClass1 = v.rejectedClass1;
            rejectedClass2 = v.rejectedClass2;

            patnici = new Patnik[broj];
            for (int i = 0; i < broj; i++) {
                patnici[i] = v.patnici[i];
            }
        }
        return *this;
    }

    ~Voz() {
        delete[] patnici;
    }

    Voz &operator+=(const Patnik &p) {
        if (p.imaVelosiped()) {
            if (p.getKlasa() == 1) {
                // 1-ва класа патници со велосипед - влегуваат приоритетно
                if (vkupnoVelosipedi < dozvoleni_vel) {
                    vkupnoVelosipedi++;
                } else {
                    rejectedClass1++;
                    return *this;
                }
            } else if (p.getKlasa() == 2) {
                // 2-ра класа патници со велосипед - ако има место после 1-вата класа
                if (vkupnoVelosipedi < dozvoleni_vel) {
                    vkupnoVelosipedi++;
                } else {
                    rejectedClass2++;
                    return *this;
                }
            }
        }

        // Додавање на патникот во низата
        Patnik *temp = new Patnik[broj + 1];
        for (int i = 0; i < broj; i++) {
            temp[i] = patnici[i];
        }
        temp[broj++] = p;
        delete[] patnici;
        patnici = temp;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const Voz &v) {
        os << v.destinacija << endl;
        for (int i = 0; i < v.broj; i++) {
            os << v.patnici[i];
        }
        return os;
    }

    void patniciNemaMesto() {
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << rejectedClass1 << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << rejectedClass2 << endl;
    }
};

int main()
{
	Patnik p;
	char ime[100], destinacija[100];
	int n;
	bool velosiped;
	int klasa;
	int maxv;
	cin >> destinacija >> maxv;
	cin >> n;
	Voz v(destinacija, maxv);
	//cout<<v<<endl;
	for (int i = 0; i < n; i++){
		cin >> ime >> klasa >> velosiped;
		Patnik p(ime, klasa, velosiped);
		//cout<<p<<endl;
		v += p;
	}
	cout << v;
	v.patniciNemaMesto();

	return 0;
}