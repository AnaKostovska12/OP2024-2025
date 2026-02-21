using namespace std;
#include <iostream>
#include <cstring>
enum tip {
	pop,rock,rap
};
class CD;
class Pesna {
	friend class CD;
	char *name;
	int vreme;
	tip tipot;
public:
	Pesna() {
		name=nullptr;
		vreme=0;
		tipot=pop;
	}
	Pesna(char *name,int vreme,tip tipot) {
		this->name=new char[strlen(name)+1];
		strcpy(this->name,name);
		this->vreme=vreme;
		this->tipot=tipot;
	}
	~Pesna() {
		delete[] name;
	}
	Pesna &operator=(const Pesna n){
		if(this!=&n){
			delete [] this->name;
			name=new char[ strlen(n.name)+1];
			strcpy(this->name,n.name);
			this->vreme=n.vreme;
			this->tipot=n.tipot;
		}
		return *this;
	}
	Pesna (const Pesna &p) {
		this->name=new char[strlen(p.name)+1];
		strcpy(this->name,p.name);
		this->vreme=p.vreme;
		this->tipot=p.tipot;
	}
	void pecati(){
		cout<<"'"<<this->name<<"' - "<<this->vreme<<"min"<<endl;
	}


};
class CD {
private:
	friend class Pesna;
	Pesna niza[10];
	int broj;
	int max_vreme;
public:
	CD(int max) {
		this->max_vreme=max;
		broj=0;
	}
	CD() {
		this->max_vreme=0;
		broj=0;

	}
	~CD(){}
	CD(const CD &n) {
		this->max_vreme=n.max_vreme;
		broj=n.broj;
		for (int i=0;i<broj;i++) {
			this->niza[i]=n.niza[i];
		}
	}
	void dodadiPesna(Pesna p) {
		if (broj<10) {
			int zbir=0;
			for (int i=0;i<broj;i++) {
				zbir+=niza[i].vreme;
			}
			if ((zbir+p.vreme)<=max_vreme) {
				niza[broj++]=p;
			}
		}
	}
	void pecatiPesniPoTip(tip t) {
		for (int i=0;i<broj;i++) {
			if (niza[i].tipot==t) {
				niza[i].pecati();
			}
		}
	}
	Pesna getPesna(int n) {
		return niza[n];
	}
	int getBroj() {
		return broj;
	}
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}