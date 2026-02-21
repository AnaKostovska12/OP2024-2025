/* Да се дефинира класа TennisPlayer. Од неа да се изведе класа RankedTennisPlayer
која дополнително чува ранг на тенисерот. Да се прикаже како се врши кастинг
од изведена во основна класа. */

#include <iostream>
#include <string>
using namespace std;

 class TennisPlayer {
 protected:
     string name;
     string surname;
     bool league;
     public:
     TennisPlayer() {
         league = false;
         name=" ";
         surname=" ";
     }
     TennisPlayer(string name, string surname) {
         this->league = false;
         this->name=name;
         this->surname=surname;
     }
     TennisPlayer(string name, string surname,bool league) {
         this->league = league;
         this->name=name;
         this->surname=surname;
     }
     TennisPlayer(const TennisPlayer &p) {
         this->league = p.league;
         this->name=p.name;
         this->surname=p.surname;
     }
     TennisPlayer &operator=(const TennisPlayer &p) {
         if (this!=&p) {
             this->league = p.league;
             this->name=p.name;
             this->surname=p.surname;
         }
         return *this;
     }
     void print() {
         cout<<name<<" "<<surname<<" ";
     }
     friend ostream &operator<<(ostream &os, const TennisPlayer &p) {
         os<<p.name<<" "<<p.surname<<" ";
         return os;
     }
 };

 class RankedTennisPlayer : public TennisPlayer {
 private:
     int rank;
     public:
     RankedTennisPlayer(string name, string surname,bool league, int rank) : TennisPlayer(name,surname,league) {
         this->rank=rank;
     }
     RankedTennisPlayer() {
         this->rank=0;
     }
     RankedTennisPlayer(const RankedTennisPlayer &p) {
         TennisPlayer::operator=(p);
         this->rank=p.rank;
     }
     RankedTennisPlayer(const TennisPlayer n,int rank) : TennisPlayer(n){
         this->rank=rank;
     };
     friend ostream &operator<<(ostream &os, RankedTennisPlayer &p) {
         os<<p.rank<<" ";
         os<<TennisPlayer(p)<<endl;
         return os;
     }
 };

 int main() {
     TennisPlayer rf("Roger", "Federer");
     TennisPlayer ng("Novak", "Djokovikj");
     cout << rf << endl;
     cout << ng << endl;
     RankedTennisPlayer rn("Rafael", "Nadal", true, 2750);
     cout << rn;
     TennisPlayer tp = rn;
     cout << tp << endl;
     RankedTennisPlayer copy(ng, 3320);
     cout << copy;
     return 0;
}