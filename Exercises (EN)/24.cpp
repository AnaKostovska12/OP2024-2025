#include<iostream>
#include<cstring>

using namespace std;

class InvalidTimeException {
public:
    void message() {
        cout << "Invalid Time" << endl;
    }
};

class Race {
protected:
    char city[40];
    int year, month;
    float bestTime, length;
public:
    Race(const char *city = "", int year = 1950, int month = 1, float bestTime = 60, float length = 0) {
        strcpy(this->city, city);
        this->year = year;
        this->month = month;
        this->bestTime = bestTime;
        this->length = length;
    }

    Race(const Race &r) {
        strcpy(this->city, r.city);
        this->year = r.year;
        this->month = r.month;
        this->bestTime = r.bestTime;
        this->length = r.length;
    }

    ~Race() {}

    virtual float complexity() {
        return (bestTime / length);
    }

    friend ostream &operator<<(ostream &o, Race &r) {
        o << r.city << " " << r.month << "." << r.year << " " << r.complexity() << endl;
        return o;
    }
};

class MotoGPRace : public Race {
private:
    float *practiceTimes;
    int n;
    int laps;
    static float coef;
public:

    MotoGPRace(const char *city = "", int year = 1950, int month = 1, float bestTime = 60, float length = 0,
               const float *practiceTimes = nullptr, int n = 0,
               int laps = 0)
            : Race(city, year, month, bestTime, length), n(n), laps(laps) {
        this->practiceTimes = new float[n];
        for (int i = 0; i < n; ++i) {
            this->practiceTimes[i] = practiceTimes[i];
        }
    }


    float average() {
        float sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += practiceTimes[i];
        }
        return sum / (float) n;
    }

    float complexity() override {
        float res = Race::complexity() + (average() * coef);
        if (laps > 22) {
            res *= 1.2;
        }
        return res;
    }

    static void setK(float coef) {
        MotoGPRace::coef = coef;
    }

    MotoGPRace &operator+=(float time) {
        if (time < 9.5) {
            throw InvalidTimeException();
        } else {
            float *tmp = new float[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = practiceTimes[i];
            }
            tmp[n++] = time;
            delete[]practiceTimes;
            practiceTimes = tmp;
        }
        return *this;
    }

    MotoGPRace operator++(int) {
        MotoGPRace temp = *this; // Save the current state
        laps++;
        return temp; // Return the saved state
    }

    int getNumberLaps() {
        return laps;
    }

    void setNumberLaps(int laps) {
        MotoGPRace::laps = laps;
    }
};


float MotoGPRace::coef = 0.4;


int main() {
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int choice;
    int numberLaps;

    if (testCase == 1) {
        cout << "===== Testing - classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        Race t(city, year, month, bestTime, length);
        cout << t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        MotoGPRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2) {
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            MotoGPRace *nn = dynamic_cast<MotoGPRace *>(rArray[i]);
            if (nn != 0) {
                flag = 0;
                try { (*nn) += best; } catch (InvalidTimeException e) {
                    e.message();
                }
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3) {
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1, time2;
        cin >> time1 >> time2;

        try {
            mgt += time1;
            mgt += time2;
        } catch (InvalidTimeException e) {
            e.message();
        }

        cout << mgt;
    }
    if (testCase == 4) {
        cout << "===== Testing - operator++ ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        float v, koef2;
        cout << (mgt++).getNumberLaps() << endl;
        cout << mgt;
        mgt++;
        cout << mgt;
    }
    if (testCase == 5) {
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6) {
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin >> newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin >> newBest;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            MotoGPRace *pok = dynamic_cast<MotoGPRace *>(rArray[i]);
            if (pok != 0) {
                (*pok)++;
                try {
                    (*pok) += newBest;
                } catch (InvalidTimeException e) {
                    e.message();
                }
                if (flag == 1) {
                    flag = 0;
                    try {
                        *pok += 1.4;
                    } catch (InvalidTimeException e) {
                        e.message();
                    }
                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}