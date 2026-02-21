using namespace std;
#include <iostream>
#include <cstring>
enum Extension {
 pdf,	txt, exe
};
class File {
	char *name;
	Extension ekstenzija;
	char *sopstvenik;
	int golemina;
public:
	File() {
		name=nullptr;
		sopstvenik=nullptr;
		ekstenzija=txt;
		golemina=0;
	}
	File(char *name,char *sopstvenik,int gol,Extension eks) {
		this->name=new char[strlen(name)+1];
		strcpy(this->name,name);
		this->sopstvenik=new char[strlen(sopstvenik)+1];
		strcpy(this->sopstvenik,sopstvenik);
		this->ekstenzija=eks;
		this->golemina=gol;
	}
	File (const File &n) {
		this->name=new char[strlen(n.name)+1];
		strcpy(this->name,n.name);
		this->sopstvenik=new char[strlen(n.sopstvenik)+1];
		strcpy(this->sopstvenik,n.sopstvenik);
		this->ekstenzija=n.ekstenzija;
		this->golemina=n.golemina;
	}
	~File() {
		delete[] name;
		delete[] sopstvenik;
	}
	File &operator=(const File &n) {
		if (this!=&n) {
			delete [] name;
			delete [] sopstvenik;
			this->name=new char[strlen(n.name)+1];
			strcpy(this->name,n.name);
			this->sopstvenik=new char[strlen(n.sopstvenik)+1];
			strcpy(this->sopstvenik,n.sopstvenik);
			this->ekstenzija=n.ekstenzija;
			this->golemina=n.golemina;
		}
		return *this;
	}
void print() {
		cout<<"File name: "<<name;
		if (ekstenzija==txt) {
			cout<<".txt"<<endl;
		}
		else if (ekstenzija==pdf) {
			cout<<".pdf"<<endl;
		}
		else if (ekstenzija==exe) {
			cout<<".exe"<<endl;
		}
          cout<<"File owner: "<<sopstvenik<<endl;
        cout<<"File size: "<<golemina<<endl;
	}
	bool equals(const File & that) {
		if (this->ekstenzija==that.ekstenzija
			&&
			strcmp(this->name,that.name)==0
			&& strcmp(this->sopstvenik,that.sopstvenik)==0)
         {return true;}
		else return false;
	}
	bool equalsType(const File & that) {
		if (this->ekstenzija==that.ekstenzija
			&&
			strcmp(this->name,that.name)==0)
		 {return true;}
		else return false;
	}
};
class Folder {
	char *name;
   int broj;
	File *niza;
	public:
	Folder(char *name) {
		this->name=new char[strlen(name)+1];
		strcpy(this->name,name);
		this->broj=0;
		niza=nullptr;
	}
	~Folder() {
		delete[] this->name;
	}
	void print() {
		cout<<"Folder name: "<<name<<endl;
		for (int i=0;i<broj;i++) {
			niza[i].print();
		}
	}
	void remove(const File & file) {
		int index;
		for (int i=0;i<broj;i++) {
			if (niza[i].equals(file)) {
				index=i;
			}
		}
		File *temp;
		temp= new File[broj-1];
		for (int i=0;i<broj;i++) {
			if (index!=i) {
				temp[i]=niza[i];
			}
		}
		delete[] niza;
		niza=temp;
		broj--;
	}
	void add(const File & file) {
		File *temp;
		temp=new File[broj+1];
		for (int i=0;i<broj;i++) {
			temp[i]=niza[i];
		}
		temp[broj++]=file;

		delete [] niza;
		niza=temp;
	}

};
int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}