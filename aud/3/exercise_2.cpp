/* Да се дефинира класа Ekipa (име, година, град).
Да се дефинира класа Natprevar (домаќин, гостин, голови).
Да се дефинира функција revans која проверува дали едниот натпревар е реванш на другиот.
Еден натпревар е реванш на друг ако гостинот и домаќинот од првиот натпревар
се истите екипи со домаќинот и гостинот од вториот натпревар. */

#include <cstring>
#include <iostream>
using namespace std;

class Ekipa {
private:
    char name[20];
    int godina;
    char grad[20];

public:
    Ekipa(const char *namee="", int godinaa=0, const char *gradd="") {
        strcpy(name, namee);
        godina = godinaa;
        strcpy(grad, gradd);
    }

    ~Ekipa() {}

    const char *getName() const {
        return name;
    }
};

class Natprevar {
private:
    Ekipa home;
    Ekipa away;
    int points_home;
    int points_away;

public:
    Natprevar(Ekipa prva, int points_homee, Ekipa vtora, int points_awayy)
        : home(prva), away(vtora), points_home(points_homee), points_away(points_awayy) {}

    ~Natprevar() {}

    const Ekipa &getHome() const {
        return home;
    }

    const Ekipa &getAway() const {
        return away;
    }

    int get_hpoints() const {
        return points_home;
    }
};

bool revans(const Natprevar &natprevar1, const Natprevar &natprevar2) {
    return (strcmp(natprevar1.getAway().getName(), natprevar2.getHome().getName()) == 0) &&
           (strcmp(natprevar1.getHome().getName(), natprevar2.getAway().getName()) == 0);
}

int main() {
    char name[100];
    char grad[100];
    int godina;

    cin.getline(name, 100);
    cin.getline(grad, 100);
    cin >> godina;
    cin.ignore();
    Ekipa home(name, godina, grad);

    cin.getline(name, 100);
    cin.getline(grad, 100);
    cin >> godina;
    cin.ignore();
    Ekipa away(name, godina, grad);

    Natprevar prv(home, 1, away, 2);
    Natprevar vtor(away, 2, home, 1);

    if (revans(prv, vtor)) {
        cout << "The matches are reverses of each other!" << endl;
    } else {
        cout << "The matches are not reverses of each other!" << endl;
    }

    return 0;
}