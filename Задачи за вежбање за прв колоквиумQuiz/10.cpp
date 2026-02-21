using namespace std;
#include <iostream>
#include <cstring>
struct Igrac {
    char korisnickoIme[15];
    int nivo;
    int poeni;

};
struct KompjuterskaIgra {
    char ime[15];
    Igrac lista[30];
    int n;

};
void najdobarIgrac(KompjuterskaIgra *lista,int n) {
    int max=0;
    KompjuterskaIgra temp;
    for(int i=0;i<n;i++) {
        if (lista[i].n>max) {
            max=lista[i].n;
            temp=lista[i];
        }

    }
    int maxpoeni=0;
    Igrac naj;
    for(int i=0;i<temp.n;i++) {
        if (temp.lista[i].poeni>maxpoeni) {
            maxpoeni=temp.lista[i].poeni;
            naj=temp.lista[i];
        }
        if(temp.lista[i].poeni==max){
            if(temp.lista[i].nivo>naj.nivo){
                naj=temp.lista[i];
            }
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<naj.korisnickoIme<<" koj ja igra igrata "<<temp.ime<<endl;
}
int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
