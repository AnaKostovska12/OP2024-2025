/* Да се напише програма која ќе споредува два датуми (ден, месец, година)
и ќе ја пресмета разликата во денови од едниот до другиот датум.
Пресметките да се реализираат во посебни функции. За датумот да се
дефинира посебна структура. */

#include <iostream>
using namespace std;

struct datum {
    int den;
    int mesec;
    int godina;
};

int redosled(datum d1, datum d2) {
    if (d1.godina > d2.godina) return 1;
    if (d1.godina < d2.godina) return -1;
    if (d1.mesec > d2.mesec) return 1;
    if (d1.mesec < d2.mesec) return -1;
    if (d1.den > d2.den) return 1;
    if (d1.den < d2.den) return -1;
    return 0;
}

int main() {
    datum d1, d2;
    cin >> d1.den >> d1.mesec >> d1.godina;
    cin >> d2.den >> d2.mesec >> d2.godina;

    int order = redosled(d1, d2);
    if (order == -1) {
        datum temp = d1;
        d1 = d2;
        d2 = temp;
    }

    int brojdenovi = (d1.godina - d2.godina) * 365 + (d1.mesec - d2.mesec) * 30 + (d1.den - d2.den);
    cout << "Razlikata vo denovi: " << brojdenovi << endl;

    return 0;
}