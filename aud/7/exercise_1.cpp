/* Да се дефинира класа HotelReservation (име, презиме, денови, лица).
Од неа се изведува HalfBoardHotelReservation каде цената е повисока за 5 евра по лице.
Класата Hotel содржи метод pay() кој преку полиморфизам пресметува цена и враќа кусур. */

#include <iostream>
#include <string>
using namespace std;

class HotelReservation{
  protected:
     int broj_denovi;
     int broj_lica;
     string name;
     string surname;
     public:
       HotelReservation(){
         broj_denovi=0;
         broj_lica=0;
         name="";
         surname="";
       }

     HotelReservation(string name,string surname,int broj_denovi,int broj_lica){
       this->broj_denovi=broj_denovi;
       this->broj_lica=broj_lica;
       this->name=name;
       this->surname=surname;
     }
     HotelReservation(const HotelReservation& n){
         this->broj_denovi=n.broj_denovi;
         this->broj_lica=n.broj_lica;
         this->name=n.name;
         this->surname=n.surname;
     }
     HotelReservation& operator=(const HotelReservation& n){
       if(this!=&n){
         this->broj_denovi=n.broj_denovi;
         this->broj_lica=n.broj_lica;
         this->name=n.name;
         this->surname=n.surname;
       }
       return *this;
     };
     ~HotelReservation(){}
      virtual int price(){
       return this->broj_denovi*this->broj_lica*25;}
    virtual  int price (int amount){
       if(price()<=amount){
         return amount-price();
       }
       else return -1;
     }

};

class  HalfBoardHotelReservation : public HotelReservation{
  public:
    HalfBoardHotelReservation(string name,string surname,int broj_denovi,int broj_lica):
    HotelReservation(name,surname,broj_denovi,broj_lica){}

     ~HalfBoardHotelReservation(){}
    int price() override {
      return HotelReservation::price()+broj_lica*5*broj_denovi;
    }
     int price (int amount){
      int cena=price();
       if(cena<=amount){
         return amount-cena;
       }
       else return -1;
     }

};

class Hotel{
    private:
      string name;
      int saldo;
      public:
        Hotel(string name):name(name), saldo(0){};
        Hotel(const Hotel& n){
          this->saldo=n.saldo;
          this->name=n.name;
        }
        Hotel& operator=(const Hotel& n){
          if(this!=&n){
            this->saldo=n.saldo;
            this->name=n.name;
          }
          return *this;
        }
        ~Hotel(){}
        int pay(HotelReservation& n,int amount){
          int p = n.price();
          if(p<=amount){
            saldo+=p;
            return n.price(amount);
          }
          return -1;
        }
};

int main() {
  Hotel h("Bristol");
  HotelReservation *hr1 = new HotelReservation("Petko", "Petkovski", 5, 5);
  int cena = h.pay(*hr1, 1000);
  if (cena != -1)
    cout << "Kusur : " << cena << endl;

  HalfBoardHotelReservation *hr2 = new HalfBoardHotelReservation("Risto", "Ristovski", 5, 5);
  cena = h.pay(*hr2, 1000);
  if (cena != -1)
    cout << "Kusur : " << cena << endl;

  HotelReservation *hr3 = new HalfBoardHotelReservation("Ana", "Anovska", 4, 2);
  cena = h.pay(*hr3, 100);
  if (cena != -1)
    cout << "Kusur : " << cena << endl;

  HalfBoardHotelReservation hr4("Tome", "Tomovski", 5, 3);
  cena = h.pay(hr4, 1000);
  if (cena != -1)
    cout << "Kusur : " << cena << endl;

  return 0;
}