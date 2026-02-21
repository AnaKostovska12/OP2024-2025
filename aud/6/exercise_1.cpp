/* Да се дефинира класа Ucenik (име, просек, година).
Да се дефинира класа Paralelka која содржи динамички алоцирана низа од ученици.
Да се преоптоварат операторите += за додавање ученик и ++ за зголемување на годината на сите ученици. */

#include <iostream>
#include <cstring>
using namespace std;

class Paralelka;

class Ucenik {
private:
 friend class Paralelka;
 char *name;
 float prosek;
 int godina;
 public:
 Ucenik() {
  name=nullptr;
  prosek=0;
  godina=0;
 }
 Ucenik (const Ucenik &n) {
  name = new char[strlen(n.name)+1];
  strcpy(this->name,n.name);
  this->prosek = n.prosek;
  this->godina = n.godina;
 }
 Ucenik &operator=(const Ucenik &n) {
  if (this!=&n) {
   delete [] name;
   name = new char[strlen(n.name)+1];
   strcpy(this->name,n.name);
   this->prosek = n.prosek;
   this->godina = n.godina;
  }
  return *this;
 }
 Ucenik(char *name,float prosek,int godina) {
  this->name = new char[strlen(name)+1];
  strcpy(this->name,name);
  this->prosek = prosek;
  this->godina = godina;
 }
 ~Ucenik() {
  delete [] name;
 }
 Ucenik &operator++() {
  godina++;
  return *this;
 }
 Ucenik operator++(int) {
  Ucenik temp = *this;
  godina++;
  return temp;
 }
 friend ostream &operator<<(ostream &out, const Ucenik &u) {
  out<<u.name<<" "<<u.prosek<<" "<<u.godina;
  return out;
 }
 bool operator<(const Ucenik &u) {
  return prosek<u.prosek;
 }
};

class Paralelka {
 private:
 friend class Ucenik;
 int broj;
 Ucenik *niza;
public:
 Paralelka(Ucenik *niza,int broj) {
  this->broj=broj;
  this->niza= new Ucenik [broj];
  for (int i=0;i<broj;i++) {
      this->niza[i]=niza[i];
  }
 }
 Paralelka(const Paralelka &n) {
  this->broj=n.broj;
  this->niza= new Ucenik [n.broj];
  for (int i=0;i<n.broj;i++) {
   this->niza[i]=n.niza[i];
  }
 }
 Paralelka() {
  broj=0;
  niza=nullptr;
 }
 ~Paralelka() {
  delete [] niza;
 }
 Paralelka operator+=(Ucenik &nov) {
  Ucenik *temp;
  temp=new Ucenik[(this->broj)+1];
  for (int i=0;i<(this->broj);i++) {
   temp[i]=this->niza[i];
  }
  temp[broj++]=nov;
  delete [] niza;
  niza=temp;
  return *this;
 }
 Paralelka &operator++() {
  for (int i=0;i<(this->broj);i++) {
   niza[i]++;
  }
  return *this;
 };
 Paralelka &operator++(int) {
  Paralelka temp = *this;
  for (int i=0;i<(this->broj);i++) {
   niza[i]++;
  }
  return temp;
 }
 friend ostream &operator<<(ostream &out, const Paralelka &p) {
  for (int i=0;i<p.broj;i++) {
   out<<p.niza[i]<<" ";
  };
  return out;
 }
 void nagradi() {
  for (int i=0;i<broj;i++) {
   if (niza[i].prosek==10.0) {
    cout<<niza[i]<<" ";
   }
  }
 };
 void najvisokProsek() {
  float max=-1;
  for (int i=0;i<broj;i++) {
   if (max<niza[i].prosek) {
    max=niza[i].prosek;
   }
  }
  cout<<max<<endl;
 }
};

int main ()
{
 Ucenik u1("Martina Martinovska", 9.5, 3);
 Ucenik u2("Darko Darkoski", 7.3, 2);
 Ucenik u3("Angela Angelovska", 10, 3);

 Paralelka p;
 p += u1;
 p += u2;
 p += u3;

 cout << p;
 cout << "Nagradeni:" << endl;
 p.nagradi();
 cout << endl;
 p.najvisokProsek();
 cout << endl;

 u2++;
 cout << p;
 cout << endl;
 p++;
 cout << p;

 return 0;
}