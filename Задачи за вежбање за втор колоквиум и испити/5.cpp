using namespace std;
#include <iostream>
#include <cstring>
#define MAX 100
enum typeC {
  standard,loyal,vip

};
class UserExistsException {
public:
 void message() {
        cout << "The user already exists in the list!" << endl;
    }
};
class Customer {
protected:
    char name[50];
    char email[50];
    typeC tip;
    int brKupeni;
 static int osnovenPopust;
 const static int dopolnitelenPopust=20;

public:
  Customer() {
    tip = standard;
    brKupeni = 0;
    strcpy(name," ");
    strcpy(email," ");
  }
  Customer(char *name ,char *email,typeC tip=standard,int brKupeni=0) {
    strcpy(this->name,name);
    strcpy(this->email,email);
    this->tip=tip;
    this->brKupeni=brKupeni;
    if (tip==loyal) {
      osnovenPopust=10;
    }
  }
  Customer(const Customer &c) {
    strcpy(this->name,c.name);
    strcpy(this->email,c.email);
    this->tip=c.tip;
    this->brKupeni=c.brKupeni;
  }
  Customer &operator=(const Customer &c) {
    if (this!=&c) {
      strcpy(this->name,c.name);
      strcpy(this->email,c.email);
      this->tip=c.tip;
      this->brKupeni=c.brKupeni;
    }
    return *this;
  }
  double popust() {
    if (tip==loyal) {
      return osnovenPopust;
    }

    else  if (tip==vip) {
      return dopolnitelenPopust+osnovenPopust;
    }
    else return 0;
  }
  friend ostream &operator<<(ostream &os,  Customer &c) {
    os << c.name <<endl;
    os << c.email <<endl;
    os << c.brKupeni <<endl;
    if (c.tip==loyal) {
      os<<"loyal "<<c.popust();
    }
    if (c.tip==standard) {
      os<<"standard "<<c.popust();
    }
    if (c.tip==vip) {
      os<<"vip "<<c.popust();
    }
   return os;
  }
  void setDiscount1(int osnovenPopust) {
    Customer::osnovenPopust=osnovenPopust;
  }
char *mail() {
    return email;
  }
  int br() {
    return brKupeni;
  }
  typeC t() {
    return tip;
  }
  void setType(typeC t) {
    tip=t;
  }
};
class FINKI_bookstore {
private:
  Customer *niza;
  int broj;
public:
  FINKI_bookstore() {
    niza=NULL;
    broj=0;
  }
  FINKI_bookstore(const FINKI_bookstore &n) {
  this-> niza= new Customer[n.broj];
    broj=n.broj;
    for (int i=0;i<n.broj;i++) {
      this->niza[i]=n.niza[i];
    }
  }
  FINKI_bookstore &operator=(const FINKI_bookstore &other) {
    if (this != &other) {
      delete[] niza;
      broj = other.broj;
      niza = new Customer[broj];
      for (int i = 0; i < broj; i++) {
        niza[i] = other.niza[i];
      }
    }
    return *this;
  }
  void setCustomers(Customer *niza,int n) {
    delete[ ] this->niza;
    this->niza=new Customer[n];
    broj=n;
    for (int i=0;i<n;i++) {
      this->niza[i]=niza[i];
    }
  }
  FINKI_bookstore &operator+=(Customer &c) {
    for (int i = 0; i < broj; i++) {
      if (strcmp(niza[i].mail(), c.mail()) == 0) {
            UserExistsException n;
            throw n;  // Exception will print error
      }
    }

    Customer *temp = new Customer[broj + 1];
    for (int i = 0; i < broj; i++) {
      temp[i] = niza[i];
    }
    temp[broj] = c;
    broj++;

    delete[] niza;
    niza = temp;

    return *this;
  }
  ~FINKI_bookstore() {
    delete [] niza;
  }
   void update() {
    for (int i=0;i<broj;i++) {
      if (niza[i].br()>5 && niza[i].t()==standard) {
        niza[i].setType(loyal);
      }
    else  if (niza[i].br()>10 && niza[i].t()==loyal) {
        niza[i].setType(vip);
      }
    }
  }
  friend ostream &operator<<(ostream &os,  FINKI_bookstore &b) {
    for (int i=0;i<b.broj;i++) {
      os << b.niza[i]<< endl;
    }
    return os;
  }
};

int Customer::osnovenPopust=10;
int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;
    cout<<endl;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
      try{fc+=c;}
      catch (UserExistsException &n){
          n.message();
      };


    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }
    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
   try{  fc+=c;}
      catch (UserExistsException &n) {
          n.message();
      }


    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
