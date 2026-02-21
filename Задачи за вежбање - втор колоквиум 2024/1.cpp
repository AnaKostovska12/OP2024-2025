#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class NoProductFoundException {
private:
    string kat;
public:
    NoProductFoundException () {
        kat="";
    }
    NoProductFoundException(string kat) {
        this->kat=kat;
    }
    void print() {
        cout<<"No products from category "<<kat<<" were found in the store"<<endl;
    }
};
class Product {
private:
    string name;
    string kategorija;
    int cena;
    int kolicina;
public:
    Product() {
        name="";
        kategorija="";
        cena=0;
        kolicina=0;
    }
    Product(string name,string kategorija,int cena,int kolicina) {
        this->name=name;
        this->kategorija=kategorija;
        this->cena=cena;
        this->kolicina=kolicina;
    }
    Product (const Product &n) {
        this->name=n.name;
        this->kategorija=n.kategorija;
        this->cena=n.cena;
        this->kolicina=n.kolicina;
    }
    Product &operator=(const Product &n) {
        if (this!=&n) {
            this->name=n.name;
            this->kategorija=n.kategorija;
            this->cena=n.cena;
            this->kolicina=n.kolicina;
        }
        return *this;
    }
    int totalPrice() const {
        return cena*kolicina;
    }
    friend ostream &operator<<(ostream &out,const Product &n) {
        out<<n.name<<" ("<<n.kategorija<<") "<<n.cena<<" x "<<n.kolicina<<" = ";
        out<<n.totalPrice();
        return out;
    }
    string getKategorija() {
        return kategorija;
    }
    friend istream &operator>>(istream &in,Product &n) {
        getline(in,n.name);
        getline(in,n.kategorija);
        in>>n.kolicina>>n.cena;
        in.ignore();
        return in;
    }
};
class Store {
private:
    Product *niza;
    int n;
public:
    Store() {
        n=0;
        niza=nullptr;
    }
    Store(const Store &a) {
        this->n=a.n;
        niza= new Product [n];
        for (int i=0;i<n;i++) {
            niza[i]=a.niza[i];
        }
    }
    Store &operator=(const Store &a) {
        if (this!=&a) {
            delete [] niza;
            this->n=a.n;
            niza= new Product [n];
            for (int i=0;i<n;i++) {
                niza[i]=a.niza[i];
            }
        }
        return *this;
    }
    ~Store () {
        delete [] niza;
    }
    Store &operator+=(Product &a) {
        Product *temp= new Product [n+1];
        for (int i=0;i<n;i++) {
            temp[i]=niza[i];
        }
        temp[n++]=a;
        delete [] niza;
        niza= temp;
        return *this;
    }
    friend ostream &operator<<(ostream &out,const Store &n) {

        for (int i=0;i<n.n;i++) {
            out<<n.niza[i]<<endl;
        }
        return out;
    }
    Store fromCategory (string & category) {
        Store temp;
        int counter=0;
        for (int i=0;i<n;i++) {
            if (niza[i].getKategorija() == category) {
                counter++;
            }
        }
        if (counter==0) {
            NoProductFoundException ex(category);
            throw ex;
            return *this;
        }

        else {
            temp.niza = new Product[counter];
            temp.n=counter;
            counter=0;

            for (int i=0;i<n;i++) {
                if (niza[i].getKategorija() == category) {
                    temp.niza[counter++]=niza[i];
                }
            }
            return temp;
        }

    }



};
void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`
       Product temp;
    ifstream in("input.txt");
    while (in>>temp) {
        s+=temp;
    }
    in.close();

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
      ofstream out("output1.txt");
    out<<s;
    out.close();
    ofstream out2("output2.txt");
   try{ Store temporary =s.fromCategory(category);out2<<temporary<<endl;}
    catch (NoProductFoundException ex) {
        ex.print();
    }


    out2.close();
    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}