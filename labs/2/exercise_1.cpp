/*Да се креира класа Flight со податоци: име на летот, место на
слетување (arrival), место на заминување (departure) -
трите со char, и цена на летот - int. Да се направи default
constructor, copy constructor, constructor со параметри и funkcii geteri:
getFlightName, getArrival, getDeparture.
Потоа, да се креира класа Airport со податоци: име на аеродромот (char) ,
број на летови (int), листа на летови (Flight * flights).
Да се креира конструктор со параметри. Дополнително, да се креира функција во класата - Flight cheapestFlight()
- ќе го враќа најевтиниот лет. */
#include <iostream>
#include <string.h>
using namespace std;

class Flight {
private:
    char name[20];
    char arrival[20];
    char departure[20];
    int price;
public:
    Flight() {}
    Flight(char *n, char *a, char *d, int p) {
        strcpy(name, n);
        strcpy(arrival, a);
        strcpy(departure, d);
        price = p;
    }
    Flight(Flight &f) {
        strcpy(name, f.name);
        strcpy(arrival, f.arrival);
        strcpy(departure, f.departure);
        price = f.price;
    }
    int getPrice() { return price; }
    char *getName() { return name; }
};

class Airport {
private:
    char name[20];
    int broj_letovi;
    Flight *Flights;
    int n;
public:
    Airport() {};
    Airport(char *nameee, int brojj, Flight *Flightss, int nn) {
        strcpy(name, nameee);
        broj_letovi = brojj;
        Flights = Flightss;
        n = nn;
    }
    Flight cheapestflight() {
        Flight min = Flights[0];
        int cena = Flights[0].getPrice();
        for(int i=0; i<n; i++) {
            if (Flights[i].getPrice() < cena) {
                cena = Flights[i].getPrice();
                min = Flights[i];
            }
        }
        return min;
    }
};

int main() {
    Flight letovi[2] = { Flight("W12", "SKP", "LON", 5000), Flight("W13", "SKP", "PAR", 3000) };
    Airport ap("Skopje", 2, letovi, 2);
    Flight евтин = ap.cheapestflight();
    cout << "Cheapest: " << евтин.getName() << " Price: " << евтин.getPrice() << endl;
    return 0;
}