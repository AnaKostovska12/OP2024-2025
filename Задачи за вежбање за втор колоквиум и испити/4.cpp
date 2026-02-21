using namespace std;
#include <iostream>
#include <cstring>

using namespace std;
#include <iostream>
#include <cstring>
class Pizza {
protected:
    char name[21];
    char sostojki[101];
    float osnovnaa;
public:
  Pizza(char *name="",char *sostojki="",float osnovnaa=0) {
    strcpy(this->name,name);
    strcpy(this->sostojki,sostojki);
    this->osnovnaa=osnovnaa;
  }
  Pizza(const Pizza &p) {
    strcpy(this->name,p.name);
    strcpy(this->sostojki,p.sostojki);
    this->osnovnaa=p.osnovnaa;
  }
  Pizza &operator=(const Pizza &p) {
    if (this != &p) {
      strcpy(this->name,p.name);
      strcpy(this->sostojki,p.sostojki);
      this->osnovnaa=p.osnovnaa;
    }
    return *this;
  }
  virtual void print()=0;
  ~Pizza() {}
  virtual double price() =0;
    bool operator<( Pizza &p) {
      return price()<p.price();
    }
  virtual double osnovna()=0;

};
enum Size {
  mala,golema,familijarna
};
class FlatPizza : public Pizza {
private:
  Size golemina;

public:
  ~FlatPizza() {}
  FlatPizza(char *name,char *sostojki,float osnovnaa)
  : Pizza(name,sostojki,osnovnaa) {
    golemina=mala;
  }
  FlatPizza(char *name,char *sostojki,float osnovnaa,Size golemina)
    :Pizza(name,sostojki,osnovnaa)
  {
    this->golemina=golemina;
  };
  double price()override {
    if (golemina==mala) {
      return osnovnaa*1.1;
    }
    else  if (golemina==golema) {
      return osnovnaa*1.2;
    }
    else  if (golemina==familijarna) {
      return osnovnaa*1.3;
    }
  }
 friend  ostream &operator<<(ostream &out,  FlatPizza &fp) {
    out << fp.name << ": " << fp.sostojki << ", ";
    if (fp.golemina == mala) out << "small";
    else if (fp.golemina == golema) out << "large";
    else if (fp.golemina == familijarna) out << "family";
    out << " - " << fp.price() << endl;
    return out;
  }
    double osnovna()override {
    return osnovnaa;
  }
  void print()override {
    cout << name << ": " << sostojki << ", ";
    if (golemina == mala) cout << "small";
    else if (golemina == golema) cout << "large";
    else if (golemina == familijarna) cout << "family";
    cout << " - " << price() << endl;
  }
};
class FoldedPizza : public Pizza {
private:
  bool beloBrashno;

public:
  double osnovna()override {
    return osnovnaa;
  }
  FoldedPizza(){
      this->beloBrashno=true;
  }
  ~FoldedPizza() {}
  FoldedPizza(char *name,char *sostojki,float osnovnaa)
    : Pizza(name,sostojki,osnovnaa)
  {
    this->beloBrashno=true;
  }
//   FoldedPizza(char *name,char *sostojki,float osnovnaa,bool beloBrashno)
//     :Pizza(name,sostojki,osnovnaa) {
//     this->beloBrashno=beloBrashno;
//   }
  double price()override {
    if (beloBrashno) {
      return osnovnaa*1.1;
    }
    else return osnovnaa*1.3;
  }
  void setWhiteFlour(bool white) {
    this->beloBrashno=white;
  }
friend  ostream &operator<<(ostream &out, FoldedPizza &fp) {
    out << fp.name << ": " << fp.sostojki << ", ";
    out << (fp.beloBrashno ? "wf" : "nwf");
    out << " - " << fp.price() << endl;
    return out;
  }
  void print()override {
    cout << name << ": " << sostojki << ", ";
    cout << (beloBrashno ? "wf" : "nwf");
    cout << " - " << price() << endl;
  }
};

void expensivePizza(Pizza ** niza, int n) {
  int max=-1;
  int index=0;
  for (int i=0;i<n;i++) {
    if (niza[i]->price()>max) {
      max=niza[i]->price();
      index=i;
    }
  }
 niza[index]->print();
// cout<<niza[index];
// cout<<&niza[index];
};
// Testing

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
