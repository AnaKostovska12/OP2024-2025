#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;
class InvalidCodeFormatException {
private:
    string code;
public:
    InvalidCodeFormatException() {
        code=" ";

    }
    InvalidCodeFormatException(string code) {
        this->code=code;
    }
    void print() {
        cout<<"The code "<<code<<" is invalid doctor code format.";
        cout<<" THE CODE MUST BE 8 CHARACTERS LONG AND CANNOT CONTAIN COMMA."<<endl;
    }
};

class Doctor {
protected:
    string name;
    string surname;
    float plata;
    string code;
public:
    Doctor() {
        name="";
        surname="";
        plata=0;
        code="";
    };
    Doctor(string name,string surname,string code) {
        this->name=name;
        this->surname=surname;

        this->code=code;
        if (code.length()!=8) {
            InvalidCodeFormatException ex(code);
            throw ex;
        }
        for (int i=0;i<code.length();i++) {
            if (code[i]==',') {
                InvalidCodeFormatException ex(code);
                throw ex;
            }
        }
    }
    virtual ~Doctor(){};
    Doctor(const Doctor &n) {
        this->name=n.name;
        this->surname=n.surname;
        this->plata=n.plata;
        this->code=n.code;
    }
    Doctor &operator=(const Doctor &n) {
        if (this!=&n) {
            this->name=n.name;
            this->surname=n.surname;
            this->plata=n.plata;
            this->code=n.code;
        }
        return *this;
    }
    virtual float calculateSalary()=0;
    // virtual void print() {
    //     cout<<name<<endl;
    // };
    virtual void print()=0;
    friend ostream &operator<<(ostream &out,const Doctor &n) {
        out<<n.name<<endl;
        return out;
    }
};

class GeneralDoctor:public Doctor {
private:
    int brPacienti;
public:
    GeneralDoctor() {
        brPacienti=0;
    }
    GeneralDoctor(string name,string surname,string code,int brPacienti)
        :Doctor(name,surname,code) {
        this->brPacienti   = brPacienti;
        plata=45000;
    }
    GeneralDoctor(const GeneralDoctor &n)
        :Doctor(n) {
        this->brPacienti=n.brPacienti;
    }
    GeneralDoctor &operator=(const GeneralDoctor &n) {
        if (this!=&n) {
            Doctor::operator=(n);
            this->brPacienti=n.brPacienti;
        }
        return *this;
    }
    float calculateSalary() override {
        float krajna=45000;
        krajna+=((brPacienti/10)*3000);
        // return krajna+(krajna*0.07);
        return krajna*0.93;
    }
    void print()override {
        cout<<"General Doctor: "<<name<<" "<<surname<<" ";
        cout<<"CODE:"<<code;

        cout<<" Salary: "<<calculateSalary()<<endl;
    }
};
class Specialist:public Doctor {
private:
    string specijalnost;
    int brIntervencii;
    int godiniIskustvo;
public:
    Specialist() {
        specijalnost="";
        brIntervencii=0;
        godiniIskustvo=0;
    }
    Specialist(string name,string surname,string code,string specijalnost
        ,int brIntervencii,int godiniIskustvo)
            :Doctor(name,surname,code) {
        this->specijalnost=specijalnost;
        this->brIntervencii=brIntervencii;
        this->godiniIskustvo=godiniIskustvo;
        this->plata=550000;
    }
    Specialist(const Specialist &n):Doctor(n) {
        this->specijalnost=n.specijalnost;
        this->brIntervencii=n.brIntervencii;
        this->godiniIskustvo=n.godiniIskustvo;
    }
    Specialist &operator=(const Specialist &n) {
        if (this!=&n) {
            Doctor::operator=(n);
            this->specijalnost=n.specijalnost;
            this->brIntervencii=n.brIntervencii;
            this->godiniIskustvo=n.godiniIskustvo;
        }
        return *this;
    }
    float calculateSalary() override {
      float krajna=55000;
        krajna+=(brIntervencii*85);
        krajna+=((55000*0.05)*godiniIskustvo);
        // return krajna+(krajna*0.07);
        return krajna*0.93;
    }
    void print()override {
        cout<<"Specialist: "<<name<<" "<<surname<<" ";
        cout<<"CODE:"<<code<<" "<<specijalnost<<" ";
        cout<<"Salary: "<<calculateSalary()<<endl;
    }
};
void findDoctorsPercentage(Doctor **doctors, int n) {
    int counterS=0;
    int counterG=0;
    for (int i=0;i<n;i++) {
        GeneralDoctor *temp1=dynamic_cast<GeneralDoctor*>(doctors[i]);
        if (temp1) {
            counterG++;
        }
        Specialist *temp2=dynamic_cast<Specialist*>(doctors[i]);
        if (temp2) {
            counterS++;
        }
    }
    float percentS = (counterS * 100.0) / n;
    float percentG = (counterG * 100.0) / n;
    cout<<percentS<<"% of the doctors are specialists and ";
    cout<<percentG<< "% are general doctors."<<endl;
}
int main()
{
    int testCase, n;
    string name, surname, specialty, code;
    int numberOfPatients, yearsOfExperience, numberOfInterventions;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "TESTING GENERAL DOCTOR CLASS" << endl;

             Doctor *d = new GeneralDoctor("John", "Smith", "236XY@2B", 120);
             Doctor *d1 = new GeneralDoctor("Marco", "Brown", "345X!Y2B", 120);
             Doctor *d2 = new GeneralDoctor("Emily", "Johnson", "ABCD123@", 230);
             d->print();
             d1->print();
             d2->print();

             cout << "GENERAL DOCTOR CLASS OK!" << endl;

    }
    else if (testCase == 2)
    {
        cout << "TESTING SPECIALIST DOCTOR CLASS" << endl;
        Doctor *d = new Specialist("Beth", "Davis", "96Tr$$33", "Cardiologist", 45, 5);
        Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
        Doctor *d2 = new Specialist("Micheal", "Rosen", "7896YZ$s", "Radiologist", 41, 10);
        d->print();
        d1->print();
        d2->print();
        cout << "SPECIALIST DOCTOR CLASS OK!" << endl;

    }
    else if (testCase == 3)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new GeneralDoctor("John", "Smith", "23Y@2B", 120);
            d->print();


        }
        catch (InvalidCodeFormatException ex) {
            ex.print();
        }   cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 4)
    {
        try {
            cout << "TESTING EXCEPTION HANDLING" << endl;
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();

        }
        catch (InvalidCodeFormatException ex) {
            ex.print();
        }cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 5)
    {   try {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
        d->print();
    } catch (InvalidCodeFormatException ex) {
        ex.print();
    }
      try{  Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
        d1->print();}
          catch (InvalidCodeFormatException ex) {
            ex.print();
        }
     try{Doctor *d2 = new Specialist("Beth", "Davis", "96Tr,", "Cardiologist", 45, 5);
        d2->print();}

        catch (InvalidCodeFormatException ex) {
            ex.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else
    {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION!" << endl;
        cin >> n;
        Doctor **doctors = new Doctor *[n];
        for (int i = 0; i < n; i++)
        {
            int t;
            cin >> t;
            cin >> name >> surname;
            cin >> code;
            if (t == 1) // General doctor
            {
                cin >> numberOfPatients;
                     try {
                         doctors[i] = new GeneralDoctor(name, surname, code, numberOfPatients);
                     }
                catch (InvalidCodeFormatException ex) {
                    ex.print();
                    i--;
                    n--;
                }

            }
            else // Specialist
            {
                cin >> specialty;
                cin >> numberOfInterventions >> yearsOfExperience;

                  // doctors[i] = new Specialist(name, surname, code, specialty, numberOfInterventions, yearsOfExperience);
                try {
                    doctors[i] = new Specialist(name, surname, code, specialty, numberOfInterventions, yearsOfExperience);
                }
                catch (InvalidCodeFormatException ex) {
                    ex.print();
                    i--;
                    n--;
                }
            }
        }
        cout << "LIST OF ALL DOCTORS: " << endl;
        for (int i = 0; i < n; i++)
        {
            doctors[i]->print();
        }
        findDoctorsPercentage(doctors, n);
        for (int i = 0; i < n; i++)
        {
            delete doctors[i];
        }
        delete[] doctors;
    }
    return 0;
}
