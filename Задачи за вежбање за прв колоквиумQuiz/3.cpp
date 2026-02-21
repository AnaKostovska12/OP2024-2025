#include <iostream>
#include <cstring>
using namespace std;

class StockRecord {
private:
    char ID[12];
    char name[50];
    double cena_k;
    double cena_m;
    int broj;

public:
    StockRecord() {
        strcpy(ID, "");
        strcpy(name, "");
        cena_k = 0;
        cena_m = 0;
        broj = 0;
    }

    StockRecord(char *id, char *name, double k, int broj) {
        strcpy(ID, id);
        strcpy(this->name, name);
        cena_k = k;
        cena_m = k; // cena_m defaults to cena_k initially
        this->broj = broj;
    }

    void setNewPrice(double price) {
        cena_m = price;
    }

    double value() const {
        return broj * cena_m;
    }

    double profit() const {
        return broj * (cena_m - cena_k);
    }

    friend ostream &operator<<(ostream &out, const StockRecord &r) {
        out << r.name << " " << r.broj << " " << r.cena_k << " " << r.cena_m << " " << r.profit()<<endl;
        return out;
    }
};

class Client {
private:
    char name[60];
    int id;
    StockRecord *niza;
    int broj;

public:
    Client() {
        strcpy(name, "");
        id = 0;
        niza = nullptr;
        broj = 0;
    }

    ~Client() {
        delete[] niza;
    }

    Client(char *name, int id) {
        strcpy(this->name, name);
        this->id = id;
        broj = 0;
        niza = nullptr;
    }

    double totalValue() const {
        double zbir = 0;
        for (int i = 0; i < broj; i++) {
            zbir += niza[i].value();
        }
        return zbir;
    }

    Client &operator+=(const StockRecord &nov) {
        StockRecord *temp = new StockRecord[broj + 1];
        for (int i = 0; i < broj; i++) {
            temp[i] = niza[i];
        }
        temp[broj++] = nov;
        delete[] niza;
        niza = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Client &c) {
        out << c.id << " " << c.totalValue() << endl;
        for (int i = 0; i < c.broj; i++) {
            out << c.niza[i] ;
        }
        return out;
    }
};
int main(){

    int test;
    cin >> test;

    if(test == 1){
    	double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
    	char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
        	cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
    	cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
        	StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
            	cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}