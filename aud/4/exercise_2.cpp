/* Да се имплементираат класи за Книга (Book), Библиотека (Library) и Член на библиотека (LibraryMember).
Во класата Book се чуваат име, автор и достапност. Класата Library содржи низа од книги.
Да се дефинира пријателска функција checkOutBook која овозможува изнајмување на книга доколку
таа е достапна, при што нејзината состојба се менува во недостапна. */

#include <iostream>
#include <cstring>
using namespace std;

class LibraryMember;
class Library;

class Book {
private:
    friend void checkOutBook(const LibraryMember& clen,const Library& biblioteka,int pozicija);
    char name[20];
    char avtor[20];
    bool availability;
    friend Library;
    public:
    Book() {
    };
    ~Book(){};
    Book(char *ime,char *avtor,bool availability) {
        strcpy(this->name,ime);
        strcpy(this->avtor,avtor);
        this->availability = availability;
    }
    Book(const Book &b) {
        strcpy(this->name,b.name);
        strcpy(this->avtor,b.avtor);
        this->availability = b.availability;
    }
    void print() {
        cout<<"["<<name<<"] ["<<avtor<<"] dostapnost:"<<availability<<endl;
    }

};

class Library {
    friend class Book;
    friend void checkOutBook(const LibraryMember& clen,const Library& biblioteka,int pozicija);
    char name[20];
    Book books[30];
    int num;
    public:
    Library() {
        strcpy(this->name,"Braka Miladinovci");
        num = 0;
    };
    ~Library(){};
    Library(char *name,Book *books,int num) {
        strcpy(this->name,name);
        this->num = num;
        for (int i=0;i<num;i++) {
            this->books[i]=books[i];
        }

    }
    void print() {
        cout<<name<<endl;
        cout<<"["<<num<<"]";
        for (int i=0;i<num;i++) {
            books[i].print();
        }
    }
    void addBook(const Book &book) {
        if (num<30) {
            books[num++] = book;
        }
    }
};

class LibraryMember {
    char name[20];
    int id;
    public:
    LibraryMember() {}
    ~LibraryMember(){};
    LibraryMember(char *name,int id) {
        strcpy(this->name,name);
        this->id = id;
    }
};

void checkOutBook(const LibraryMember& clen,const Library& biblioteka,int pozicija) {
   if ( biblioteka.books[pozicija-1].availability) {
       cout<<"Knigata e dostapna"<<endl;
       //bitno
       const_cast<Library&>(biblioteka).books[pozicija-1].availability=0;
   }
    else {
        cout<<"Knigata ne e dostapna"<<endl;
    }
}

int main() {
    Library l1;
    int n;
    cout << "Enter the number of books" << endl;
    cin >> n;
    char name[30], author[30];
    bool availability;
    for (int i = 0; i < n; i++) {
        cin >> name >> author >> availability;
        Book b = Book(name, author, availability);
        l1.addBook(b);
    }
    l1.print();
    LibraryMember m1("marko", 9541);
    int index;
    cin >> index;
    checkOutBook(m1, l1, index);
    return 0;
};