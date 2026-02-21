#include <iostream>
#include <cstring>
using namespace std;

class UserProfile;

class Achievement {
private:
    friend void showAchievementsProgress(UserProfile *profiles, int n, Achievement* achievements, int m);
    friend class UserProfile;
    char name[20];
    char description[20];
    static int totalUserAchievements;

public:
    Achievement() {}

    Achievement(char *na, char *de) {
        strcpy(name, na);
        strcpy(description, de);
    }

    Achievement(Achievement &n) {
        strcpy(name, n.name);
        strcpy(description, n.description);
    }

    void print() {
        cout << "Achievement Name: " << name << endl;
        cout << "Description: " << description << endl;
    }

    static void incrementTotalUserAchievements() {
        totalUserAchievements++;
    }

    static int getTotalUserAchievements() {
        return totalUserAchievements;
    }
};
int Achievement::totalUserAchievements = 0;

class UserProfile {
private:
    friend void showAchievementsProgress(UserProfile *profiles, int n, Achievement* achievements, int m);
    friend class Achievement;
    char name[20];
    Achievement niza[50];
    int n;

public:
    UserProfile() {
        n = 0;
    }

    UserProfile(char *namee) {
        strcpy(name, namee);
        n = 0;
    }

    ~UserProfile() {}

    UserProfile(char *namee, Achievement *nizaa, int nn) {
        strcpy(name, namee);
        n = nn;
        for(int i = 0; i < n; i++) {
            niza[i] = nizaa[i];
        }
    }

    void print() {
        cout << "User Profile: " << name << endl;
        for (int i = 0; i < n; i++) {
            niza[i].print();
        }
    }

    void addAchievement(const Achievement &achievement) {
        niza[n++] = achievement;
        niza[n-1].incrementTotalUserAchievements();
    }

    bool prisutenAchievement(Achievement nov) {
        for (int i = 0; i < n; i++) {
            if (strcmp(niza[i].name, nov.name) == 0) {
                return true;
            }
        }
        return false;
    }
};

void showAchievementsProgress(UserProfile *profiles, int n, Achievement *achievements, int m) {
    int counter = 0;
    for(int i = 0; i < m; i++) {
        counter = 0;
        for(int j = 0; j < n; j++) {
            if (profiles[j].prisutenAchievement(achievements[i])) {
                counter++;
            }
        }
        double percentage = (counter * 100.0) / n;
        achievements[i].print();
        cout << "Percentage of users with this achievement: " << percentage << "%" << endl;
    }
    double average=Achievement::getTotalUserAchievements()*100.0/(n*m);
    cout << "Average number of achievements per user: " << average << "%" << endl;
}

int main() {
    char testcase[100];
    cin.getline(testcase, 100);

    int n;
    cin >> n;
    cin.ignore();

    char ignore[100];
    cin.getline(ignore, 100);
    UserProfile users[100];
    for (int i = 0; i < n; ++i) {
        char name[100];
        cin >> name;
        users[i] = UserProfile(name);
    }

    int m;
    cin >> m;
    cin.ignore();

    cin.getline(ignore, 100);
    Achievement achievements[100];
    for (int i = 0; i < m; ++i) {
        char name[100], description[100];
        cin.getline(name, 100);
        cin.getline(description, 100);
        achievements[i] = Achievement(name, description);
    }

    int k;
    cin >> k;
    cin.ignore();

    cin.getline(ignore, 100);
    for (int i = 0; i < k; ++i) {
        int numUser, numAchievement;
        cin >> numUser >> numAchievement;
        numUser -= 1;
        numAchievement -= 1;
        users[numUser].addAchievement(achievements[numAchievement]);
    }

    if (testcase[8] == 'A') {
        for (int i = 0; i < m; ++i) {
            achievements[i].print();
        }
        Achievement::incrementTotalUserAchievements();
    } else if (testcase[8] == 'U') {
        for (int i = 0; i < n; ++i) {
            users[i].print();
        }
    } else {
        showAchievementsProgress(users, n, achievements, m);
    }

    return 0;
}