#include <iostream>
#include <cstring>
using namespace std;

class Book {
protected:
    char isbn[21];
    char naslov[51];
    char avtor[21];
    float price;

public:
    Book() {
        strcpy(isbn, " ");
        strcpy(naslov, " ");
        strcpy(avtor, " ");
        price = 0;
    }

    Book(char *isbn, char *naslov, char *avtor, float price) {
        strcpy(this->isbn, isbn);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->price = price;
    }

    Book(const Book &n) {
        strcpy(this->isbn, n.isbn);
        strcpy(this->naslov, n.naslov);
        strcpy(this->avtor, n.avtor);
        this->price = n.price;
    }

    Book &operator=(const Book &n) {
        if (this != &n) {
            strcpy(this->isbn, n.isbn);
            strcpy(this->naslov, n.naslov);
            strcpy(this->avtor, n.avtor);
            this->price = n.price;
        }
        return *this;
    }

    bool operator>(Book &n) {
        return this->bookPrice() > n.bookPrice();
    }

    virtual ~Book() {}

    virtual float bookPrice() const = 0;

    friend ostream &operator<<(ostream &os, const Book &n) {
        n.print();
        return os;
    }

    virtual void print() const {
        cout << isbn << ": " << naslov << ", " << avtor << " " << bookPrice() << endl;
    }

    void setISBN(char *isbn) {
        strcpy(this->isbn, isbn);
    }
};

class OnlineBook : public Book {
private:
    char *url;
    int MB;

public:
    OnlineBook() {
        url = nullptr;
        MB = 0;
    }

    OnlineBook(char *isbn, char *naslov, char *avtor, float price, char *url, int MB)
        : Book(isbn, naslov, avtor, price) {
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
        this->MB = MB;
    }

    ~OnlineBook() {
        delete[] url;
    }

    OnlineBook(const OnlineBook &n) : Book(n) {
        this->url = new char[strlen(n.url) + 1];
        strcpy(this->url, n.url);
        this->MB = n.MB;
    }

    OnlineBook &operator=(const OnlineBook &n) {
        if (this != &n) {
            Book::operator=(n);
            delete[] url;
            this->url = new char[strlen(n.url) + 1];
            strcpy(this->url, n.url);
            this->MB = n.MB;
        }
        return *this;
    }

    float bookPrice() const override {
        if (MB > 20)
            return price * 1.2;
        else
            return price;
    }

    void print() const override {
        cout << isbn << ": " << naslov << ", " << avtor << " " << bookPrice() << endl;
    }
};

class PrintBook : public Book {
private:
    float tezhina;
    bool zaliha;

public:
    PrintBook() {
        tezhina = 0;
        zaliha = 0;
    }

    PrintBook(char *isbn, char *naslov, char *avtor, float price, float tezhina, bool zaliha)
        : Book(isbn, naslov, avtor, price) {
        this->tezhina = tezhina;
        this->zaliha = zaliha;
    }

    PrintBook(const PrintBook &n) : Book(n) {
        this->tezhina = n.tezhina;
        this->zaliha = n.zaliha;
    }

    PrintBook &operator=(const PrintBook &n) {
        if (this != &n) {
            Book::operator=(n);
            this->tezhina = n.tezhina;
            this->zaliha = n.zaliha;
        }
        return *this;
    }

    float bookPrice() const override {
        if (tezhina > 0.7)
            return price * 1.15;
        else
            return price;
    }

    void print() const override {
        cout << isbn << ": " << naslov << ", " << avtor << " " << bookPrice() << endl;
    }
};

void mostExpensiveBook(Book **books, int n) {
    float maxPrice = 0;
    int index = 0;
    int counterOnlineBooks = 0;
    int counterPrintBooks = 0;

    for (int i = 0; i < n; i++) {
        float currPrice = books[i]->bookPrice();
        if (currPrice > maxPrice) {
            maxPrice = currPrice;
            index = i;
        }

        if (dynamic_cast<OnlineBook *>(books[i]))
            counterOnlineBooks++;
        if (dynamic_cast<PrintBook *>(books[i]))
            counterPrintBooks++;
    }

    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << counterOnlineBooks << endl;
    cout << "Total number of print books: " << counterPrintBooks << endl;
    cout << "The most expensive book is: " << endl;
    books[index]->print();

}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}