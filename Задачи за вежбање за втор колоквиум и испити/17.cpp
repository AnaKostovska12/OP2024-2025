#include <iostream>
#include <cstring>
using namespace std;
class FudbalskaEkipa {
protected:
    char trener[101];
    int golovi[10];
public:
    FudbalskaEkipa() {
        strcpy(trener,"");
        for (int i = 0; i < 10; i++) {
            golovi[i] = 0;
        }
    }
    FudbalskaEkipa(char *trener,int *golovi) {
        strcpy(this->trener,trener);
        for (int i = 0; i < 10; i++) {
            this->golovi[i] = golovi[i];
        }
    }
    FudbalskaEkipa(const FudbalskaEkipa &f) {
        strcpy(this->trener,f.trener);
        for (int i = 0; i < 10; i++) {
            this->golovi[i] = f.golovi[i];
        }

    }
    friend ostream &operator<<(ostream &out,  FudbalskaEkipa &f) {
       f.print();
        return out;
    }
    FudbalskaEkipa &operator+=(int n) {

        for (int i = 0; i < 9; i++) {
           this->golovi[i] = this->golovi[i+1] ;
        }
        this->golovi[9] = n;
        return *this;
    }
    FudbalskaEkipa &operator=(const FudbalskaEkipa &f) {
        if (this!=&f) {
            strcpy(this->trener,f.trener);
            for (int i = 0; i < 10; i++) {
                this->golovi[i] = f.golovi[i];
            }
        }
        return *this;
    }
    virtual ~FudbalskaEkipa() {}
    virtual float uspeh()=0;
    bool operator>( FudbalskaEkipa &f) {
        return this->uspeh()>f.uspeh();
    }
    virtual void print()=0;

};
class Klub:public FudbalskaEkipa {
private:
    char name[21];
    int broj_tituli;
    public:
    Klub() {
        strcpy(name,"");
        broj_tituli = 0;
    }
    Klub(char *trener,int *golovi,char *name,int broj_tituli)
        : FudbalskaEkipa(trener,golovi) {
        strcpy(this->name,name);
        this->broj_tituli = broj_tituli;
    }
    Klub(const Klub &n): FudbalskaEkipa(n) {
        strcpy(this->name,n.name);
        this->broj_tituli = n.broj_tituli;

    }
    Klub &operator=(const Klub &n) {
        if (this!=&n) {
            strcpy(this->name,n.name);
            this->broj_tituli = n.broj_tituli;
            FudbalskaEkipa::operator=(n);
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out,  Klub &f) {
        out<<f.name<<endl;
        out<<f.trener<<endl;
        out<<f.uspeh()<<endl;
        return out;
    }
      float uspeh() override {
        float kraj=0;
        for (int i=0;i<10;i++) {
            kraj+=this->golovi[i];
        }
        return kraj*3+(this->broj_tituli*1000);
    }
    void print() override {
        cout<<this->name<<endl;
        cout<<this->trener<<endl;
        cout<<this->uspeh()<<endl;
    }
} ;
class Reprezentacija:public FudbalskaEkipa {
    private:
    char drzava[21];
    int megunarodni_nastapi;
    public:
    Reprezentacija() {
        strcpy(drzava,"");
        megunarodni_nastapi = 0;
    }
    Reprezentacija(char *trener,int *golovi,char *drzava,int megunarodni_nastapi)
        :FudbalskaEkipa(trener,golovi) {
        strcpy(this->drzava,drzava);
        this->megunarodni_nastapi = megunarodni_nastapi;
    };
    Reprezentacija(const Reprezentacija &n) :FudbalskaEkipa(n){
        strcpy(this->drzava,n.drzava);
        this->megunarodni_nastapi = n.megunarodni_nastapi;
    }

    Reprezentacija &operator=(const Reprezentacija &n) {
        if (this!=&n) {
            strcpy(this->drzava,n.drzava);
        this->megunarodni_nastapi = n.megunarodni_nastapi;
            FudbalskaEkipa::operator=(n);

        }
        return *this;
    }
    friend ostream &operator<<(ostream &out,  Reprezentacija &f) {
        out<<f.drzava<<endl;
        out<<f.trener<<endl;
        out<<f.uspeh()<<endl;
        return out;
    }
   float uspeh() override {
        float kraj=0;
        for (int i=0;i<10;i++) {
            kraj+=this->golovi[i];
        }
        return kraj*3+(this->megunarodni_nastapi*50);
    }
    void print() override{
        cout<<this->drzava<<endl;
        cout<<this->trener<<endl;
        cout<<this->uspeh()<<endl;
    }
};
void najdobarTrener(FudbalskaEkipa **niza,int n) {
    float max=0;
    int index=0;
    for (int i=0;i<n;i++) {
        if (niza[i]->uspeh()>max) {
            max=niza[i]->uspeh();
            index=i;
        }
    }
    niza[index]->print();
}
int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}