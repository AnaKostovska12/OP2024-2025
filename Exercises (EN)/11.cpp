#include <iostream>
#include <cstring>
using namespace std;

class InvalidDiscount {
private:
    int discount;
public:
    InvalidDiscount() {
        discount = 0;
    }
    InvalidDiscount(int discount) {
        this->discount = discount;
    }
    void print() {
        cout << "Invalid discount value: " << discount << endl;
    }
};

class IceCream {
protected:
    char *name;
    char ingredients[100];
    float price;
    int discount; // Changed from static to instance variable
public:
    IceCream() {
        name = nullptr;
        strcpy(ingredients, "");
        price = 0;
        discount = 0; // Initialize discount
    }

    IceCream(const char *name, const char *ingredients, float price) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->price = price;
        discount = 0; // Initialize discount
    }

    IceCream(const IceCream &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->ingredients, other.ingredients);
        this->price = other.price;
        this->discount = other.discount; // Copy discount
    }

    IceCream& operator=(const IceCream &other) {
        if (this != &other) {
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            strcpy(this->ingredients, other.ingredients);
            this->price = other.price;
            this->discount = other.discount; // Copy discount
        }
        return *this;
    }

    ~IceCream() {
        delete[] name;
    }

    void setDiscount(int discount) {
        if (discount < 0 || discount > 100) {
            throw InvalidDiscount(discount);
        }
        this->discount = discount; // Use instance variable
    }

    IceCream& operator++() {
        discount += 5;
        if (discount > 100) discount = 100;
        return *this;
    }

    IceCream operator+(const char *suffix) const {
        char *newName = new char[strlen(name) + strlen(suffix) + 2];
        strcpy(newName, name);
        strcat(newName, " + ");
        strcat(newName, suffix);

        IceCream result(newName, ingredients, price + 10);
        result.discount = this->discount; // Copy discount to new ice cream
        delete[] newName;
        return result;
    }

    void setName(const char *newName) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }

    friend ostream& operator<<(ostream &os, const IceCream &i) {
        os << i.name << ": " << i.ingredients << " " << i.price;
        if (i.discount > 0) {
            float discountedPrice = i.price * (100 - i.discount) / 100.0;
            os << " (" << discountedPrice << ")";
        }
        return os;
    }
};

// Removed static initialization: int IceCream::discount = 0;

class IceCreamShop {
protected:
    char name[51];
    IceCream *niza;
    int broj;
public:
    IceCreamShop() {
        strcpy(name, "");
        broj = 0;
        niza = nullptr;
    }

    IceCreamShop(const char *name) {
        strcpy(this->name, name);
        broj = 0;
        niza = nullptr;
    }

    IceCreamShop(const IceCreamShop &other) {
        strcpy(this->name, other.name);
        this->broj = other.broj;
        niza = new IceCream[broj];
        for (int i = 0; i < broj; i++) {
            niza[i] = other.niza[i];
        }
    }

    IceCreamShop& operator=(const IceCreamShop &other) {
        if (this != &other) {
            delete[] niza;
            strcpy(this->name, other.name);
            this->broj = other.broj;
            niza = new IceCream[broj];
            for (int i = 0; i < broj; i++) {
                niza[i] = other.niza[i];
            }
        }
        return *this;
    }

    ~IceCreamShop() {
        delete[] niza;
    }

    IceCreamShop& operator+=(const IceCream &i) {
        IceCream *temp = new IceCream[broj + 1];
        for (int j = 0; j < broj; j++) {
            temp[j] = niza[j];
        }
        temp[broj++] = i;
        delete[] niza;
        niza = temp;
        return *this;
    }

    friend ostream& operator<<(ostream &os, const IceCreamShop &shop) {
        os << shop.name << endl;
        for (int i = 0; i < shop.broj; i++) {
            os << shop.niza[i] << endl;
        }
        return os;
    }
};
// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR &lt;&lt;" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "TESTING EXCEPTION" << endl;

        // exception handling
        try {
            cin >> discount;
            ic1.setDiscount(discount);
        } catch (InvalidDiscount &ex) {
            ex.print();
        }

    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }

    return 0;
}
