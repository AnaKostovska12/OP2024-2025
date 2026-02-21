using namespace std;
#include <iostream>
#include <cstring>
class List {
    int *lista;
    int broj;
    public:
    List() {
        lista = NULL;
        broj = 0;
    }
    int getBroj(){
        return broj;
    }
    List(int *lista,int broj) {
        this->broj=broj;
        this->lista = new int[broj];
        for (int i=0;i<broj;i++) {
            this->lista[i] = lista[i];
        }
    }
    List(const List &l) {
        this->broj=l.broj;
        this->lista = new int[broj];
        for (int i=0;i<broj;i++) {
            this->lista[i] = l.lista[i];
        }
    }
    ~List() {
        delete [] lista;
    }
    List &operator=(const List &l) {
        if(this!=&l){
        delete [] lista;
        this->broj=l.broj;
        this->lista = new int[l.broj];
        for (int i=0;i<broj;i++) {
            this->lista[i] = l.lista[i];
        }}
        return *this;
    }
    void pecati() {
        cout<<broj<<": ";
        int zbir=0;
        for (int i=0;i<broj;i++) {
            zbir+=lista[i];
            if(i==broj-1){
                cout<<lista[i];
            }
            else
            cout<<lista[i]<<" ";
        }
        cout<<" sum: "<<zbir;
        cout<<" average: "<<zbir/(double)broj<<endl;
    }
    int sum() {
        int zbir=0;
        for (int i=0;i<broj;i++) {
            zbir+=lista[i];
        }
        return zbir;
    }
    double average() {
        return sum()/broj*1.0;
    }


};
class ListContainer {
private:
    List *niza;
    int broj;
    static int dodavanje;
    static int nedodavanja;
    public:
    ListContainer() {
        niza = NULL;
        broj = 0;

    }
    ListContainer(List *niza,int broj){
        this->broj=broj;
        niza =new List[broj];
        for(int i=0;i<broj;i++){
            this->niza[i]=niza[i];
        }
    }
    ListContainer(const ListContainer &l) {
        this->broj=l.broj;
             niza =new List[l.broj];
        for (int i=0;i<broj;i++) {
            this->niza[i]=l.niza[i];
        }
    }
    ~ListContainer() {
        delete [] niza;
    }
    ListContainer &operator=(const ListContainer &l) {

        if (this!=&l) {
            delete [] niza;
            this->broj=l.broj;
                  niza =new List[l.broj];
            for (int i=0;i<broj;i++) {
                this->niza[i]=l.niza[i];
            }
        }
        return *this;
    }
    void print() {
        if (broj==0) {
            cout<<"The list is empty "<<endl;
        }
        else {
            for (int i=0;i<broj;i++) {
                cout<<"List number: "<<i+1<<" List info: ";
                niza[i].pecati();
            }
            cout<<"Sum: "<<sum();
            cout<<" Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<dodavanje;
            cout<<" Failed attempts: "<<nedodavanja<<endl;
        }


    }
    void addNewList(List l) {
        bool flag=true;
        for (int i=0;i<broj;i++) {
            if (niza[i].sum()==l.sum()) {
                flag=false;
            }
        }
        if (flag) {
           List *temp = new List[broj + 1];
        for (int i = 0; i < broj; i++) {
            temp[i] = niza[i]; // calls assignment operator of List
        }
        temp[broj++] = l;
        delete[] niza;
        niza = temp;
        dodavanje++;
        }
        else nedodavanja++;
    }
    int sum() {
        int zbir=0;
        for (int i=0;i<broj;i++) {
            zbir+=niza[i].sum();
        }
        return zbir;
    }
    // double average() {
    //   double zbir=0;
    //     for (int i=0;i<broj;i++) {
    //         zbir+=niza[i].average();
    //     }
    //     return (zbir/broj)*1.0;
    // }
    double average() {
    int totalSum = 0;
    int totalCount = 0;
    for (int i = 0; i < broj; i++) {
        totalSum += niza[i].sum();
        totalCount += niza[i].getBroj();  // 🔴 Add this getter if missing
    }
    return totalCount == 0 ? 0 : (double)totalSum / totalCount;
}

};
int ListContainer::dodavanje=0;
int ListContainer::nedodavanja=0;

int main() {

	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];

		cin>>n;

		for (int j=0;j<n;j++){
			cin>>niza[j];

		}

		List l=List(niza,n);

		lc.addNewList(l);
	}


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}