using namespace std;
#include <cstring>
#include <iostream>
#include <string.h>
#include <cstdlib>
class NegativnaVrednost {
public:
    NegativnaVrednost() {}
    void print() {
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

//место за вашиот код
class Oglas {
    private:
    char naslov[51];
    char kategorija[31];
    char opis[101];
    float cenaEvra;
public:
    Oglas() {
        strcpy(naslov,"");
        strcpy(kategorija,"");
        strcpy(opis,"");
        cenaEvra=0;
    }
    Oglas(char *naslov,char *kategorija,char *opis,float cenaEvra) {
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cenaEvra=cenaEvra;
    }
    Oglas (const Oglas &n) {
        strcpy(this->naslov,n.naslov);
        strcpy(this->kategorija,n.kategorija);
        strcpy(this->opis,n.opis);
        this->cenaEvra=n.cenaEvra;
    }
    Oglas &operator=(const Oglas &n) {
        strcpy(this->naslov,n.naslov);
        strcpy(this->kategorija,n.kategorija);
        strcpy(this->opis,n.opis);
        this->cenaEvra=n.cenaEvra;
    }
    bool operator>(const Oglas &n) {
        return this->cenaEvra>n.cenaEvra;
    }
    friend ostream &operator<<(ostream &os,const Oglas &n) {
        os<<n.naslov<<endl;
        os<<n.opis<<endl;
        os<<n.cenaEvra<<" evra"<<endl;
        return os;
    }
  const  float getCena()const {
        return cenaEvra;
    }
    ~Oglas() {}
   const  char *getKategorija()const {
        return kategorija;
    }
};
class Oglasnik {
    private:
    char name[21];
    Oglas *oglasi;
    int broj;
public:
    Oglasnik() {
        strcpy(name,"");
        oglasi=NULL;
        broj=0;
    }
    Oglasnik(char *name) {
        strcpy(this->name,name);
    }
    Oglasnik &operator=(const Oglasnik &n) {
        if (this!=&n) {
            delete [] oglasi;
            strcpy(this->name,n.name);
            this->broj=n.broj;
            for (int i=0;i<n.broj;i++) {
                this->oglasi[i]=n.oglasi[i];
            }
        }
        return *this;
    }
    Oglasnik (const Oglasnik &n) {
        strcpy(this->name,n.name);
        this->broj=n.broj;
        for (int i=0;i<n.broj;i++) {
            this->oglasi[i]=n.oglasi[i];
        }
    }
    ~Oglasnik() {
        delete [] oglasi;
    }
    Oglasnik &operator+=(const Oglas &n) {
        if (n.getCena()<0) {
            NegativnaVrednost e;
            throw e;
        }
        else {
            Oglas *temp= new Oglas[broj +1];
            for (int i=0;i<broj;i++) {
                temp[i]=this->oglasi[i];
            }
            temp[broj++]=n;
            delete [] oglasi;
            oglasi=temp;
            return *this;
        }
    };
    friend ostream &operator<<(ostream &os,const Oglasnik &n) {
       os<<n.name<<endl;
        for (int i=0;i<n.broj;i++) {
            os<<n.oglasi[i]<<endl;
        }
        return os;
    }void oglasiOdKategorija(const char *k) {
        for (int i=0;i<broj;i++) {
           if (strcmp(k,oglasi[i].getKategorija())==0) {
               cout<<oglasi[i]<<endl;
           }
        }
    }
    void najniskaCena() {
        int index=0;
        int min=oglasi[0].getCena();
        for (int i=0;i<broj;i++) {
            if (min>oglasi[i].getCena()) {
                min=oglasi[i].getCena();
                index=i;
            }
        }
        cout<<oglasi[index]<<endl;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);

            try {
                ogl += o;
            } catch (NegativnaVrednost &e) {
                e.print();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost &e) {
                e.print();
            }
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost &e) {
                e.print();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost &e) {
                e.print();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost &e) {
                e.print();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
