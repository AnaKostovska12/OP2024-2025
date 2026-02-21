using namespace std;
#include <iostream>
#include <cstring>
struct Vozenje {
    char ime[20];
    int traenje;
    float cena;
    bool daliPopust;

};
struct ZabavenPark {
    char ime[100];
    char lokacija[100];
    Vozenje niza[100];
    int n;
    int traenje(){
        int zbir=0;
        for (int i=0;i<n;i++) {
            zbir+=niza[i].traenje;
        }
        return zbir;
    }
    void pecati() {
        cout<<ime<<" "<<lokacija<<endl;
        for(int i=0;i<n;i++) {
            cout<<niza[i].ime<<" "<<niza[i].traenje<<" "<<niza[i].cena<<endl;
        }
    }
    int cena(){
        int counter=0;
        for (int i=0;i<n;i++) {

            if (niza[i].daliPopust) {
                counter++;
            }

        }
        return counter;
    };
    void pecatiIme(){
        cout<<ime<<" "<<lokacija<<endl;
    }
};
void najdobar_park(ZabavenPark *niza,int n)
{
    ZabavenPark temp=niza[0];
    for(int i=1;i<n;i++) {
        if (niza[i].cena()>temp.cena()) {
            temp=niza[i];
        }
        else if (niza[i].cena()==temp.cena() && niza[i].traenje()>=temp.traenje()) {
            temp=niza[i];
        }
    }
    cout<<"Najdobar park: "; temp.pecatiIme();
}
void pecati(ZabavenPark *niza,int n){
    for(int i=0;i<n;i++){
        niza[i].pecati();
    }
}


int main()
{
    int i, j, n, broj;
    //kreiraj niza od maksimum 100 zabavni parkovi
    ZabavenPark ff[100];
    scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
        //ime na festivalot
        scanf("%s", ff[i].ime);
        //mesto
        scanf("%s", ff[i].lokacija);
        //broj na filmovi
        scanf("%d", &ff[i].n);

        for (j = 0; j < ff[i].n; j++){
            scanf("%s", ff[i].niza[j].ime);  			/* Ime na filmot */
            scanf("%d", &ff[i].niza[j].traenje); 		/* Vremetraenje   */
            scanf("%f", &ff[i].niza[j].cena); 	/* Cena */
            scanf("%d", &ff[i].niza[j].daliPopust);	/* Popust */

        }


    }
    pecati(ff,n);
    najdobar_park(ff,n);

    return 0;
}