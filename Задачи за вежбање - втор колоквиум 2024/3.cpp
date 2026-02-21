#include <cstring>
#include <iostream>
#include <string>
using namespace std;

class Library {
protected:
    string name;
    string grad;
    float mesecna_clenarina;
    bool vikend;

public:
    Library() {
        name = "";
        grad = "";
        mesecna_clenarina = 0.0;
        vikend = false;
    }

    Library(string name, string grad, float mesecna_clenarina, bool vikend) {
        this->name = name;
        this->grad = grad;
        this->mesecna_clenarina = mesecna_clenarina;
        this->vikend = vikend;
    }

    Library(const Library &other) {
        this->name = other.name;
        this->grad = other.grad;
        this->mesecna_clenarina = other.mesecna_clenarina;
        this->vikend = other.vikend;
    }

    virtual ~Library() {}

    bool getvikend() const {
        return vikend;
    }

    virtual void printDetail() const = 0;
    virtual double calculateMembershipCardCost() const = 0;
};

class AcademicLibrary : public Library {
private:
    bool istrazuvanja;
    int specijalizirani;

public:
    AcademicLibrary(string name, string grad, float mesecna_clenarina, bool vikend, bool istrazuvanja, int specijalizirani)
        : Library(name, grad, mesecna_clenarina, vikend) {
        this->istrazuvanja = istrazuvanja;
        this->specijalizirani = specijalizirani;
    }

    AcademicLibrary(const AcademicLibrary &other)
        : Library(other) {
        this->istrazuvanja = other.istrazuvanja;
        this->specijalizirani = other.specijalizirani;
    }

    AcademicLibrary &operator=(const AcademicLibrary &other) {
        if (this != &other) {
            Library::operator=(other);
            this->istrazuvanja = other.istrazuvanja;
            this->specijalizirani = other.specijalizirani;
        }
        return *this;
    }

    double calculateMembershipCardCost() const override {
        double total = mesecna_clenarina;
        if (istrazuvanja) {
            total *= 1.24;
        }
        return total + specijalizirani * 6;
    }

    void printDetail() const override {
        cout << name << " - (Academic) " << grad
             << " " << specijalizirani << " "
             << calculateMembershipCardCost() << endl;
    }
};

class NationalLibrary : public Library {
private:
    bool edukativni;
    int originalniRakopisi;

public:
    NationalLibrary() {
        edukativni = false;
        originalniRakopisi = 0;
    }

    NationalLibrary(string name, string grad, float mesecna_clenarina, bool vikend, bool edukativni, int originalniRakopisi)
        : Library(name, grad, mesecna_clenarina, vikend) {
        this->edukativni = edukativni;
        this->originalniRakopisi = originalniRakopisi;
    }

    NationalLibrary(const NationalLibrary &other)
        : Library(other) {
        this->edukativni = other.edukativni;
        this->originalniRakopisi = other.originalniRakopisi;
    }

    NationalLibrary &operator=(const NationalLibrary &other) {
        if (this != &other) {
            Library::operator=(other);
            this->edukativni = other.edukativni;
            this->originalniRakopisi = other.originalniRakopisi;
        }
        return *this;
    }

    double calculateMembershipCardCost() const override {
        double total = mesecna_clenarina;
        if (edukativni) {
            total *= 0.93;
        }
        return total + originalniRakopisi * 15;
    }

    void printDetail() const override {
        cout << name << " - (National) " << grad
             << " " << originalniRakopisi << " "
             << calculateMembershipCardCost() << endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    double max = 0;
    int index = -1;

    for (int i = 0; i < n; i++) {
        NationalLibrary *nat = dynamic_cast<NationalLibrary *>(l[i]);
        if (nat) {
            double cost = nat->calculateMembershipCardCost();
            if (cost > max || (cost == max && nat->getvikend())) {
                max = cost;
                index = i;
            }
        }
    }

    return index;
}
int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
