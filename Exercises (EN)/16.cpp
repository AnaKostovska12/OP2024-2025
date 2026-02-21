#include <iostream>
#include <cstring>
using namespace std;

class Pair {
protected:
    char *key;
    float value;
public:
    Pair() {
        key = nullptr;
        value = 0;
    }

    Pair(const char *key, float value) {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
    }

    Pair(const Pair &other) {
        key = new char[strlen(other.key) + 1];
        strcpy(key, other.key);
        value = other.value;
    }

    Pair& operator=(const Pair &other) {
        if (this != &other) {
            delete[] key;
            key = new char[strlen(other.key) + 1];
            strcpy(key, other.key);
            value = other.value;
        }
        return *this;
    }

    ~Pair() {
        delete[] key;
    }

    friend ostream& operator<<(ostream &os, const Pair &pair) {
        os << "('" << pair.key << "', " << pair.value << ")" << endl;
        return os;
    }

    Pair operator++(int) {
        Pair temp(*this);
        value++;
        return temp;
    }

    Pair& operator++() {
        value++;
        return *this;
    }

    Pair operator+(const Pair &other) {
        const char *longerKey = (strlen(this->key) >= strlen(other.key)) ? this->key : other.key;
        Pair result(longerKey, this->value + other.value);
        return result;
    }

    bool operator==(const Pair &other) const {
        return strcmp(key, other.key) == 0 && value == other.value;
    }

    const char* getKey() const {
        return key;
    }

    float getValue() const {
        return value;
    }
};

class Collection {
protected:
    Pair *niza;
    int broj;
public:
    Collection() {
        broj = 0;
        niza = nullptr;
    }

    Collection(Pair *niza, int broj) {
        this->broj = broj;
        this->niza = new Pair[broj];
        for (int i = 0; i < broj; ++i)
            this->niza[i] = niza[i];
    }

    Collection(const Collection &other) {
        broj = other.broj;
        niza = new Pair[broj];
        for (int i = 0; i < broj; ++i)
            niza[i] = other.niza[i];
    }

    Collection& operator=(const Collection &other) {
        if (this != &other) {
            delete[] niza;
            broj = other.broj;
            niza = new Pair[broj];
            for (int i = 0; i < broj; ++i)
                niza[i] = other.niza[i];
        }
        return *this;
    }

    ~Collection() {
        delete[] niza;
    }

    Collection& operator+=(const Pair &p) {
        Pair *tmp = new Pair[broj + 1];
        for (int i = 0; i < broj; ++i)
            tmp[i] = niza[i];
        tmp[broj] = p;
        delete[] niza;
        niza = tmp;
        broj++;
        return *this;
    }

    friend ostream& operator<<(ostream &os, const Collection &c) {
        os << "Size: " << c.broj << endl;
        for (int i = 0; i < c.broj; ++i)
            os << c.niza[i];
        return os;
    }

    bool operator==(const Collection &other) const {
        if (broj != other.broj) return false;
        for (int i = 0; i < broj; ++i)
            if (!(niza[i] == other.niza[i]))
                return false;
        return true;
    }

    Pair* find(const char *key) {
        for (int i = 0; i < broj; ++i)
            if (strcmp(niza[i].getKey(), key) == 0)
                return &niza[i];
        return nullptr;
    }
};

// Input reader
void read(char *k, float *v) {
    cin >> k >> *v;
}

// Test main (unchanged)
int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator ++(int) -----" << endl;
    cout << p1++;
    cout << p1;
    cout << "----- operator ++ -----" << endl;
    cout << ++p2;
    cout << "----- operator + -----" << endl;
    Pair p = p1 + p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator == -----" << endl;
    if (k == k2)
        cout << "k == k2" << endl;
    k2 += p1;
    if (k == k2)
        cout << "k == k2" << endl;
    cout << "----- find -----" << endl;
    Pair* f = k.find(key);
    if (f)
        cout << *f;
    strcat(key, "other");
    f = k.find(key);
    if (!f)
        cout << key << " not found" << endl;
    return 0;
}
