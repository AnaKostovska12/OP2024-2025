using namespace std;
#include <iostream>
#include <cstring>
enum Tip {
    LINUX, UNIX, WINDOWS
};
class Repozitorium;
class OperativenSistem {
    char *name;
    friend class Repozitorium;
    float verzija;
    Tip tip;
    float golemina;
public:
    OperativenSistem() {
     name=nullptr;
        verzija=0;
        tip=LINUX;
        golemina=0;
    }
    OperativenSistem(char *name, float verzija, Tip tip,float golemina) {
        this->verzija=verzija;
        this->tip=tip;
        this->golemina=golemina;
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
    }
    OperativenSistem(const OperativenSistem &n) {
        this->verzija=n.verzija;
        this->tip=n.tip;
        this->golemina=n.golemina;
        this->name=new char[strlen(n.name)+1];
        strcpy(this->name,n.name);
    }
    OperativenSistem &operator=(const OperativenSistem &n) {
        if (this!=&n) {
         delete [] name;
            this->verzija=n.verzija;
            this->tip=n.tip;
            this->golemina=n.golemina;
            this->name=new char[strlen(n.name)+1];
            strcpy(this->name,n.name);
        }
        return *this;
    }
    void pecati() {
     cout<<"Ime: "<<name;
        cout<<" Verzija: "<<verzija;
        cout<<" Tip: "<<tip;
        cout<<" Golemina:"<<golemina<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os) {
      if (this->golemina==os.golemina
          && this->verzija==os.verzija
          && this->tip==os.tip
          && strcmp(this->name,os.name)==0) {
          return true;
      }
        else return false;
    }
    int sporediVerzija(const OperativenSistem &os) {
     if (this->verzija==os.verzija)
         return 0;
       else if (this->verzija<os.verzija)
            return -1;
        else return 1;
    }
    bool istaFamilija(const OperativenSistem &sporedba) {
       if (this->tip==sporedba.tip
           && strcmp(this->name,sporedba.name)==0) {
           return true;
       }
        else return false;
    }
};
class Repozitorium {
private:
    friend class OperativenSistem;
    char name[20];
    OperativenSistem *niza;
    int broj;
public:
 Repozitorium(){

        strcpy(this->name,"");
        niza=nullptr;
        broj=0;
 }
    Repozitorium(const char *ime) {
        strcpy(this->name,ime);
        niza=nullptr;
        broj=0;
    }
    ~Repozitorium() {
        delete [] niza;
    }
    void pecatiOperativniSistemi() {
      cout<<"Repozitorium: "<<name<<endl;
        for (int i=0;i<broj;i++) {
           niza[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem) {
        OperativenSistem *temp;\
        int index=-1;
        temp=new OperativenSistem[broj-1];
        for (int i=0;i<broj;i++) {
            if (niza[i].ednakviSe(operativenSistem)) {
              index=i;
            }
        }
        if (index!=-1) {
            for (int i=0;i<broj;i++) {
                if (i!=index) {
                    temp[i]=niza[i];
                }

            }
            delete [] niza;
            niza=temp;
            broj--;
        }
    }

    void dodadi(const OperativenSistem &nov) {
        OperativenSistem *temp;
        bool flag=false;
        temp= new OperativenSistem[broj+1];
        for (int i=0;i<broj;i++) {
            if (niza[i].istaFamilija(nov)) {
               if (niza[i].verzija<nov.verzija) {
                    temp[i]=nov;
                   flag=true;
               }
            }
            temp[i]=niza[i];
        }
        if (flag==false) {
          temp[broj]=nov;
            broj++;
            delete [] niza;
            niza=temp;
        }
        else {
            delete [] niza;
            niza=temp;
        }
    }

};
int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}