/* Од стандарден влез се читаат податоци за непознат број студенти (не повеќе од 100). Податоците
се внесуваат така што во секој ред се состои од:

името
презимето
бројот на индекс (формат xxyzzzz)
четири броја (поени од секоја задача)
со произволен број празни места или табулатори меѓу нив.

Да се напише програма која ќе испечати список на студенти, каде во секој ред ќе има: презиме,
име, број на индекс, вкупен број на бодови сортиран според бројот на бодови. При тоа имињата
и презимињата да се напишат со голема почетна буква. */

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;
struct student{
    char ime[21];
    char prezime[21];
    int index;
    int poeni;
};
void uppercase(char ime[]){
    if(islower(ime[0])){
        ime[0]=toupper(ime[0]);
    }
}
int main()
{
    int n,a,b,c,d;
    cout<<"Kolku ke vnesete "<<endl;
    cin>>n;
    student Studenti[n];

    for(int i=0;i<n;i++){
        a=b=c=d=0;
        cout<<"Ime "<<endl;
        cin>>Studenti[i].ime;
        cout<<"Prezime "<<endl;
        cin>>Studenti[i].prezime;
        cout<<"Broj "<<endl;
        cin>>Studenti[i].index;
        cout<<"Poeni "<<endl;
        cin>>a>>b>>c>>d;
        Studenti[i].poeni=a+b+c+d;
        uppercase(Studenti[i].ime);
        uppercase(Studenti[i].prezime);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(Studenti[j].poeni>Studenti[j+1].poeni){
                student temp;
                Studenti[j]=temp;
                Studenti[j]=Studenti[j+1];
                Studenti[j+1]=temp;
            }
        }
    }

    cout << "Sortirani studenti: "<<endl;
    for (int i = 0; i < n; i++) {
        cout << Studenti[i].prezime << " " << Studenti[i].ime << " "
             << Studenti[i].index << " " << Studenti[i].poeni << endl;
    }


    return 0;
}