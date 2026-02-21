#include <list>
#include <numbers>
using namespace std;
#include <iostream>
#include <cstring>
enum type{
    strucna,roman
};
class BookStore;
class Book{
    friend class BookStore;
    friend void best(BookStore *niza,int n);
char title[30];
   int seriski;
   static int bc;
    type tip;
    float cena;
    public:
    public:
    ~Book(){}
    Book(){};
    Book(char *t,int tipp,float c){
        strcpy(title,t);
        tip=(type)tipp;
        cena=c;
        seriski=bc++;
    }
    Book (const Book &n){
        strcpy(title,n.title);
        tip=n.tip;
        cena=n.cena;
    }
    char *getTitle(){
        return title;
    }
    int getSeriski(){
        return seriski;
    }
    float getCena(){
        return cena;
    }
    void setCena(float cenaa){
        cena=cenaa;
    }
    void setTitle(char *t){
        strcpy(title,t);
    }
    void print(){
        cout<<seriski<<"-"<<title<<"-"<<tip<<" "<<cena<<endl;
    }
    void increasePrice(float n){
        cena=cena+n;
    }

}
int Book::bc=777551;
class BookStore;
class BookStore{
    friend class Book;
    friend void best(BookStore *niza,int n);
    char name[20];
    Book niza[100];
    int broj;
    public:
    BookStore(){}
    BookStore(char *t) {
        strcpy(name,t);
    }
    ~BookStore(){}
    BookStore(char *na,Book *n,int b){
        strcpy(name,na);
        broj=b;
        for(int i=0;i<broj;i++){
            niza[i]=n[i];
        }
    }
    BookStore(BookStore &n){
        strcpy(name,n.name);
        broj=n.broj;
        for(int i=0;i<broj;i++){
            niza[i]=n[i];
        }
    }
   char *getName(){
       return name;
   }
   int getBroj(){
       return broj;
   }
   void setBroj(int b){
       broj=b;
   }
   void setName(char *n){
       strcpy(name,n);
   }
   void print(){
       cout<<name<<endl;
       for(int i=0;i<broj;i++){
           niza[i].print();
       }
   }
   void addBook(const Book& n){
      bool flag=true;
       for(int i=0;i<broj;i++){
           if(strcmp(niza[i].getTitle(),n.getTitle())==0){
               flag=false;
           }
       }
       if(flag){
           niza[broj++]=n;
       }
   }
   bool greaterThan(const BookStore &n){
       if(n.broj>broj){
          return true;
       }
       if(n.broj<broj){
           false;
       }
       else return false;
   }
   void createMarketPrice(){
       for(int i=0;i<broj;i++){
           if(niza[i].tip==0){
             niza[i].cena*=1.05;
           }
           else niza[i].cena*=1.03;
       }
   }

};
void best(BookStore *niza,int n){
    BookStore temp=niza[0];
    int min=0;
    int index=0;
    for(int i=0;i<n;i++){
        if(temp.greaterThan(niza[i])){
            temp=niza[i];
        }
    }
    temp.print();
}
int main() {
    int testCase;
    cin>>testCase;
    if(testCase==0)
    {
        cout<<"TESTING BOOK CONSTRUCTOR"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==1)
    {
        cout<<"TESTING BOOK print()"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        book1.print();
        book2.print();
        book3.print();
        cout<<"TEST PASSED"<<endl;
    } else if(testCase==2)
    {
        cout<<"TESTING BOOK increasePrice"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        book1.print();
        book2.print();
        book3.print();
        book1.increasePrice(200);
        book2.increasePrice(300);
        book3.increasePrice(150);
        cout<<"===== INCREASE ====="<<endl;
        book1.print();
        book2.print();
        book3.print();
        cout<<"TEST PASSED"<<endl;
    }
    else if(testCase==3)
    {
        cout<<"TESTING BOOKSTORE CONSTRUCTOR"<<endl;
        BookStore bookStore1("The Book Cellar");
        bookStore1.print();
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==4)
    {
        cout<<"TESTING BOOKSTORE addBook() and print()"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        bookStore1.print();
        cout<<"TEST PASSED"<<endl;
    }
    else if(testCase==5)
    {
        cout<<"TESTING BOOKSTORE OPERATOR addBook() and print()"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        Book book4("Object-oriented programming",0,2300);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        bookStore1.addBook(book4);
        bookStore1.print();
        cout<<"TEST PASSED"<<endl;
    }
    else if(testCase==6)
    {
        cout<<"TESTING BOOKSTORE COPY-CONSTRUCTOR"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        Book book4("Anna Karenina",1,1200);
        Book book5("Calculus 1",0,1320);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        BookStore bookStore2(bookStore1);

        bookStore1.print();
        bookStore2.print();
        cout<<"TEST PASSED"<<endl;

    }
    else if(testCase==7)
    {
        cout<<"TESTING BOOKSTORE greaterThan "<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        Book book4("Anna Karenina",1,1200);
        Book book5("Calculus 1",0,1320);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        BookStore bookStore3("Word Wizardry Books");
        bookStore3.addBook(book4);
        bookStore3.addBook(book5);
        if(bookStore1.greaterThan(bookStore3))
        {
            cout<<"TEST PASSED"<<endl;
        }
        else
        {
            cout<<"TEST FAILED"<<endl;
        }
    }else if(testCase==8)
    {
        cout<<"TESTING METHOD createMarketPrice()"<<endl;
        char name[30],name1[30];
        int type, numofBookStores, numberOfBooks;
        float price;
        cin>>numofBookStores;
        cin.ignore();
        BookStore bookStores[10];
        for(int i=0;i<numofBookStores;i++)
        {
            cin.getline(name,20);
            bookStores[i]=BookStore(name);
            cin>>numberOfBooks;
            cin.ignore();
            Book books[10]; //777561
            for(int j=0;j<numberOfBooks;j++)
            {
                cin >> name1 >> type >> price;
                cin.ignore();
                books[j]=Book(name1,type,price);
                bookStores[i].addBook(books[j]);
            }
        }
        for(int i=0;i<numofBookStores;i++)
        {
            bookStores[i].print();
            cout<<"CREATED MARKET PRICES"<<endl;
            bookStores[i].createMarketPrice();
            bookStores[i].print();
        }

    }else if(testCase==9)
    {
        cout<<"TESTING METHOD best()"<<endl;
        char name[30],name1[30];
        int type, numofBookStores, numberOfBooks;
        float price;
        cin>>numofBookStores;
        cin.ignore();
        BookStore bookStores[10];
        for(int i=0;i<numofBookStores;i++)
        {
            cin.getline(name,20);
            bookStores[i]=BookStore(name);
            cin>>numberOfBooks;
            cin.ignore();
            Book books[10];
            for(int j=0;j<numberOfBooks;j++)
            {
                cin >> name1 >> type >> price;
                cin.ignore();
                books[j]=Book(name1,type,price);
                bookStores[i].addBook(books[j]);
            }
        }
//        best(bookStores,numofBookStores).print();
    }
    return 0;
}