/* Да се дефинира основна класа DebitAccount (име, број, биланс).
Да се изведе класа CreditAccount која има лимит за повлекување во минус и камата.
Да се имплементира функција withdraw која овозможува влегување во минус
со пресметување на камата. */

#include <iostream>
#include <string>
using namespace std;

class DebitAccount {
protected:
    string name;
    long number;
    double balance;
    public:
    DebitAccount(string name, long number, double balance) {
        this->name = name;
        this->number = number;
        this->balance = balance;
    }
    DebitAccount(const DebitAccount &d) {
        this->name = d.name;
        this->number = d.number;
        this->balance = d.balance;
    }
    DebitAccount &operator=(const DebitAccount &d) {
        if (this!=&d) {
            this->name = d.name;
            this->number = d.number;
            this->balance = d.balance;
        }
        return *this;
    }
    DebitAccount() {
        this->name = "";
        this->number = 0;
        this->balance = 0;
    }
    void showInfo() {
        cout<<"Name: "<<name<<endl;
        cout<<"Number: "<<number<<endl;
        cout<<"Balance: "<<balance<<endl;
    }
    double getBalance() {
        return this->balance;
    }
    void deposit(double amount) {
        this->balance += amount;
    }
    void withdraw(double amount) {
        if (balance-amount>=0) {
            this->balance -= amount;
        }
        else {
            cout << "You can not withdraw more money than you have on your account.\n"
                 << "Please upgrade your debut account to credit account!"<<endl;
        }
    }
    ~DebitAccount(){};
};

class CreditAccount : public DebitAccount {
protected:
    double limit;
    double interest; // % percent
    double minus;
    public:
    CreditAccount(string name, long number,double balance, double limit): DebitAccount(name,number,balance) {
        this->limit = limit;
        interest = 0.05;
        minus = 0;
    }
    CreditAccount() {
        this->limit = 0;
        interest = 0.05;
        minus = 0;
    }
    void withdraw(double amount) {
        if (amount <= balance){
            DebitAccount::withdraw(amount);
        }
        else if (amount <= balance + limit - minus) {
            double advance = amount - balance;
            this->minus += advance * (1.0 + interest);

            cout<<"Minus: " << advance <<"\n"
                << "Minus with interest: " << advance*interest<<endl;

            deposit(advance);
            DebitAccount::withdraw(amount);
        } else {
            cout << "The bank is not giving you that much money..." << endl;
        }
    };
    void showInfo() {
        DebitAccount::showInfo();
        cout<<"\t Limit: "<<this->limit << "\n"
            <<"\t In minus: " << this->minus << "\n"
            <<"\t Interest: " << this->interest << "%\n";
    }
};

int main() {
    DebitAccount d("Pero Perovski", 6, 100000);
    CreditAccount ca("Mitko Mitkovski", 10, 5000, 1000);
    d.showInfo();
    d.deposit(50000);
    d.withdraw(600000);
    d.showInfo();
    ca.showInfo();
    ca.deposit(500);
    ca.showInfo();
    ca.withdraw(6200);
    ca.showInfo();
    return 0;
}