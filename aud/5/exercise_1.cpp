/* Да се дефинира класа Array за работа со динамички алоцирана низа од цели броеви.
Класaта треба да поддржува:
- Динамичка алокација и реалокација на меморија (зголемување на капацитетот).
- Преоптоварување на операторот += за додавање елемент во низата.
- Преоптоварување на операторот -= за бришење на сите појавувања на одреден број.
- Преоптоварување на операторот [] за пристап до елемент.
- Преоптоварување на операторите ==, << и >>.
- Соодветен деструктор за ослободување на зафатената меморија. */

#include <iostream>
#include <cstring>
using namespace std;

class Array{
private:
    int *arr;
    char *name;
    int size;
    int capacity;

public:
    Array(){
      size = 0;
    }
    Array(char *name,int capacity=10){
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
      this->capacity = capacity;
      size=0;
    }
    Array &operator+=(int number){
      if(size!=capacity){
        arr[size++] = number;
      }
      else{
        int *temp= new int[capacity*2];
        for(int i=0;i<size;i++){
          temp[i]=arr[i];
        }
        capacity*=2;
        temp[size++]=number;
        delete [] arr;
        arr = temp;
        }
        return *this;
    }
  Array &operator-=(int number) {
    int newSize=0;
    int *temp=new int[capacity];
    for(int i=0;i<size;i++) {
      if(arr[i]!=number) {
        temp[newSize]=arr[i];
        newSize++;
      }
    }
      delete [] arr;
      arr=temp;
      size=newSize;
      return *this;
  }
  int operator[](int index) {
    if (index>=0 && index<size) {
      return arr[index];
    }
    else {
      cout<<"Nadvor od opseg"<<endl;
      return -1;
    }
  }
    bool operator==(Array &other){
      if(this!=&other){
        if(size==other.size && capacity==other.capacity){
          for(int i=0;i<size;i++){
            if(arr[i]!=other.arr[i]){ return false; }
          }
          return true;
        }
      }
      return false;
    }
    friend ostream &operator<<(ostream &os, Array &arr){
      os<<arr.name<<endl;
      os<<arr.capacity<<endl;
      os<<arr.size<<endl;
      for(int i=0;i<arr.size;i++){
        os<<arr.arr[i]<<endl;
      }
      return os;
    }
    friend istream &operator>>(istream &is, Array &arr){
      is>>arr.name;
      is>>arr.capacity;
      is>>arr.size;
      for(int i=0;i<arr.size;i++){
        is>>arr.arr[i];
      }
      return is;
    };
   ~Array() {
      delete [] arr;
      delete [] name;
    }
};

int main() {

    Array a;
    a += (6);
    a += (4);
    a += (3);
    a += (2);
    a += (1);


    Array b(a);
    b -= (2);
    b -= (3);


    cout << " a: " << a;
    cout << " b: " << b;

    if (a == b) cout << "Isti se";
    else cout << "Ne se isti";


    return 0;
}