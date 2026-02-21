#include <iostream>
#include <cstring>
using namespace std;

class Pair {
protected:
    char *key;
    int value;
public:
    Pair() {
        key = nullptr;
        value = 0;
    }

    Pair(char *key, int value) {
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

    friend ostream &operator<<(ostream &os, const Pair &pair) {
        os <<"'"<< pair.key<<"' -> "<<pair.value<<""<<endl;
        return os;
    }
    Pair operator--(int n) {
        Pair nov=*this;
        value--;
        return nov;}
    Pair &operator--() {
        value--;
        return *this;
    }
    Pair operator*(Pair &n) {
        Pair c;
        c.value=this->value*n.value;
        if (strlen(this->key)<strlen(n.key)) {
            c.key = new char[strlen(this->key)+1];
            strcpy(c.key, this->key);
        }
        else {
            c.key = new char[strlen(n.key)+1];
            strcpy(c.key, n.key);
        }
        return c;
    } int getValue() {
        return value;
    }

};
// vashiot kod ovde
class Collection {
    protected:
    Pair *niza;
    int broj;
    public:
   Collection() {
    broj = 0;
    niza = nullptr; // FIX for segmentation fault
}
  Collection(Pair *niza, int broj) {
    this->niza = new Pair[broj];
    this->broj = broj;
    for (int i = 0; i < broj; i++) {
        this->niza[i] = niza[i];
    }
}
    ~Collection() {
        delete[] niza;
    }
    Collection (const Collection &n) {
        niza = new Pair[n.broj];
        this->broj=n.broj;
        for (int i=0;i<n.broj;i++) {
            this->niza[i] = n.niza[i];
        }
    }
    Collection &operator=(const Collection &n) {
        if (this!=&n) {
            delete[] niza;
            niza = new Pair[n.broj];
            this->broj=n.broj;
            for (int i=0;i<n.broj;i++) {
                this->niza[i] = n.niza[i];
            }
        }
        return *this;
    }
    Collection &operator+=(Pair &n) {
        Pair *temp= new Pair [broj+1];
        for (int i=0;i<broj;i++) {
            temp[i] = this->niza[i];
        }
        temp[broj++]=n;
        delete[] niza;
        niza = temp;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const Collection &n) {
        os<<"Size: "<<n.broj<<endl;
        for (int i=0;i<n.broj;i++) {
            os<<n.niza[i];
        }
        return os;
    }
    bool operator<(const Collection &n) {
        int prv=0;
        for (int i=0;i<broj;i++) {
            prv+=niza[i].getValue();
        }
        int vtor=0;
        for (int i=0;i<n.broj;i++) {
            vtor+=n.niza[i].getValue();
        }
        if (prv<vtor) {
            return true;
        }
            else return false;

    }
    int greater(int value) {
        int counter=0;
        for (int i=0;i<broj;i++) {
            if (niza[i].getValue()>value) {
                counter++;
            }
        }
        return counter;
    }
};


void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}
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
    cout << "----- operator --(int) -----" << endl;
    cout << p1--;
    cout << p1;
    cout << "----- operator -- -----" << endl;
    cout << --p2;
    cout << "----- operator * -----" << endl;
    Pair p = p1 * p2;
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
    cout << "----- operator < -----" << endl;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    k2 += p1;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    cout << "----- greater -----" << endl;
    int x;
    cin >> x;
    int pp = k.greater(x);
    cout << pp;
    return 0;
}