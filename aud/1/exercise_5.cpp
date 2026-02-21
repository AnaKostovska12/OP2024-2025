#include <iostream>
#include <cstring>
using namespace std;

class X {
private: 
    int i;
public:
    X(int a) : i(a) { cout << "Constructor(" << i << ") called" << endl; }
    ~X() { cout << "Destructor for " << i << " called" << endl; }
    void show() const { cout << "Value: " << i << endl; }
};

int main() {
    X *x = new X(5);
    x->show();
    delete x;

    return 0;
}