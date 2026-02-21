#include <iostream>
#include <cstring>
using namespace std;

class Profile {
private:
    char name[30];
    int br_prijateli;
    int godina;

public:
    Profile() {
        strcpy(name, "");
        br_prijateli = 0;
        godina = 0;
    }
    
    Profile(const char *name, int br_prijateli, int godina) {
        strncpy(this->name, name, 29);
        this->br_prijateli = br_prijateli;
        this->godina = godina;
    }

    void print() {
        cout << name << " Friends: " << br_prijateli << " Year: " << godina << endl;
    }

    bool operator==(const Profile &m) const {
        return br_prijateli == m.br_prijateli;
    }

    bool operator>(const Profile &m) const {
        return godina < m.godina; // Lower year means older
    }

    Profile& operator++() {
        br_prijateli++;
        return *this;
    }

    Profile operator++(int) {
        Profile temp(*this);
        br_prijateli++;
        return temp;
    }

    // Profile + int
    Profile operator+(int m) {
        return Profile(name, br_prijateli + m, godina);
    }

    friend Profile operator+(int m, const Profile &k);
    friend Profile operator&(const Profile &k, const Profile &m);
    friend ostream& operator<<(ostream &o, const Profile &p);
    friend istream& operator>>(istream &i, Profile &p);
};

Profile operator+(int m, const Profile &k) {
    return Profile(k.name, k.br_prijateli + m, k.godina);
}

// Combine two profiles
Profile operator&(const Profile &k, const Profile &m) {
    char newName[60];
    strcpy(newName, k.name);
    strcat(newName, m.name);
    int olderYear = (k.godina < m.godina) ? k.godina : m.godina;
    return Profile(newName, k.br_prijateli + m.br_prijateli, olderYear);
}

ostream& operator<<(ostream &o, const Profile &p) {
    o << p.name << " " << p.br_prijateli << " " << p.godina;
    return o;
}

istream& operator>>(istream &i, Profile &p) {
    i >> p.name >> p.br_prijateli >> p.godina;
    return i;
}

int main() {
    Profile p1("Mitre", 200, 1999);
    Profile p2("Katerina", 300, 2000);
    
    cout << "Profile 1: " << p1 << endl;
    
    if (p1 > p2) cout << "P1 is older." << endl;
    
    Profile p3 = p1 & p2;
    cout << "Combined: " << p3 << endl;

    return 0;
}