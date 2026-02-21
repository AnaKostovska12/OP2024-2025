#include <iostream>
#include <cstring>
using namespace std;

class AlcoholicDrink {
protected:
    char name[101];
    char origin[101];
    float percentAlcohol;
    float basePrice;
    static int discount;

public:
    AlcoholicDrink() {
        strcpy(name, "");
        strcpy(origin, "");
        percentAlcohol = 0;
        basePrice = 0;
    }

    AlcoholicDrink(float percentAlcohol, char *name, char *origin, float basePrice) {
        strcpy(this->name, name);
        strcpy(this->origin, origin);
        this->percentAlcohol = percentAlcohol;
        this->basePrice = basePrice;
    }

    AlcoholicDrink(const AlcoholicDrink &other) {
        strcpy(this->name, other.name);
        strcpy(this->origin, other.origin);
        this->percentAlcohol = other.percentAlcohol;
        this->basePrice = other.basePrice;
    }

    AlcoholicDrink &operator=(const AlcoholicDrink &other) {
        if (this != &other) {
            strcpy(this->name, other.name);
            strcpy(this->origin, other.origin);
            this->percentAlcohol = other.percentAlcohol;
            this->basePrice = other.basePrice;
        }
        return *this;
    }

    virtual ~AlcoholicDrink() {}

    static void changeDiscount(int d) {
        discount = d;
    }

    static void total(AlcoholicDrink **drinks, int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += drinks[i]->computedPrice();
    }
    cout << "Total price: " << total << endl;
    cout << "Total price with discount: " << total * (100 - discount) / 100 << endl;
}
    virtual float computedPrice() const = 0;

    bool operator<(AlcoholicDrink &other) {
        return this->computedPrice() < other.computedPrice();
    }

    friend ostream &operator<<(ostream &os, const AlcoholicDrink &d) {
        os << d.name << " " << d.origin << " " << d.computedPrice() ;
        return os;
    }
};

int AlcoholicDrink::discount = 5;

class Beer : public AlcoholicDrink {
private:
    bool mainIngredientWheat; // true if wheat, false if barley

public:
    Beer() : AlcoholicDrink() {
        mainIngredientWheat = false;
    }

    Beer(float percentAlcohol, char *name, char *origin, float basePrice, bool mainIngredientWheat)
        : AlcoholicDrink(percentAlcohol, name, origin, basePrice) {
        this->mainIngredientWheat = mainIngredientWheat;
    }

    Beer(const Beer &other) : AlcoholicDrink(other) {
        this->mainIngredientWheat = other.mainIngredientWheat;
    }

    Beer &operator=(const Beer &other) {
        if (this != &other) {
            AlcoholicDrink::operator=(other);
            this->mainIngredientWheat = other.mainIngredientWheat;
        }
        return *this;
    }

    float computedPrice() const override {
    float finalPrice = basePrice;
    if (!mainIngredientWheat) {
        finalPrice += basePrice * 0.10f;  // +10% base price
    }
    if (strcmp(origin, "Germany") == 0) {
        finalPrice += basePrice * 0.05f;  // +5% base price
    }
    return finalPrice;
}
};

class Wine : public AlcoholicDrink {
private:
    int year;
    char grapesType[20];

public:
    Wine() : AlcoholicDrink() {
        year = 0;
        strcpy(grapesType, "");
    }

    Wine(float percentAlcohol, char *name, char *origin, float basePrice, int year, char *grapesType)
        : AlcoholicDrink(percentAlcohol, name, origin, basePrice) {
        this->year = year;
        strcpy(this->grapesType, grapesType);
    }

    Wine(const Wine &other) : AlcoholicDrink(other) {
        this->year = other.year;
        strcpy(this->grapesType, other.grapesType);
    }

    Wine &operator=(const Wine &other) {
        if (this != &other) {
            AlcoholicDrink::operator=(other);
            this->year = other.year;
            strcpy(this->grapesType, other.grapesType);
        }
        return *this;
    }

    float computedPrice() const override {
    float finalPrice = basePrice;
    if (strcmp(origin, "Italy") == 0) {
        finalPrice += basePrice * 0.05f;  // +5% base price
    }
    if (year < 2005) {
        finalPrice += basePrice * 0.15f;  // +15% base price
    }
    return finalPrice;
}
};

void lowestPrice(AlcoholicDrink **drinks, int n) {
    int minIndex = 0;
    float minPrice = drinks[0]->computedPrice();
    for (int i = 1; i < n; i++) {
        float price = drinks[i]->computedPrice();
        if (price < minPrice) {
            minPrice = price;
            minIndex = i;
        }
    }
    cout << *drinks[minIndex];
}

// DO NOT CHANGE THE MAIN FUNCTION

int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape[20];
    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if (testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink **ad = new AlcoholicDrink *[n];
        for (int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for (int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete[] ad;
    } else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink **ad = new AlcoholicDrink *[n];
        for (int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for (int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete[] ad;
    }
}
