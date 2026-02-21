using namespace std;
#include <cstring>
#include <iostream>
class Delo {
protected:
    char name[51];
    int godina;
    char zemja[51];
public:
    Delo(char *name=" ",int godina=0,char *zemja=" ") {
        strcpy(this->name,name);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }
    Delo &operator=(const Delo &other) {
        if (this!=&other) {
            strcpy(this->name,other.name);
        this->godina=other.godina;
        strcpy(this->zemja,other.zemja);
        }
        return *this;
    }
    Delo (const Delo &other) {
        strcpy(this->name,other.name);
        this->godina=other.godina;
        strcpy(this->zemja,other.zemja);
    }
    ~Delo() {}
    char *getIme() {
        return name;
    }
    char *getZemja() {
        return zemja;
    }
    void setIme(char *name) {
        strcpy(this->name,name);
    }
    void setZemja(char *zemja) {
        strcpy(this->zemja,zemja);
    }
    bool operator==(const Delo &other) {
        return strcmp(this->name,other.name)==0;
    }
    int getGodina() {
        return godina;
    }

};
class Pretstava {
    protected:
    Delo delo;
    int prodadeni;
    char data[16];
    public:
    Pretstava() {
        strcpy(data," ");
        prodadeni=0;
    }
    Pretstava(Delo delo,int prodadeni,char *data) {
        this->delo=delo;
        strcpy(this->data,data);
        this->prodadeni=prodadeni;
    }
   virtual ~Pretstava() {}
    Pretstava &operator=(const Pretstava &other) {
        if (this!=&other) {
           this->delo=other.delo;
            this->prodadeni=other.prodadeni;
            strcpy(this->data,other.data);
        }
        return *this;
    }
    Pretstava(const Pretstava &other) {
        this->delo=other.delo;
        this->prodadeni=other.prodadeni;
        strcpy(this->data,other.data);
    }
    int getProdadeni(){
        return prodadeni;
    }
  virtual   double cena() {
        int n;
        int m;
        if (delo.getGodina() > 1900) {
            m = 50;
        } else if (delo.getGodina() > 1800 && delo.getGodina() <= 1900) {
            m = 75;
        } else {
            m = 100;
        }
        if (strcmp(delo.getZemja(), "Italija") == 0) {
            n = 100;
        } else if (strcmp(delo.getZemja(), "Rusija") == 0) {
            n = 150;
        } else {
            n = 80;
        }
        return m + n;
    }
    Delo getDelo() {
        return delo;
    }

};
class Balet: public Pretstava {
private:
   static int cena_dopolnitelna;
public:
    Balet() {
        cena_dopolnitelna=0;
    }
    Balet(Delo delo,int prodadeni,char *data)
        : Pretstava(delo,prodadeni,data) {

    }
    static void setCenaBalet(int cena) {
        cena_dopolnitelna = cena;
    }
    double cena() override {
        return Pretstava::cena()+cena_dopolnitelna;
    }
    ~Balet() {}

};
int Balet::cena_dopolnitelna=150;
 class Opera: public Pretstava {
     public:
     Opera(Delo delo,int prodadeni,char *data)
    : Pretstava(delo,prodadeni,data) {

     }
     double cena() override {
         return Pretstava::cena();
     }
     ~Opera() {}
 };
double prihod(Pretstava *lista[],int num) {
    double suma=0;
    for (int i=0;i<num;i++) {
        suma+=lista[i]->cena()*lista[i]->getProdadeni();
    }
    return suma;
}
int brojPretstaviNaDelo (Pretstava *lista[],int num,Delo novo) {
    int counter=0;
    for (int i=0;i<num;i++) {
        if (lista[i]->getDelo()==novo) {
            counter++;
        }
    }
    return counter;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
