/*Да се креира класа BasketballPlayer која ќе ги чува следните информации:

    име на кошаркарот (низа од знаци не подолга од 20 карактери)
    презиме на кошаркарот (низа од знаци не подолга од 20 карактери)
    број на дрес (цел број)
    поени од прв натпревар (цел број)
    поени од втор натпревар (цел број)
    поени од трет натпревар (цел број)

Да се направат потребните методи за класата, како и метод за печатење на информации за
кошаркарот во следен формат
"Player: name surname with number: number has avg_pts points on average".

Од стандарден влез се внесуваат име, презиме, број на дрес и поени за сите три натпревари
за еден кошаркар.

На стандарден излез се печатат информациите за кошаркарот.*/

#include <iostream>
#include <string.h>
using namespace std;

class BasketballPlayer {
private:
    char name[20];
    char surname[20];
    int number;
    int prv,vtor,tret;
public:
    void set_name(char *namee) {
        strcpy(name,namee);
    }
    void set_surname(char *surnamee) {
        strcpy(surname,surnamee);
    }
    void  set_number(int numberr) {
        number=numberr;
    }
    void set_poeni(int prvv,int vtorr,int trett) {
        prv=prvv;
        vtor=vtorr;
        tret=trett;
    }

    void print() {
        int average=(prv+vtor+tret)/3;
        cout<<"Player Name: "<<name<<" "<<surname<<":"<<number<<"has "<<average<<"on average"<<endl;
    }

};
int main() {
    char namee[20],surnamee[20];
    int numberr,prvv,vtorr,trett;
    BasketballPlayer igrac;
    cin.getline(namee,20);
    igrac.set_name(namee);
    cin.getline(surnamee,20);
    igrac.set_surname(surnamee);
    cin>>numberr;
    igrac.set_number(numberr);
    cin>>prvv>>vtorr>>trett;
    igrac.set_poeni(prvv,vtorr,trett);
    igrac.print();
    return 0;
}