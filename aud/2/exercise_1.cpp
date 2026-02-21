/* Дефинирајте класа Cuboid во која се чуваат димензиите на кубоид (а, b, c).
Да се имплементираат методи за пресметување на плоштина и волумен,
како и конструктори и деструктор. */

#include <iostream>
using namespace std;

class Cuboid {
private:
    int a, b, c;
public:
    // Default constructor
    Cuboid(){
        cout << "Default constructor" << endl;
    }
    // Constructor with arguments
    Cuboid(int aa, int bb, int cc) {
        a = aa;
        b = bb;
        c = cc;
        cout << "Constructor" << endl;
    }
    ~Cuboid() {        cout << "Destructor" << endl; }
    // Method for computing area
    int area() {
        return 2 * (a * b + a * c + b * c);
    }
    // Method for computing volume
    int volume() {
        return a * b * c;
    }
};

int main(){
    Cuboid kocka(1,2,3);
    cout<<kocka.area();
}