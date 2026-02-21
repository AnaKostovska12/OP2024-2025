/*Да се напише програма која од стандарден влез ќе чита податоци за држави и на екран ќе го отпечати името и презимето на претседателот на државата чиj што главен град има најмногу жители. Податоци за држава:

име
претседател
главен град
број на жители.
Податоци за град:

име
број на жители.
Податоци за претседател:

име
презиме
политичка партија.   */

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
struct glaven_grad{
    char ime[20];
    int broj_ziteli;

};
struct president{
    char ime[20];
    char prezime[20];
};
struct drzava{
    president Pretsedatel;
    glaven_grad Glaven;
    char ime_drzava[20];
    int broj_gragjani;

};

void read(int n,drzava niza[]){
    for(int i=0;i<n;i++){
        cin>>niza[i].ime_drzava;
        cin>>niza[i].Pretsedatel.ime;
        cin>>niza[i].Pretsedatel.prezime;
        cin>>niza[i].Glaven.ime;
        cin>>niza[i].Glaven.broj_ziteli;
    }
}
void max_capital(int n, drzava niza[]){
    president max;
    int max_ziteli=0;
    for(int i=0;i<n;i++){
        if(niza[i].Glaven.broj_ziteli>max_ziteli){
            max_ziteli=niza[i].Glaven.broj_ziteli;
            max=niza[i].Pretsedatel;
        }
    }
    cout<<max.ime<<" "<<max.prezime<<endl;
}

int main(){
    drzava niza[100];
    int n;
    cin >> n;
    read(n,niza);
    max_capital(n,niza);
    return 0;
}