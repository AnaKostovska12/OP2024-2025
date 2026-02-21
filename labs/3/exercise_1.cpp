#include <iostream>
#include <cstring>
using namespace std;

class Mountain;
class MountainTrail {
    friend void sortMountainsByPeakElevation( Mountain *mountains,int n);
    char name[20];
    int length;
    double slope;
    public:
    MountainTrail() {}
    ~MountainTrail() {}
    MountainTrail(char *namee, int lengthh, double slopee) {
        strcpy(name, namee);
        this->length = lengthh;
        this->slope = slopee;
    }
    MountainTrail(MountainTrail &t) {
        strcpy(name, t.name);
        this->length = t.length;
        this->slope = t.slope;
    }
    void display() {
        cout<<name<<" "<<length<<" "<<slope<<endl;
    }
    double difficulty() {
        double difficulty = length*slope/100*1.0;
        return difficulty;
    }
};

class Mountain {
    friend void sortMountainsByPeakElevation( Mountain *mountains,int n);
    char name[20];
    MountainTrail trails[5];
    int peak_elevation;
   static int num_mountains;
    public:
    Mountain() {num_mountains ++;}
    ~Mountain() { num_mountains --;}
    Mountain(char *namee, MountainTrail *trailss, int peak_elevationn) {
        strcpy(name, namee);
        for (int i = 0; i <5; i++) {
            trails[i]=trailss[i];
        }
        peak_elevation = peak_elevationn;
        num_mountains ++;
    }
  static  int getNumMountains() {
        return num_mountains;
    }
    void display() {
        cout<<name<<":"<<peak_elevation<<"m"<<endl;
    }
};

int Mountain::num_mountains=0;

void sortMountainsByPeakElevation( Mountain *mountains,int n)
{
    Mountain temp;
    for (int i = 0; i <n; i++) {
        for (int j = 0; j <n-1-i; j++) {
            if (mountains[j+1].peak_elevation>mountains[j].peak_elevation) {
                temp=mountains[j];
                mountains[j]=mountains[j+1];
                mountains[j+1]=temp;
            }
        }
    }
    for(int i=0; i<n; i++) {
        mountains[i].display();
    }
}

int main() {
    int test_case_n;
    char trail_name[100];
    int trail_length;
    double trail_slope;
    char mountain_name[100];
    int mountain_peak_elevation;

    cin>>test_case_n;
    if (test_case_n == 0) {
        cout << "Testing MountainTrail c-tors, display function:"<<endl;
        cin >> trail_name >> trail_length >> trail_slope;
        MountainTrail mt = MountainTrail(trail_name, trail_length, trail_slope);
        MountainTrail mt2 = MountainTrail(mt);
        mt.display();
        mt2.display();
    } else if (test_case_n == 1) {
        cout << "Testing MountainTrail difficulty function:"<<endl;
        for (int i = 0; i < 5; ++i) {
            cin >> trail_name >> trail_length >> trail_slope;
            MountainTrail mt = MountainTrail(trail_name, trail_length, trail_slope);
            cout<<mt.difficulty()<<endl;
        }
    } else if (test_case_n == 2) {
        cout << "Testing Mountain c-tor, display function:"<<endl;
        MountainTrail trails[5];
        cin>>mountain_name>>mountain_peak_elevation;
        for (int i = 0; i < 5; ++i) {
            cin >> trail_name >> trail_length >> trail_slope;
            trails[i] = MountainTrail(trail_name, trail_length, trail_slope);
        }
        Mountain mountain = Mountain(mountain_name, trails, mountain_peak_elevation);
        mountain.display();
    } else if (test_case_n == 3) {
        cout << "Testing static field in Mountain:" <<endl;
        MountainTrail trails[5];
        cin>>mountain_name>>mountain_peak_elevation;
        for (int i = 0; i < 5; ++i) {
            cin >> trail_name >> trail_length >> trail_slope;
            trails[i] = MountainTrail(trail_name, trail_length, trail_slope);
        }
        for (int i = 0; i < 10; ++i) {
            Mountain mountain = Mountain(mountain_name, trails, mountain_peak_elevation);
        }
        Mountain m1 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m2 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m3 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m4 = Mountain(mountain_name, trails, mountain_peak_elevation);
        Mountain m5 = Mountain(mountain_name, trails, mountain_peak_elevation);

        if(Mountain::getNumMountains() == 5) {
            cout<<"OK";
        } else {
            cout<<"Missing mountain count increment/decrement";
        }
    } else if (test_case_n == 4) {
        int M;
        cin>>M;
        cout<<"Testing order function:"<<endl;
        Mountain mountains[M];
        for (int i = 0; i < M; ++i) {
            cin>>mountain_name>>mountain_peak_elevation;
            MountainTrail trails[5];
            for (int j = 0; j < 5; ++j) {
                cin >> trail_name >> trail_length >> trail_slope;
                trails[j] = MountainTrail(trail_name, trail_length, trail_slope);
            }
            mountains[i] = Mountain(mountain_name, trails, mountain_peak_elevation);
        }
        sortMountainsByPeakElevation(mountains, M);
    }
    return 0;
}