/* Да се напише програма која од стандарден влез ќе чита податоци за држави
и на екран ќе го отпечати името и презимето на претседателот на државата чиj
што главен град има најмногу жители. Податоци за држава: име, претседател,
главен град, број на жители. Податоци за град: име, број на жители.
Податоци за претседател: име, презиме, политичка партија. */

#include <iostream>
#include <cstring>
using namespace std;

struct glaven_grad {
    char ime[20];
    int broj_ziteli;
};

struct president {
    char ime[20];
    char prezime[20];
    char partija[20];
};

struct drzava {
    char ime_drzava[20];
    int broj_gragjani;
    president Pretsedatel;
    glaven_grad Glaven;
};

void max_capital(int n, drzava niza[]) {
    int max_index = 0;
    for (int i = 1; i < n; i++) {
        if (niza[i].Glaven.broj_ziteli > niza[max_index].Glaven.broj_ziteli) {
            max_index = i;
        }
    }
    cout << niza[max_index].Pretsedatel.ime << " " << niza[max_index].Pretsedatel.prezime << endl;
}

int main() {
    drzava niza[100];
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> niza[i].ime_drzava >> niza[i].broj_gragjani;
        cin >> niza[i].Pretsedatel.ime >> niza[i].Pretsedatel.prezime >> niza[i].Pretsedatel.partija;
        cin >> niza[i].Glaven.ime >> niza[i].Glaven.broj_ziteli;
    }

    max_capital(n, niza);
    return 0;
}