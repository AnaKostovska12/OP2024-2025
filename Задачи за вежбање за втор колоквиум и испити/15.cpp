#include<iostream>
#include<string.h>
using namespace std;

class BadInputException {
public:
    void print() {
        cout << "Greshna opisna ocenka" << endl;
    }
};

class StudentKurs {
protected:
    char ime[30];
    int ocena;
    bool daliUsno;
    static int MAX;
    const static int MINOCENKA;

public:
    StudentKurs() {
        ocena = 0;
        daliUsno = false;
        strcpy(ime, "");
    }

    StudentKurs(char* ime, int finalenIspit) {
        strcpy(this->ime, ime);
        this->ocena = finalenIspit;
        this->daliUsno = false;
    }

    StudentKurs(const StudentKurs &n) {
        strcpy(this->ime, n.ime);
        this->ocena = n.ocena;
        this->daliUsno = n.daliUsno;
    }

    StudentKurs& operator=(const StudentKurs &n) {
        if (this != &n) {
            strcpy(this->ime, n.ime);
            this->ocena = n.ocena;
            this->daliUsno = n.daliUsno;
        }
        return *this;
    }

    virtual ~StudentKurs() {}

    static void setMAX(int m) {
        MAX = m;
    }

    virtual int ocenka() const {
        return ocena;
    }

    virtual bool getDaliUsno() const {
        return daliUsno;
    }

    const char* getIme() const {
        return ime;
    }

    static int getMin() {
        return MINOCENKA;
    }

    friend ostream& operator<<(ostream &os, const StudentKurs &n) {
        os << n.ime << " --- " << n.ocenka() << endl;
        return os;
    }
};

int StudentKurs::MAX = 10;
const int StudentKurs::MINOCENKA = 6;

class StudentKursUsno : public StudentKurs {
private:
    char* opisna;

public:
    StudentKursUsno(char* ime, int ocena) : StudentKurs(ime, ocena) {
        daliUsno = true;
        opisna = new char[10];
        strcpy(opisna, "");
    }

    StudentKursUsno(const StudentKursUsno &n) : StudentKurs(n) {
        opisna = new char[strlen(n.opisna) + 1];
        strcpy(opisna, n.opisna);
    }

    StudentKursUsno& operator=(const StudentKursUsno &n) {
        if (this != &n) {
            StudentKurs::operator=(n);
            delete[] opisna;
            opisna = new char[strlen(n.opisna) + 1];
            strcpy(opisna, n.opisna);
        }
        return *this;
    }

    ~StudentKursUsno() {
        delete[] opisna;
    }

    int ocenka() const override {
        if (strcmp(opisna, "odlicen") == 0) {
            return (ocena + 2 <= MAX) ? ocena + 2 : MAX;
        } else if (strcmp(opisna, "dobro") == 0) {
            return (ocena + 1 <= MAX) ? ocena + 1 : MAX;
        } else if (strcmp(opisna, "losho") == 0) {
            return (ocena - 1 >= MINOCENKA) ? ocena - 1 : MINOCENKA;
        }
        return ocena;
    }

    StudentKurs& operator+=(char* nova) {
        for (int i = 0; i < strlen(nova); ++i) {
            if (!isalpha(nova[i])) {
                throw BadInputException();
            }
        }
        delete[] opisna;
        opisna = new char[strlen(nova) + 1];
        strcpy(opisna, nova);
        return *this;
    }
};

class KursFakultet {
private:
    char naziv[30];
    StudentKurs* studenti[20];
    int broj;

public:
    KursFakultet(char* naziv, StudentKurs** studenti, int broj) {
        strcpy(this->naziv, naziv);
        this->broj = broj;
        for (int i = 0; i < broj; ++i) {
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            } else {
                this->studenti[i] = new StudentKurs(*studenti[i]);
            }
        }
    }

    ~KursFakultet() {
        for (int i = 0; i < broj; ++i) {
            delete studenti[i];
        }
    }

    void pecatiStudenti() {
        cout << "Kursot " << naziv << " go polozile:" << endl;
        for (int i = 0; i < broj; ++i) {
            if (studenti[i]->ocenka() >= StudentKurs::getMin()) {
                cout << *studenti[i];
            }
        }
    }

    void postaviOpisnaOcenka(char* ime, char* opisnaOcenka) {
        for (int i = 0; i < broj; ++i) {
            if (studenti[i]->getDaliUsno()) {
                if (strcmp(studenti[i]->getIme(), ime) == 0) {
                    StudentKursUsno* temp = dynamic_cast<StudentKursUsno*>(studenti[i]);
                    if (temp) {
                        *temp += opisnaOcenka;
                    }
                }
            }
        }
    }
};

int main() {
    StudentKurs** niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;

    cin >> n;
    niza = new StudentKurs*[n];

    for (int i = 0; i < n; ++i) {
        cin >> ime >> ocenka >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);

    for (int i = 0; i < n; ++i) delete niza[i];
    delete[] niza;

    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> ime >> opisna;
        try {
            programiranje.postaviOpisnaOcenka(ime, opisna);
        } catch (BadInputException &e) {
            e.print();
            int len = strlen(opisna);
            for (int j = 0; j < len; ++j) {
                if (!isalpha(opisna[j])) {
                    for (int k = j; k < len - 1; ++k)
                        opisna[k] = opisna[k + 1];
                    opisna[len - 1] = '\0';
                    --j;
                    --len;
                }
            }
            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
    }

    StudentKurs::setMAX(9);
    programiranje.pecatiStudenti();
    return 0;
}
