#include <iostream>
#include <cstring>
using namespace std;

class FoodProduct {
private:
    char name[20];
    int amount;
    int price;
public:
    FoodProduct() {}
    FoodProduct(char *name, int kolicina, int price) {
        strcpy(this->name, name);
        this->amount = kolicina;
        this->price = price;
    }
    ~FoodProduct() {}
    int getamount() { return amount; }
    int getprice() { return price; }
    void setprice(int pricee) { this->price = pricee; }
    void setamount(int amount) { this->amount = amount; }
    void print() {
        cout<<"name: "<<name<<"]"<<endl;
        cout<<"amount: "<<amount<<"]"<<endl;
        cout<<"price: ["<<price<<"]"<<endl;
    }
};

class Menu {
private:
    char name[50];
    int NumberOfProducts;
    FoodProduct produkti[50];
public:
    Menu() { NumberOfProducts = 0; }
    ~Menu() {}
    Menu(char *name) {
        strcpy(this->name, name);
        NumberOfProducts = 0;
    }
    char *getname(){ return name; }
    int getNumberOfProducts() { return NumberOfProducts; }
    void setNumberOfProducts(int numberOfProducts) { NumberOfProducts = numberOfProducts; }
    void setName(char *namee) { strcpy(this->name, namee); }

    void addProduct(FoodProduct p) {
        if (NumberOfProducts < 50) {
            produkti[NumberOfProducts] = p;
            NumberOfProducts++;
        }
        else {
            cout<<"nema mesto"<<endl;
        }
    }

    void print() {
        cout<<"name: "<<name<<endl;
        cout<<"Products "<<endl;
        for (int i = 0; i < NumberOfProducts; i++) {
            produkti[i].print();
        }
    }

    int totalIncome() {
        int income=0;
        int zbir=0;
        for (int i = 0; i < NumberOfProducts; i++) {
            zbir=produkti[i].getamount()*produkti[i].getprice();
            income+=zbir;
        }
        return income;
    }
};

void printWorstMenu(Menu *menus, int n) {
    Menu najloso;
    int lowest_income = menus[0].totalIncome();
    najloso = menus[0];
    for (int i = 1; i < n; i++) {
        if (menus[i].totalIncome() < lowest_income) {
            lowest_income = menus[i].totalIncome();
            najloso = menus[i];
        }
    }
    najloso.print();
}

int main() {
    int n;
    cin >> n;
    Menu menus[n];
    for(int i = 0; i < n; i++) {
        int m;
        char name[50];
        cin >> name >> m;
        menus[i] = Menu(name);
        for(int j = 0; j < m; j++) {
            char itemName[50];
            int amount, price;
            cin >> itemName >> amount >> price;
            FoodProduct product(itemName, amount, price);
            menus[i].addProduct(product);
        }
    }
    cout << "\n-- Testing printWorstMenu() --\n";
    printWorstMenu(menus, n);
    return 0;
}