/*Да се дефинира класа Programmer во која ќе се чуваат информации за:
name (низа од максимум 100 карактери) - име на вработениот
programmingLanguage (низа од максимум 100 карактери) - омилен програмски јазик на вработениот
salary (цел број) - плата на вработениот
Сите променливи внатре во класата треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:
конструктор (без и со параметри)
деструктор
set методи
get методи
Да се дефинираат следните методи во класата:
display() која што ќе ги печати информациите за програмерот во следниот формат:
Name: …
Programming language: …
Salary: …
Надвор од класата:

printProgrammerWithHighestSalary(Programmer programmers, int n, charlang)
кој што ќе го најде програмерот со најголема плата, чиј што омилен програмски јазик
е оној кој што се предава како аргумент во функцијата.*/

#include <iostream>
#include <string.h>
using namespace std;

class Programmer {
private:
 char name[100];
 char programminglanguage[100];
 int salary;
 public:
 Programmer(char *namee="nema",char *languagee="nema",int salaryy=0) {
  strcpy(name,namee);
  strcpy(programminglanguage,languagee);
  salary=salaryy;
 }
 Programmer() {};
 ~Programmer() {};
  void set_name(char *namee) {
   strcpy(name,namee);
  }
 void set_programminglanguage(char *languagee) {
   strcpy(programminglanguage,languagee);
  }
 void set_salary(int salaryy) {
   salary=salaryy;
  }
 char *get_name() {
   return name;
  }
 char *get_programminglanguage() {
   return programminglanguage;
  }
 int get_salary() {
   return salary;
  }
 void display() {
   cout<<"Name :"<<name<<endl;
   cout<<"Programming language :"<<programminglanguage<<endl;
   cout<<"Salary :"<<salary<<endl;
  }
};

 void printProgrammerWithHighestSalary(Programmer *programmers, int n, char *charlang) {
 int max_salary=0;
 int index=-1;
 for(int i=0;i<n;i++) {
  if (strcmp(charlang,programmers[i].get_programminglanguage())==0) {
   if(programmers[i].get_salary()>max_salary) {
    max_salary=programmers[i].get_salary();
    index=i;
   }
  }
 }
 if(index != -1) programmers[index].display();
}