#include <iostream>
#include <cstring>
using namespace std;

class SMS {
protected:
    char tel[20];
    float osnovna;

public:
    SMS(const char *tel = "", float osnovna = 0.0) {
        strcpy(this->tel, tel);
        this->osnovna = osnovna;
    }

    virtual ~SMS() {}

    virtual float SMS_cena() const = 0;

    friend ostream& operator<<(ostream &out, const SMS &s) {
        out << "Tel: " << s.tel << " - cena: " << s.SMS_cena() << "den."<<endl;
        return out;
    }
};

class RegularSMS : public SMS {
private:
    char *msg;
    bool roaming;
    static float rProcent;

public:
    RegularSMS(const char *tel = "", float osnovna = 0.0, const char *msg = "", bool roaming = false)
        : SMS(tel, osnovna) {
        this->msg = new char[strlen(msg) + 1];
        strcpy(this->msg, msg);
        this->roaming = roaming;
    }

    RegularSMS(const RegularSMS &r) : SMS(r.tel, r.osnovna) {
        this->msg = new char[strlen(r.msg) + 1];
        strcpy(this->msg, r.msg);
        this->roaming = r.roaming;
    }

    RegularSMS &operator=(const RegularSMS &r) {
        if (this != &r) {
            delete[] msg;
            strcpy(this->tel, r.tel);
            this->osnovna = r.osnovna;
            this->msg = new char[strlen(r.msg) + 1];
            strcpy(this->msg, r.msg);
            this->roaming = r.roaming;
        }
        return *this;
    }

    ~RegularSMS() {
        delete[] msg;
    }

    static void set_rProcent(float p) {
        rProcent = p;
    }

    float SMS_cena() const override {
        int broj_poraki =  (strlen(msg) / 160) + 1;
        if (roaming) {
            return osnovna * rProcent / 100.0 * broj_poraki+5;

        } else {
            return osnovna * 1.18 * broj_poraki;
        }
    }

    friend ostream& operator<<(ostream &out, const RegularSMS &s) {
	out << "Tel: " << s.tel << " - cena: " << s.SMS_cena() << "den."<<endl;
    	return out;
    }
};

float RegularSMS::rProcent = 300.0;

class SpecialSMS : public SMS {
private:
    bool humanitarna;
    static float sProcent;

public:
    SpecialSMS(const char *tel = "", float osnovna = 0.0, bool humanitarna = false)
        : SMS(tel, osnovna), humanitarna(humanitarna) {

    }

    static void set_sProcent(float p) {
        sProcent = p;
    }

    float SMS_cena() const override {
        if (humanitarna)
            return osnovna;
        else
            return osnovna * (1 + sProcent / 100.0);
    }

    friend ostream& operator<<(ostream &out, const SpecialSMS &s) {
    	out << "Tel: " << s.tel << " - cena: " << s.SMS_cena() << "den."<<endl;
    	return out;
    }
};

float SpecialSMS::sProcent = 150.0;

void vkupno_SMS(SMS **poraki, int n) {
    int regCount = 0, specCount = 0;
    float regCena = 0, specCena = 0;

    for (int i = 0; i < n; ++i) {
        RegularSMS *r = dynamic_cast<RegularSMS*>(poraki[i]);
        SpecialSMS *s = dynamic_cast<SpecialSMS*>(poraki[i]);
        if (r != nullptr) {
            regCount++;
            regCena += r->SMS_cena();
        } else if (s != nullptr) {
            specCount++;
            specCena += s->SMS_cena();
        }
    }
    cout << "Vkupno ima " << regCount << " regularni SMS poraki i nivnata cena e: " << regCena << endl;
    cout << "Vkupno ima " << specCount << " specijalni SMS poraki i nivnata cena e: " << specCena << endl;
}
int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}
	return 0;
}