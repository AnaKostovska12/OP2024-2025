using namespace std;
#include <iostream>
#include <cstring>
class Koncert {
protected:
    char naziv[21];
    char lokacija[21];
   static float sezonski_popust;
    float cena_bilet;
public:
    Koncert() {
        strcpy(naziv,"");
        strcpy(lokacija,"");

        cena_bilet=0;
    }
    Koncert(char *naziv,char *lokacija,float cena_bilet) {
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cena_bilet=cena_bilet;
    }
    Koncert(const Koncert &n) {
        strcpy(this->naziv,n.naziv);
        strcpy(this->lokacija,n.lokacija);
        this->cena_bilet=n.cena_bilet;
    }
    Koncert &operator=(const Koncert &n) {
        if (this!=&n) {
            strcpy(this->naziv,n.naziv);
            strcpy(this->lokacija,n.lokacija);
            this->cena_bilet=n.cena_bilet;
        }
        return *this;
    }
 virtual    float cena() {
        return cena_bilet*(1-sezonski_popust);
    }
    void setSezonskiPopust(float p) {
        sezonski_popust=p;
    }
    virtual void print() {
        cout<<naziv<<" "<<cena()<<endl;
    }
   virtual  char *getNaziv() {
        return naziv;
    }
virtual float getSezonskiPopust()  {
        return sezonski_popust;
    }
};
class ElektronskiKoncert: public Koncert {
    private:
    char *dj;
    float vremetraenje;
    bool dnevna;
    public:
    ElektronskiKoncert() {
        dj=nullptr;
        vremetraenje=0;
        dnevna=false;
    }
    ElektronskiKoncert(char *naziv,char *lokacija,float cena_bilet,char *dj,float vremetraenje,bool dnevna)
        :Koncert(naziv,lokacija,cena_bilet) {
        this->dnevna=dnevna;
        this->vremetraenje=vremetraenje;
        this->dj=new char [strlen(dj)+1];
        strcpy(this->dj,dj);
    }
    ElektronskiKoncert(const ElektronskiKoncert &n)  :Koncert(n){
        this->dnevna=n.dnevna;
        this->vremetraenje=n.vremetraenje;
        this->dj=new char [strlen(n.dj)+1];
        strcpy(this->dj,n.dj);
    }
    ElektronskiKoncert &operator=(const ElektronskiKoncert &n) {
        if (this!=&n) {
            Koncert::operator=(n);
            delete [] this->dj;
            this->dnevna=n.dnevna;
            this->vremetraenje=n.vremetraenje;
            this->dj=new char [strlen(n.dj)+1];
            strcpy(this->dj,n.dj);
        }
        return *this;
    }
   char *getNaziv() override{
        return naziv;
    }
    float getSezonskiPopust() override {
        return sezonski_popust;
    }
    float cena() override {
        float krajna;
        krajna=Koncert::cena();
        if (vremetraenje>7)
            krajna+=360;
      else  if (vremetraenje>5)
            krajna+=150;
      if (dnevna) {
          krajna-=50;
      }
        else {
            krajna+=100;
        }
        return krajna;

    }
     void print() override{
        cout<<naziv<<" "<<cena()<<endl;
    }

};
float Koncert::sezonski_popust=0.20;
void najskapKoncert(Koncert ** koncerti, int n) {
    float max_cena=0;
    int index=0;
    int counterE=0;
    for (int i=0;i<n;i++) {
        if (koncerti[i]->cena()>max_cena) {
            max_cena=koncerti[i]->cena();
            index=i;
        }
        ElektronskiKoncert *pointer1=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if (pointer1) counterE++;

    }
    cout<<"Najskap koncert: ";
    koncerti[index]->print();
    cout<<"Elektronski koncerti: "<<counterE;
    cout<<" od vkupno "<<n<<endl;
}
bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski) {
    bool flag=false;
    for (int i=0;i<n;i++) {
      bool ista=strcmp(koncerti[i]->getNaziv(),naziv);
        ElektronskiKoncert *point=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
       if (elektronski) {
           if (ista==0 && point) {
               cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
               return true;
               flag=true;
           }

       }
        else {
            if (ista==0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                return true;
                flag=true;
            }
        }
    }
    if (!flag) {
        return false;
    }

};
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}
