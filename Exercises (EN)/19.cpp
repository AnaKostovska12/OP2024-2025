#include <iostream>
#include <cstring>
using namespace std;

class Parcel {
protected:
    int id;
    static int price;
public:
    Parcel(int id, int price) {
        this->id = id;
        Parcel::price = price;
    }

    Parcel(int id) {
        this->id = id;
    }

    Parcel() {
        this->id = 0;
    }

    Parcel(const Parcel &parcel) {
        this->id = parcel.id;
    }

    Parcel &operator=(const Parcel &parcel) {
        if (this != &parcel) {
            this->id = parcel.id;
        }
        return *this;
    }

    virtual int getId() const {
        return id;
    }

    static void setProcessingPrice(int p) {
        Parcel::price = p;
    }

    static int getProcessingPrice() {
        return price;
    }
};

int Parcel::price = 150;

class Envelope : public Parcel {
private:
    int width;
    int height;
    char receiver[51];
public:
    Envelope() : Parcel() {
        width = height = 0;
        strcpy(receiver, "");
    }

    Envelope(int id, const char *receiver, int width, int height)
        : Parcel(id) {
        this->width = width;
        this->height = height;
        strncpy(this->receiver, receiver, 50);
        this->receiver[50] = '\0';
    }

    Envelope(const Envelope &e) : Parcel(e) {
        width = e.width;
        height = e.height;
        strcpy(receiver, e.receiver);
    }

    Envelope &operator=(const Envelope &e) {
        if (this != &e) {
            Parcel::operator=(e);
            width = e.width;
            height = e.height;
            strcpy(receiver, e.receiver);
        }
        return *this;
    }

    int getId() const override {
    return id;
}

const char *getReceiver() const {
    return receiver;
}

int price() const {
    return Parcel::getProcessingPrice() + (width * height * 0.3);
}
};

class PostOffice {
private:
    Envelope envelopes[100];
    int n;
public:
    PostOffice() {
        n = 0;
    }

    PostOffice(const PostOffice &other) {
        n = other.n;
        for (int i = 0; i < n; ++i) {
            envelopes[i] = other.envelopes[i];
        }
    }

    PostOffice &operator=(const PostOffice &other) {
        if (this != &other) {
            n = other.n;
            for (int i = 0; i < n; ++i) {
                envelopes[i] = other.envelopes[i];
            }
        }
        return *this;
    }

    int sendEnvelope(int id, const char *receiver, int width, int height) {
        Envelope e(id, receiver, width, height);
        envelopes[n++] = e;
        return static_cast<int>(e.price());
    }

    void printEnvelopsTo( char *receiver) const {
        cout << "For " << receiver << " are envelops with ids: ";
        for (int i = 0; i < n; ++i) {
            if (strcmp(envelopes[i].getReceiver(), receiver) == 0) {
                cout << envelopes[i].getId() << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    int type, n, price, id, height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> type;
        if (type == 1) {
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) {
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) {
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) {
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId()
                 << " To: " << p2.getReceiver()
                 << " is: " << p2.price() << endl;
        }
    }
    return 0;
}

