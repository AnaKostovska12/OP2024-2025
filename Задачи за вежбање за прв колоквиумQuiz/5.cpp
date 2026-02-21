using namespace std;
#include <iostream>
#include <cstring>
class Gitara {
    char seriski[25];
    float nabavna;
    int godina;
    char tip[40];
    public:
    ~Gitara() {}
    Gitara() {}
    Gitara(char *t,char *s,int g,float n) {
        strcpy(seriski,s);
        nabavna=n;
        godina=g;
        strcpy(tip,t);
    }
    bool daliIsti( Gitara r) {
        if (strcmp(seriski,r.seriski)==0) {
            return true;
        }
        else return false;
    }
    char *getTip() {
        return tip;
    }
    void pecati() {
        cout<<seriski<<" "<<tip<<" "<<nabavna<<endl;
    }
    float getNabavna() {
        return nabavna;
    }
    char *getSeriski() {
        return seriski;
    }
    int getGodina() {
        return godina;
    }
};
class Magacin {
    char ime[20];
    char lokacija[60];
    Gitara poseduvame[60];
    int broj;
    int godina_otvaranje;
    public:
    ~Magacin() {}
    Magacin() {}
    Magacin(char *namee,char *lok) {
        strcpy(ime,namee);
        strcpy(lokacija,lok);


    }
    Magacin(char *namee,char *lok,int godina) {
        strcpy(ime,namee);
        strcpy(lokacija,lok);
        godina_otvaranje=godina;

    }
    double vrednost() {
        double zbir=0;
        for (int i=0;i<broj;i++) {
            zbir+=poseduvame[i].getNabavna();
        }
        return zbir;
    }
    void dodadi(Gitara d) {
        poseduvame[broj++]=d;
    }
    void prodadi(Gitara d) {
        for (int i=0;i<broj;i++) {
            if (strcmp(poseduvame[i].getSeriski(),d.getSeriski())==0) {
                for (int j=i;j<broj-1;j++) {
                    poseduvame[j]=poseduvame[j+1];
                }broj--;
            }
        }

    }
    void pecati(bool daliNovi) {
        if (daliNovi) {
            cout<<ime<<" "<<lokacija<<endl;
            for (int i=0;i<broj;i++) {
                if (poseduvame[i].getGodina()>godina_otvaranje) {
                    poseduvame[i].pecati();
                }
            }
        }
     else {
         cout<<ime<<" "<<lokacija<<endl;
            for (int i=0;i<broj;i++) {
                poseduvame[i].pecati();
            }
        }
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, godina;
	float cena;
	char seriski[50],tip[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
		cout<<g.getTip()<<endl;
		cout<<g.getSeriski()<<endl;
		cout<<g.getGodina()<<endl;
		cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
		Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
		cin>>n;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;
                Gitara g(tip,seriski, godina,cena);
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
   else if(testCase ==6)
        {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
				kb.dodadi(g);
			}
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
        }
    return 0;
}