/*Да се дефинира класа SpaceObject во која ќе се чуваат информации за:
product_name (низа од максимум 100 карактери) - име на објектот
type (низа од максимум 100 карактери) - тип на објектот
distanceFromEarth (цел број) - оддалеченост од Земја
методи кои што класата треба да ги има:
print()-Принта во формат:
"[product_name] ( [type] ) - distance: [distanceFromEarth] light years away from Earth".
Да се дефинира класа Alien во која ќе се чуваат информации за:
product_name (низа од максимум 100 карактери) - име
age (цел број) - возраст
homePlanet (низа од максимум 100 карактери) - планета на која што живее
numObj (цел број) - број на омилени вселенски објекти
spaceObjects (низа од SpaceObject објекти) - омилени вселенски објекти
методи кои што класата треба да ги има:
SpaceObject getObjectClosestToEarth()
- Ќе го врати објектот кој што им е еден од омилените а има најмала оддалеченост од Земјата.
print()
-Принта во формат:
Alien product_name: ...
Alien age: ...
Alien homePlanet: ...
Favourite space object closest to earth: ....
Сите променливи внатре во класите треба да бидат приватни. Соодветно во рамките на класите да се дефинираат:
конструктор (без и со параметри)
деструктор
set методи
get методи
copy constructor
ДА НЕ СЕ МЕНУВА main() ФУНКЦИЈАТА.*/

#include <iostream>
#include <cstring>
using namespace std;

class SpaceObject {
private:
 char product_name[100];
 char type[100];
 int distanceFromEarth;
public:
 SpaceObject() {};
 SpaceObject(char *product_namee, char *typee, int distanceFromEarthh) {
  strcpy(product_name, product_namee);
  strcpy(type, typee);
  this->distanceFromEarth = distanceFromEarthh;
 }
 int getDistanceFromEarth() {
  return distanceFromEarth;
 }
 ~SpaceObject() {};
 void print(){
  cout<<"[ "<<product_name<<"] ( ["<<type<<"] ) - distance : ["<<distanceFromEarth<<"] light years away from Earth.";
 }
};
 class Alien {
  private:
  char product_name[100];
  int age;
  char homePlanet[100];
  int numObj;
  SpaceObject spaceobjects[100];
 public:
  Alien() {};
  ~Alien() {};
  Alien(char *product_namee, int agee, char *homePlanett, int numObjj,SpaceObject *spaceobjectss) {
   strcpy(product_name, product_namee);
   age = agee;
   strcpy(homePlanet, homePlanett);
   numObj = numObjj;
   for (int i = 0; i < numObj; i++) {
    spaceobjects[i] = spaceobjectss[i];
   }

  };
  void getSpaceObject() {
   SpaceObject povolna = spaceobjects[0];
   for (int i=1;i<numObj;i++){
    if (povolna.getDistanceFromEarth()>spaceobjects[i].getDistanceFromEarth()) {
     povolna=spaceobjects[i];
    }
   }
   povolna.print();
  }
  void print() {
   cout<<"Alien product name :"<<product_name<<endl;
   cout<<"Alien age : "<<age<<endl;
   cout<<"Alien home planet : "<<homePlanet<<endl;
   cout<<"Favorite space object closest to Earth: ";
   getSpaceObject();
  }

 };
int main() {
 char name[100], homePlanet[100];
 int age, numObj;
 cin >> name >> age >> homePlanet >> numObj;
 SpaceObject spaceObjects[numObj];
 for (int i = 0; i < numObj; i++) {
  char spaceObjectName[100], spaceObjectType[100];
  int distanceFromEarth;
  cin >> spaceObjectName >> spaceObjectType >> distanceFromEarth;
  spaceObjects[i] = SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
 }
 Alien alien(name, age, homePlanet, numObj, spaceObjects);
 alien.print();
 return 0;
}