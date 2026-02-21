using namespace std;
#include <iostream>
#include <cstring>
class Museum {
protected:
    string name;
    string grad;
    float bilet;
    int casovi;
public:
    int getCasovi() {
        return casovi;
    }
    Museum() {
        name="";
        grad="";
        bilet=0;
        casovi=0;
    }
    Museum(string name,string grad,float bilet,int casovi) {
        this->name=name;
        this->grad=grad;
        this->bilet=bilet;
        this->casovi=casovi;
    }
    Museum(const Museum &m) {
        name=m.name;
        grad=m.grad;
        bilet=m.bilet;
        casovi=m.casovi;
    }
    Museum &operator=(const Museum &m) {
        if (this!=&m) {
            name=m.name;
            grad=m.grad;
            bilet=m.bilet;
            casovi=m.casovi;
        }
        return *this;
    }
    virtual void printDetails()=0;
    virtual double calculateTicketCost()=0;
};
class ScientificMuseum : public Museum {
private:
    bool interakcija;
    int multimedijalni;
public:
    ScientificMuseum() {
        interakcija=0;
        multimedijalni=0;
    }
    ScientificMuseum(string name,string grad,float bilet,int casovi,bool interakcija,int multimedijalni)
        : Museum(name,grad,bilet,casovi) {
        this->interakcija=interakcija;
        this->multimedijalni=multimedijalni;
    }
    ScientificMuseum(const ScientificMuseum &m) : Museum(m) {
        interakcija=m.interakcija;
        multimedijalni=m.multimedijalni;
    };
    double calculateTicketCost()override {
        double krajna=bilet;
        if (interakcija) krajna*=1.12;
        return krajna+ (multimedijalni*6);
    };
    void printDetails()override {
        cout<<name<<" - (Scientific) "<<grad<<" "<<multimedijalni<<" "<<calculateTicketCost()<<endl;
    }
};
class ArtMuseum : public Museum {
    private:
    bool amateri;
    int originalni;
    public:
    ArtMuseum() {
        originalni=0;
        amateri=0;
    }
    ArtMuseum(string name,string grad,float bilet,int casovi,bool amateri,int originalni)
        : Museum(name,grad,bilet,casovi) {
        this->originalni=originalni;
        this->amateri=amateri;
    };
    ArtMuseum(const ArtMuseum &m) : Museum(m) {
        originalni=m.originalni;
        amateri=m.amateri;
    }
    double calculateTicketCost()override {
        double krajna=bilet;
        if (amateri)
            krajna*=0.82;
        return krajna+ (originalni*3);

    }
    void printDetails()override {
        cout<<name<<" - (Art) "<<grad<<" "<<amateri<<" "<<calculateTicketCost()<<endl;
    }

};
int findCheapestScientificMuseum(Museum **m, int n) {
    double max=999999;
    int index=-1;
    for (int i=0;i<n;i++) {
        ScientificMuseum *point=dynamic_cast<ScientificMuseum *>(m[i]);
        if (point!=NULL) {
            if (max>m[i]->calculateTicketCost() || (max==m[i]->calculateTicketCost()&&m[i]->getCasovi()>m[index]->getCasovi())) {
                max=point->calculateTicketCost();
                index=i;
            }
        }
    }
    return index;

}


int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetails();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetails();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
