#include <iostream>
#include <cstring>
using namespace std;

#include <iostream>
#include <cstring>
using namespace std;

class IceCream {
private:
    char *name;
    char sostav[100];
    float price;
    int popust;

public:
    IceCream() {
        name = nullptr;
        price = 0;
        popust = 0;
    }

    IceCream(char *name, char *sostav, float price) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->sostav, sostav);
        this->price = price;
        this->popust = 0;
    }

    IceCream(const IceCream &other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        strcpy(sostav, other.sostav);
        price = other.price;
        popust = other.popust;
    }

    IceCream &operator=(const IceCream &other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            strcpy(sostav, other.sostav);
            price = other.price;
            popust = other.popust;
        }
        return *this;
    }

    ~IceCream() {
        delete[] name;
    }

    friend ostream &operator<<(ostream &os, const IceCream &ic) {
        os << ic.name << ": " << ic.sostav << " " << ic.price;
        if (ic.popust > 0) {
            float discounted = ic.price * (1 - ic.popust / 100.0);
            os << " (" << discounted << ")";
        }
        return os;
    }

    IceCream &operator++() {
        popust += 5;
        if (popust > 100) popust = 100;
        return *this;
    }

    IceCream operator+(char *suffix) const {
        IceCream temp(*this);

        int newLen = strlen(name) + strlen(suffix) + 4;
        char *newName = new char[newLen];

        strcpy(newName, name);
        strcat(newName, " + ");
        strcat(newName, suffix);

                // delete[] temp.name;
        temp.name = newName;
        temp.name= new char [newLen];
     strcpy(temp.name,newName);

        temp.price += 10;
        return temp;
    }

    void setDiscount(int discount) {
        if (discount < 0) discount = 0;
        if (discount > 100) discount = 100;
        popust = discount;
    }

    void setName(char* newName) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }
};

class IceCreamShop {
private:
    char name[50];
    IceCream *sladoledi;
    int broj;

public:
    IceCreamShop() {
        strcpy(name, "");
        broj = 0;
        sladoledi = nullptr;
    }

    IceCreamShop(char *name) {
        strcpy(this->name, name);
        broj = 0;
        sladoledi = nullptr;
    }

    IceCreamShop(const IceCreamShop &other) {
        strcpy(name, other.name);
        broj = other.broj;
        sladoledi = new IceCream[broj];
        for (int i = 0; i < broj; ++i)
            sladoledi[i] = other.sladoledi[i];
    }

    IceCreamShop &operator=(const IceCreamShop &other) {
        if (this != &other) {
            delete[] sladoledi;
            strcpy(name, other.name);
            broj = other.broj;
            sladoledi = new IceCream[broj];
            for (int i = 0; i < broj; ++i)
                sladoledi[i] = other.sladoledi[i];
        }
        return *this;
    }

    ~IceCreamShop() {
        delete[] sladoledi;
    }

    IceCreamShop &operator+=(IceCream &ic) {
        IceCream *temp = new IceCream[broj + 1];
        for (int i = 0; i < broj; ++i)
            temp[i] = sladoledi[i];
        temp[broj++] = ic;
        delete[] sladoledi;
        sladoledi = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {
        os << shop.name << endl;
        for (int i = 0; i < shop.broj; ++i) {
            os << shop.sladoledi[i] << endl;
        }
        return os;
    }
};
// zabraneto e menuvanje na main funkcijata

    int main() {
        char name[100];
        char ingr[100];
        float price;
        int discount;

        int testCase;

        cin >> testCase;
    	cin.get();
        if(testCase == 1) {
            cout << "====== TESTING IceCream CLASS ======" << endl;
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            cin >> discount;
            cout << "CONSTRUCTOR" << endl;
            IceCream ic1(name, ingr, price);
            ic1.setDiscount(discount);
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            cin >> discount;
            IceCream ic2(name, ingr, price);
            ic2.setDiscount(discount);
            cout << "OPERATOR <<" << endl;
            cout << ic1 << endl;
            cout << ic2 << endl;
            cout << "OPERATOR ++" << endl;
            ++ic1;
            cout << ic1 << endl;
            cout << "OPERATOR +" << endl;
            IceCream ic3 = ic2 + "chocolate";
            cout << ic3 << endl;
        } else if(testCase == 2) {
            cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            cout << "CONSTRUCTOR" << endl;
            IceCream ic1(name, ingr, price);
            cout << ic1 << endl;
            cout << "COPY CONSTRUCTOR" << endl;
            IceCream ic2(ic1);
            cin.get();
            cin.getline(name,100);
            ic2.setName(name);
            cout << ic1 << endl;
            cout << ic2 << endl;
            cout << "OPERATOR =" << endl;
            ic1 = ic2;
            cin.getline(name,100);
            ic2.setName(name);
            cout << ic1 << endl;
            cout << ic2 << endl;

            cin >> discount;
            ic1.setDiscount(discount);


        } else if(testCase == 3) {
            cout << "====== TESTING IceCreamShop ======" << endl;
            char icsName[50];
            cin.getline(icsName,100);
            cout << "CONSTRUCTOR" << endl;
            IceCreamShop ics(icsName);
            int n;
            cin >> n;
            cout << "OPERATOR +=" << endl;
            for(int i = 0; i < n; ++i) {
                cin.get();
                cin.getline(name,100);
            	cin.getline(ingr,100);
                cin >> price;
                IceCream ic(name, ingr, price);
                ics += ic;
            }
            cout << ics;
        } else if(testCase == 4) {
            cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
            char icsName[50];
            cin.getline(icsName,100);
            IceCreamShop ics(icsName);
            int n;
            cin >> n;
            for(int i = 0; i < n; ++i) {
                cin.get();
                cin.getline(name,100);
            	cin.getline(ingr,100);
                cin >> price;
                IceCream ic(name, ingr, price);
                ics += ic;
            }
            IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
            IceCreamShop icp = ics;
            ics+=x;
            cout << ics << endl;
            cout << icp << endl;
        }


        return 0;
    }

