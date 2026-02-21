/* Да се креира структура Engine во која што ќе се чуваат податоци
*за коњска сила / horsepower (int) и вртежен момент / torque (int).
Потоа, да се креира структура Car во која што ќе  се чуваат податоци
името на производителот (char array) , која година е произведена колата
(int) и кој мотор / engine (Engine) која што го користи/
На почетокот се внесува број N што озналува колку коли ќе се читаат од
влез.
Да се направи функцијата:
void printCars(...)

која што ќе ги земе двете коли кои имаат најмала коњска сила, и од нив
две, ќе ја испечати колата што има поголем вртежен момент.*/

#include <iostream>
#include <string.h>
using namespace std;

struct Engine {
    int horsepower;
    int torque;
};
struct Car {
    char array[20];
    int year;
    Engine engine;
};
void printCars(Car *car,int n) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<n-i-1;j++) {
            if (car[j].engine.horsepower>car[j+1].engine.horsepower) {
                Car temp = car[j];
                car[j] = car[j+1];
                car[j+1] = temp;
            }
        }
    }
    if (car[0].engine.torque>car[1].engine.torque) {

        cout<<car[0].array;

    }
    else {

        cout<<car[1].array;

    }
}

int main() {
    int n;
    cin>>n;
    cin.ignore();
    Car car[n];
    for (int i=0;i<n;i++) {
        cin.getline(car[i].array,20);
        cin>>car[i].year;
        cin>>car[i].engine.horsepower;
        cin>>car[i].engine.torque;
        cin.ignore();
    }
    printCars(car,n);
    return 0;
}