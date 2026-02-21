#include<iostream>
#include <cstring>
using namespace std;
struct Voz {
    char relacija[50];
    float km;
    int patnici;
};
struct ZeleznickaStanica {
    char grad[20];
    Voz poagjaat[30];
    int broj_vozovi;
};
void najkratkaRelacija(ZeleznickaStanica *z,int n,char * grad) {
    int min;
    Voz temp;
    bool flag=true;
    for (int i = 0; i < n; i++) {
        if (strcmp(z[i].grad, grad) == 0){
            for (int j = 0; j < z[i].broj_vozovi; j++) {
                if (flag){
                    temp=z[i].poagjaat[j];
                    min=z[i].poagjaat[j].km;
                    flag=false;}
                if (!flag && min>=z[i].poagjaat[j].km) {
                    min=z[i].poagjaat[j].km;
                    temp=z[i].poagjaat[j];
                }
            }
        }

    }  cout<<"Najkratka relacija: "<<temp.relacija<<" ("<<temp.km<<" km)  "<<endl;
}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>zStanica[i].grad;
        cin>>zStanica[i].broj_vozovi;
        for(int j=0;j<zStanica[i].broj_vozovi;j++){
            cin>>zStanica[i].poagjaat[j].relacija;
            cin>>zStanica[i].poagjaat[j].km;
            cin>>zStanica[i].poagjaat[j].patnici;
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
