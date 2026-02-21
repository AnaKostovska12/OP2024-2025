/* Да се напише класа во која ќе се чуваат основни податоци за вработен:
име
плата
работна позиција (работната позиција може да биде вработен, директор или шеф).
Напишете главна програма во која се читаат од стандарден влез податоци за N вработени,
а потоа се пачати листа на вработените сортирани според висината на платата во опаѓачки редослед. */

#include <iostream>
#include <string.h>
using namespace std;

enum position {
    employee, manager, owner
};

class Vraboten{
private:
    char ime[20];
    int plata;
    position p;
public:
    Vraboten(){

    }//prazen default Constructor без него не би можеле да напраите temporary
    Vraboten(char *imee,int plataa,position pp){
        strcpy(ime,imee);
        plata=plataa;
        p=pp;
    }
    ~Vraboten(){}
    void set_ime(char *imee){
        strcpy(ime,imee);
    }
    void set_plata(int plataa){
        plata=plataa;
    }
    void set_position(position pp){
        p=pp;
    }
    int get_plata(){
        return plata;
    }
    void get_everything(){
        cout<<"Vraboten : "<<ime;
        cout<<"plata : "<<plata;
        cout<<"pozicija : "<<p<<endl;
    }

};

void sort(Vraboten niza[],int n){
    Vraboten temp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1-i;j++){
            if(niza[j+1].get_plata()<niza[j].get_plata()){
                temp=niza[j+1];
                niza[j+1]=niza[j];
                niza[j]=temp;
            }
        }
    }
}

int main(){
    int n,plataa,pp;
    char imee[20];
    cout<<"Broj na vraboteni ";
    cin>>n;
    Vraboten niza[n],temp;
    for(int i=0;i<n;i++){
        cin>>imee;
        cin>>plataa;
        cin>>pp;
        niza[i].set_ime(imee);
        niza[i].set_plata(plataa);
        niza[i].set_position((position)pp);
    }
    sort(niza,n);
    for(int i=0;i<n;i++){
        niza[i].get_everything();
    }
}