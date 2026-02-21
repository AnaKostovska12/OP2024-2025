#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class StudentFailedException {
private:
    string index;
public:
    StudentFailedException(string index = "") {
        this->index = index;
    }
    void print() {
        cout << "Student with id " << index << " failed the course" << endl;
    }
};

class Student {
private:
    string index;
    string name;
    string surname;
    int poeni;
public:
    Student() : index(""), name(""), surname(""), poeni(0) {}
    Student(string index, string name, string surname, int poeni)
        : index(index), name(name), surname(surname), poeni(poeni) {}
    Student(const Student &s) {
        index = s.index;
        name = s.name;
        surname = s.surname;
        poeni = s.poeni;
    }
    friend istream &operator>>(istream &in,Student &n) {
        in>>n.index>>n.name>>n.surname>>n.poeni;
        // in.ignore();
        return in;
    }
    Student &operator=(const Student &s) {
        if (this != &s) {
            index = s.index;
            name = s.name;
            surname = s.surname;
            poeni = s.poeni;
        }
        return *this;
    }
    ~Student() {}

    int grade() const {
        if (poeni >= 90) return 10;
        if (poeni >= 80) return 9;
        if (poeni >= 70) return 8;
        if (poeni >= 60) return 7;
        if (poeni >= 50) return 6;
        return 5;
    }

    string getIndex() const {
        return index;
    }

    friend ostream &operator<<(ostream &os, const Student &s) {
        os << s.index << " " << s.name << " " << s.surname << " " << s.poeni;
        os << " Grade: " << s.grade()<<endl;
        return os;
    }
};

class Results {
private:
    Student *lista;
    int broj;
public:
    Results() {
        lista = nullptr;
        broj = 0;
    }

    Results(Student *lista, int broj) {
        this->broj = broj;
        this->lista = new Student[broj];
        for (int i = 0; i < broj; i++) {
            this->lista[i] = lista[i];
        }
    }

    Results(const Results &r) {
        broj = r.broj;
        lista = new Student[broj];
        for (int i = 0; i < broj; i++) {
            lista[i] = r.lista[i];
        }
    }

    Results &operator=(const Results &r) {
        if (this != &r) {
            delete[] lista;
            broj = r.broj;
            lista = new Student[broj];
            for (int i = 0; i < broj; i++) {
                lista[i] = r.lista[i];
            }
        }
        return *this;
    }

    ~Results() {
        delete[] lista;
    }

    Results &operator+=(Student &s) {
        if (s.grade() == 5) {
            throw StudentFailedException(s.getIndex());
        }
        Student *temp = new Student[broj + 1];
        for (int i = 0; i < broj; i++) {
            temp[i] = lista[i];
        }
        temp[broj++] = s;
        delete[] lista;
        lista = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Results &r) {

        for (int i = 0; i < r.broj; i++) {
            os << r.lista[i];
        }
        if(r.broj==0)
        os<<"None"<<endl;
        return os;
    }

    Results withGrade(int grade) {
        int count = 0;
        for (int i = 0; i < broj; i++) {
            if (lista[i].grade() == grade) count++;
        }
        Student *temp = new Student[count];
        int j = 0;
        for (int i = 0; i < broj; i++) {
            if (lista[i].grade() == grade) {
                temp[j++] = lista[i];
            }
        }
        Results r(temp, count);
        delete[] temp;
        return r;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(cin, line)) {
        if (line == "----") break;
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

int main() {
    wtf();

    Results results;
    ifstream in("input.txt");
    string index, name, surname;
    int poeni;
;
    Student s;
while (in>>s) {
    try {

        results += s;
    } catch (StudentFailedException &e) {
        e.print();
    }
}
in.close();

    int grade;
    cin >> grade;

    ofstream out1("output1.txt");
    out1 << results ;
    out1.close();

    ofstream out2("output2.txt");
    Results filtered = results.withGrade(grade);
    // out2 << filtered << endl;
        out2 <<  results.withGrade(grade);
    out2.close();

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");

    return 0;
}
