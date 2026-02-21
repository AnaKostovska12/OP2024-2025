/* Да се дефинира класа User со динамички низи за име и компанија.
Да се дефинира класа Group која содржи динамичка низа од User објекти.
Класата PrivateGroup го ограничува бројот на членови преку статички капацитет.
Методот rating() е виртуелен и различно се пресметува за обична и приватна група. */

#include <iostream>
#include <cstring>
using namespace std;

class User {
    char *username;
    char *companyName;
    int position;

    void copy(const User &u) {
        this->username = new char[strlen(u.username) + 1];
        strcpy(this->username, u.username);
        this->companyName = new char[strlen(u.companyName) + 1];
        strcpy(this->companyName, u.companyName);
        this->position = u.position;
    }

public:
    User() {
        username=nullptr;
        companyName=nullptr;
        position=0;
    }
    User(char *username , char *companyName, int position) {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
        this->companyName = new char[strlen(companyName) + 1];
        strcpy(this->companyName, companyName);
        this->position = position;
    }

    User(const User &u) {
        copy(u);
    }

    User &operator=(const User &u) {
        if (this != &u) {
            delete[] username;
            delete[] companyName;
            copy(u);
        }
        return *this;
    }

    ~User() {
        delete[] username;
        delete[] companyName;
    }

    char *getUsername() const { return username; }
    int getPosition() const { return position; }

    friend ostream &operator<<(ostream &os, const User &user) {
        return os << "Username: " << user.username
                  << " Company name: " << user.companyName
                  << " Position: " << user.position;
    }

    friend istream &operator>>(istream &in, User &user) {
        char tempU[50], tempC[50];
        int pos;
        in >> tempU >> tempC >> pos;
        user.username = new char[strlen(tempU)+1];
        strcpy(user.username, tempU);
        user.companyName = new char[strlen(tempC)+1];
        strcpy(user.companyName, tempC);
        user.position = pos;
        return in;
    }

    bool operator==(User &u) {
        return strcmp(this->username,u.username)==0;
    }
};

class Group {
protected:
    User *clenovi;
    int n;
    string name;
    public:
    Group(string name) {
        this->name = name;
        this->clenovi = nullptr;
        n=0;
    }
    Group() {
        this->clenovi = nullptr;
        this->n=0;
        name="";
    }
    Group(const Group &n) {
        this->n=n.n;
        this->name=n.name;
        clenovi=new User[n.n];
        for (int i=0;i<n.n;i++) {
            this->clenovi[i]=n.clenovi[i];
        }
    }
    Group &operator=(const Group &n) {
        if (this != &n) {
            delete[] this->clenovi;
            this->n=n.n;
            this->name=n.name;
            clenovi=new User[n.n];
            for (int i=0;i<n.n;i++) {
                this->clenovi[i]=n.clenovi[i];
            }
        }
        return *this;
    }
    virtual ~Group() {
        delete[] this->clenovi;
    }
   virtual void addMember(User &user) {
        for (int i=0;i<n;i++) {
            if (this->clenovi[i]==user) {
                return;
            }
        }
        User *temp=new User[n+1];
        for (int i=0;i<n;i++) {
            temp[i]=this->clenovi[i];
        }
        delete [] this->clenovi;
        temp[n++]=user;
        this->clenovi=temp;
    }
    double average_position() const {
        if(n==0) return 0;
        double zbir=0;
        for (int i=0;i<n;i++) {
            zbir+=this->clenovi[i].getPosition();
        }
        return zbir/(n*1.0);
    }
     virtual double rating() const  {
        return (10-average_position())*n/100.0;
    }
    friend ostream &operator<<(ostream &out, const Group &g) {
        out << "Group: " << g.name << endl;
        out << "Members: " << g.n << endl;
        out << "Rating: " << g.rating() << endl;
        out << "Members list: " << endl;
        if (g.n == 0) {
            out << "EMPTY" << endl;
        } else {
            for (int i = 0; i < g.n; i++) {
                out << i + 1 << ". " << g.clenovi[i] << endl;
            }
        }
        return out;
    }
};

class PrivateGroup : public Group {
private:
    static int capacity;
    const static float coeficient;

    public:
    PrivateGroup(string name):Group(name) {}
    PrivateGroup(const PrivateGroup &n) :Group(n){}

    PrivateGroup &operator=(const PrivateGroup &n) {
        if (this != &n) {
            Group::operator=(n);
        }
        return *this;
    }
    void addMember(User &user) override {
        if (n < capacity) {
            Group::addMember(user);
        };
    }
    double rating() const override {
        return (10-average_position())*( (double)n/capacity ) * coeficient;
    }
    static void setCapacity(int cap) {
        capacity=cap;
    }
    friend ostream &operator<<(ostream &out, const PrivateGroup &g){
        out << "Private ";
        const Group &group = g;
        out << group;
        return out;
    }
};

int PrivateGroup::capacity = 10;
const float PrivateGroup::coeficient = 0.8f;

int main() {
    cout << "INTEGRATION TEST" << endl;
    char name[50];
    int nGroups;
    cin >> nGroups;
    Group **groups = new Group *[nGroups];
    for (int i = 0; i < nGroups; i++) {
        int type;
        cin >> type;
        cin >> name;
        if (type == 1) {
            groups[i] = new Group(name);
        } else {
            groups[i] = new PrivateGroup(name);
        }
        int nUsers;
        cin >> nUsers;
        for (int j = 0; j < nUsers; j++) {
            User u;
            cin >> u;
            groups[i]->addMember(u);
        }
    }

    cout << "BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }
    PrivateGroup::setCapacity(15);
    cout << "AFTER CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }

    for (int i = 0; i < nGroups; ++i) delete groups[i];
    delete[] groups;

    return 0;
}