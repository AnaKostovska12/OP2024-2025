using namespace std;
#include <iostream>
#include <cstring>
struct Laptop {
    char firma[100];
    float monitor;
    bool touch;
    int cena;
    void print() {
        cout<<firma<<" "<<monitor<<" "<<cena<<endl;
    }
};
struct ITStore {
    char name[100];
    char lokacija[100];
    Laptop dostapni[100];
    int broj;
    void print() {
        cout<<name<<" "<<lokacija<<endl;
        for (int i=0;i<broj;i++) {
            dostapni[i].print();
        }
    }
    Laptop najeftin() {
        Laptop temp;
        bool flag=1;

        for (int i=0;i<broj;i++) {
            if (dostapni[i].touch && flag) {
                temp=dostapni[i];
                flag=false;
            }
            if (dostapni[i].touch && !flag&&
                dostapni[i].cena<temp.cena) {
                temp=dostapni[i];
                }

        }
        return temp;
    }
    void print_only() {
        cout<<name<<" "<<lokacija<<endl;
    }

};
void najeftina_ponuva(ITStore *s,int n) {
    ITStore temp=s[0];
    Laptop tempp=s[0].najeftin();
    int min=s[0].najeftin().cena;
    for (int i=0;i<n;i++) {
        if (s[i].najeftin().cena<min) {
            min=s[i].najeftin().cena;
            temp=s[i];
            tempp=s[i].najeftin();
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata: "<<endl;
    temp.print_only();
    cout<<"Najniskata cena iznesuva: ";
    cout<<tempp.cena;


}

int main() {
    ITStore s[100];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s[i].name;
        cin>>s[i].lokacija;
        cin>>s[i].broj;
        for(int j=0;j<s[i].broj;j++){
            cin>>s[i].dostapni[j].firma;
            cin>>s[i].dostapni[j].monitor;
            cin>>s[i].dostapni[j].touch;
            cin>>s[i].dostapni[j].cena;
        }
    }
    for(int i=0;i<n;i++) {
        s[i].print();
    }
    najeftina_ponuva(s,n);
    // scanf("%d",&n); //broj na IT prodavnici

    // //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv



    // //pecatenje na site prodavnici




    // //povik na glavnata metoda
    // najeftina_ponuda(s, n);

    return 0;
}