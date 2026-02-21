using namespace std;
#include <cstring>
#include <iostream>
struct SkiLift {
    char ime[15];
    int max_skijaci;
    bool voUpotreba;
};
struct SkiCenter {
    char ime[15];
    char drzava[20];
    SkiLift niza[20];
    int br_lifts;
    int kapacitet() {
        int zbir=0;
        for (int i = 0; i < br_lifts; i++) {
            if (niza[i].voUpotreba) {
                zbir+=niza[i].max_skijaci;
            }
        }
        return zbir;
    }
    void print() {
        cout<<ime<<endl;
        cout<<drzava<<endl;
        cout<<kapacitet();
    }

};
void najgolemKapacitet(SkiCenter *sc,int n) {
    int max=sc[0].kapacitet();
    SkiCenter temp=sc[0];
    for (int i = 0; i < n; i++) {
        if (sc[i].kapacitet() > max) {
            max=sc[i].kapacitet();
            temp=sc[i];
        }
    }
    temp.print();

}
int main()
{
    int i, j, n, broj;
    SkiCenter sc[20];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        //printf("Ime:");
        scanf("%s", sc[i].ime);
        //printf("\nDrzava:");
        scanf("%s", sc[i].drzava);
        scanf("%d", &sc[i].br_lifts);

        for (j = 0; j < sc[i].br_lifts; j++){
            scanf("%s", sc[i].niza[j].ime);
            scanf("%d", &sc[i].niza[j].max_skijaci);
            scanf("%d", &sc[i].niza[j].voUpotreba);
        }
    }
    najgolemKapacitet(sc, n);

    return 0;
}
