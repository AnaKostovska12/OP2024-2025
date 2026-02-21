/* Да се напише програма која ќе споредува два датуми (ден, месец, година) и
ќе ја пресмета разликата во денови од едниот до другиот датум. Пресметките
да се реализираат во посебни функции. За датумот да се дефинира посебна структура. */

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
struct datum{
    int den;
    int mesec;
    int godina;
};
//1 d1 e poblisku do realnosta
//-1 d2 e poblisku do realnosta
int redosled(datum d1,datum d2){
    if(d1.godina>d2.godina) return 1;
    else if(d1.godina<d2.godina) return -1;
    else if(d1.mesec>d2.mesec) return 1;
    else if(d1.mesec<d2.mesec) return -1;
    else if(d1.den>d2.den) return 1;
    else if(d1.den<d2.den) return -1;
    else return 0;
}
int main(){
    datum d1,d2;
    cout<<"Vnesi prv datum"<<endl;
    cin>>d1.den>>d1.mesec>>d1.godina;
    cout<<"Vnesi vtor datum"<<endl;
    cin>>d2.den>>d2.mesec>>d2.godina;
    if(redosled(d1,d2)==-1){
        datum temp=d1;
        d1=d2;
        d2=temp;
    }
    if(redosled(d1,d2)==0){
        cout<<"Stanuva zbor za istiot datum"<<endl;

    }
    int brojdenovi=0;
    brojdenovi+=(d1.godina-d2.godina)*365;
    brojdenovi+=(d1.mesec-d2.mesec)*30;
    brojdenovi+=(d1.den-d2.den);
    cout<<"Razlikata vo denovi iznesuva"<<endl;
    cout<<brojdenovi;
    return 0;
}