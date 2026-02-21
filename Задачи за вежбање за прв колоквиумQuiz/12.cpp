#include <iostream>
#include <cstring>
using namespace std;

class Picerija;

class Pica {
private:
    friend class Picerija;
    char name[15];
    int cena;
    char sostojki[100];
    int popust;

public:
    Pica() {
        popust = 0;
    }

    ~Pica() {}

    Pica(char *namee, int cenaa, char *sostojkii, int popustt) {
        strcpy(this->name, namee);
        this->cena = cenaa;
        this->popust = popustt;
        strcpy(this->sostojki, sostojkii);
    }

    Pica(const Pica& n) {
        strcpy(name, n.name);
        cena = n.cena;
        strcpy(sostojki, n.sostojki);
        popust = n.popust;
    }

    void pecati() {
        cout << name << " " << sostojki << " " << cena << endl;
    }

    bool istiSe(Pica p) {
        if (strcmp(sostojki, p.sostojki) == 0) {
            return true;
        }
        return false;
    }

    void setIme(char *ime) {
        strcpy(name, ime);
    }

    int getPopust() {
        return popust;
    }

    void pecatiPopust() {
        // Print the pizza with the discount
        cout << name << " - " << sostojki << ", " << cena << " "
             << cena * 1.0 * (100 - popust) / 100 << endl;
    }
};

class Picerija {
private:
    friend class Pica;
    char name[15];
    Pica pici[30];
    int broj_pici;

public:
    Picerija(char *namee) {
        strcpy(name, namee);
        broj_pici = 0;
    }

    ~Picerija() {}

    Picerija(char *namee, Pica *picii, int brojj) {
        strcpy(this->name, namee);
        this->broj_pici = brojj;
        for (int i = 0; i < brojj; i++) {
            pici[i] = picii[i];
        }
    }

    void dodadiPica(Pica p) {
        int counter = 0;
        for (int i = 0; i < broj_pici; i++) {
            if (pici[i].istiSe(p)) {
                counter++;
            }
        }
        if (counter == 0) {
            pici[broj_pici++] = p;
        }
    }

    void setIme(char *ime) {
        strcpy(name, ime);
    }

    char* getIme() {
        return name;
    }

    void piciNaPromocija() {
        for (int i = 0; i < broj_pici; i++) {
            if (pici[i].getPopust() > 0) {
                // Use pecatiPopust to print discounted pizza
                pici[i].pecatiPopust();
            }
        }
    }
};

int main() {
    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);

    for (int i = 0; i < n; i++) {
        char imp[100];
        cin.ignore();  // To clear the newline character after cin >> n
        cin.getline(imp, 100);  // Get the name of the pizza

        int cena;
        cin >> cena;

        char sostojki[100];
        cin.ignore();  // Clear the newline character before next getline
        cin.getline(sostojki, 100);  // Get the ingredients of the pizza

        int popust;
        cin >> popust;

        Pica p(imp, cena, sostojki, popust);
        p1.dodadiPica(p);
    }

    Picerija p2 = p1;  // Copy the pizzas from p1 to p2
    cin >> ime;
    p2.setIme(ime);

    char imp[100];
    cin.ignore();  // To clear the newline character after cin
    cin.getline(imp, 100);  // Get the name of the pizza
    int cena;
    cin >> cena;

    char sostojki[100];
    cin.ignore();  // Clear the newline character before next getline
    cin.getline(sostojki, 100);  // Get the ingredients of the pizza

    int popust;
    cin >> popust;

    Pica p(imp, cena, sostojki, popust);
    p2.dodadiPica(p);

    // Printing pizzas in both Picerija objects
    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();  // Print promotional pizzas for p1

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();  // Print promotional pizzas for p2

    return 0;
}