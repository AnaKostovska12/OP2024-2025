#include <iostream>
#include <cstring>
using namespace std;
class InvalidTeamName {
private:
    char teamName[50];
    public:
    InvalidTeamName() {
        strcpy(teamName," ");
    }
    InvalidTeamName(char *team) {
        strcpy(teamName, team);
    }
    char *what() {
      return teamName;
    }
};
class Goal {
protected:
    char *goalScorer;
    int minute;
    char team[51];
    public:
    Goal () {
       goalScorer = NULL;
        minute = 0;
        strcpy(team,"");
    }
    Goal(char *goalScorer,int minute,char *team) {
        this->goalScorer = new char[strlen(goalScorer)+1];
        strcpy(this->goalScorer,goalScorer);
        this->minute = minute;
        strcpy(this->team,team);
    }
    Goal (const Goal &n) {
        goalScorer = new char[strlen(n.goalScorer)+1];
        strcpy(goalScorer,n.goalScorer);
        minute = n.minute;
    }
    Goal &operator=(const Goal &n) {
        if (this != &n) {
            delete [] goalScorer;
            goalScorer = new char[strlen(n.goalScorer)+1];
            strcpy(goalScorer,n.goalScorer);
            minute = n.minute;
        }
        return *this;
    }
    const char *getTeam()  {
        return team;
    }
    ~Goal() {
        delete [] goalScorer;
    }
    friend ostream &operator<<(ostream &os, const Goal &n) {
        os << n.minute<<" "<<n.goalScorer<<endl;
        return os;
    }
    Goal &operator++( int n) {
        Goal temp = *this;
        this->minute ++;
        return temp;
    }
    Goal &operator--( ) {
        this->minute --;
        return *this;
    }

};
class Game {
private:
    Goal *niza;
    int broj;
    char team1[51];
    char team2[51];
    public:
    Game() {
        niza = NULL;
        broj = 0;
        strcpy(team1,"");
        strcpy(team2,"");
    }
    Game(char *team1,char *team2) {
        broj=0;
        strcpy(this->team1,team1);
        strcpy(this->team2,team2);
    }
    ~Game() {
        delete [] niza;
    }
    Game &operator+=( Goal &n) {
        // Check if the team's name matches either team1 or team2
        if (strcmp(n.getTeam(),team1)!=0 && strcmp(n.getTeam(),team2)!=0) {
            InvalidTeamName ex((char*)n.getTeam());  // pass the invalid team name from the goal
            throw ex;
        }
        Goal *temp= new Goal[broj+1];
        for (int i=0; i<broj; i++) {
            temp[i]=niza[i];
        }
        temp[broj++] = n;
        delete [] niza;
        niza = temp;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const Game &n) {
        os << n.team1<<" - "<<n.team2<<endl;
        for (int i=0;i<n.broj;i++) {
            os<<n.niza[i];
        }
        return os;
    }
};
// Your code here


int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}
