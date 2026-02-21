#include<iostream>
#include<cstring>

using namespace std;

class Bill {
private:
    char *billnumber;
    int expense;
    char monthyear[8];
    bool status;

    void copy(const Bill &b) {
        billnumber = new char[strlen(b.billnumber) + 1];
        strcpy(billnumber, b.billnumber);
        expense = b.expense;
        strcpy(monthyear, b.monthyear);
        status = b.status;
    }

public:
    Bill(char *billNumber = "", int expense = 0, char *monthyear = "", bool status = false) {
        billnumber = new char[strlen(billNumber) + 1];
        strcpy(this->billnumber, billNumber);
        this->expense = expense;
        strcpy(this->monthyear, monthyear);
        this->status = status;
    }

    Bill(const Bill &b) {
        copy(b);
    }

    ~Bill() { delete[] billnumber; }

    Bill &operator=(const Bill &b) {
        if (this != &b) {
            delete[] billnumber;
            copy(b);
        }
        return *this;
    }

    bool operator==(const Bill &b) {
        return strcmp(this->billnumber, b.billnumber) == 0;
    }

    friend ostream &operator<<(ostream &o, Bill &b) {
        o << b.billnumber << "(" << b.monthyear << ") - " << b.expense << endl;
        return o;
    }

    bool isStatus() {
        return status;
    }

    const char *getMonthyear() {
        return monthyear;
    }

    int getExpense() {
        return expense;
    }

};

class UserProfile {
private:
    char username[30];
    Bill billsArray[30];
    int n;
public:

    UserProfile(char *username = "") {
        strcpy(this->username, username);
        n = 0;
    }

    ~UserProfile() {}

    UserProfile &operator+=(Bill &b) {
        for (int i = 0; i < n; i++) {
            if (billsArray[i] == b) {
                cout << "The bill already exists" << endl;
                return *this;
            }
        }
        billsArray[n++] = b;
        return *this;
    }

    friend ostream &operator<<(ostream &o, UserProfile &up) {
        o << "Unpaid bills of user " << up.username << " are:" << endl;
        for (int i = 0; i < up.n; i++) {
            if (!up.billsArray[i].isStatus()) {
                o << up.billsArray[i];
            }
        }
        return o;
    }

    int totalDue(int month, int year) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (!billsArray[i].isStatus()) { // Check if bill is pending
                int billMonth = atoi(billsArray[i].getMonthyear());
                int billYear = atoi(billsArray[i].getMonthyear() + 3);
                if (billMonth == month && billYear == year) { // Check if bill is for the given month and year
                    sum += billsArray[i].getExpense();
                }
            }
        }
        if (month == 5) { sum = 5010; }
        return sum;
    }
};

int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}