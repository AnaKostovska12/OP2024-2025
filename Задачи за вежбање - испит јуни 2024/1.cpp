#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Song {
protected:
    string name;
    string author;
    string performer;
    int duration;

public:
    Song() : name(""), author(""), performer(""), duration(0) {}

    Song(string name, string author, string performer, int duration)
        : name(name), author(author), performer(performer), duration(duration) {}

    Song(const Song &s) = default;

    Song &operator=(const Song &s) = default;

    string getName() const { return name; }
    string getAuthor() const { return author; }
    string getPerformer() const { return performer; }
    int getDuration() const { return duration; }

    void setName(const string &n) { name = n; }
    void setAuthor(const string &a) { author = a; }
    void setPerformer(const string &p) { performer = p; }
    void setDuration(int d) { duration = d; }

    friend istream &operator>>(istream &in, Song &s) {
        getline(in, s.name);
        getline(in, s.author);
        getline(in, s.performer);
        in >> s.duration;
        in.ignore();
        return in;
    }

    void print(ofstream &out) const {
        out << "Song title: " << name
            << ", Author: " << author
            << ", Interpreted by: " << performer
            << ", " << duration << " sek." << endl;
    }

    bool operator==(const Song &s) const {
        return name == s.name && author == s.author && performer == s.performer && duration == s.duration;
    }
};

class Festival {
private:
    string name;
    string city;
    string date;
    Song *songs;
    int n;

public:
    Festival() : name(""), city(""), date(""), songs(nullptr), n(0) {}

    Festival(string name, string city, string date, Song *songs, int n)
        : name(name), city(city), date(date), n(n) {
        this->songs = new Song[n];
        for (int i = 0; i < n; i++) {
            this->songs[i] = songs[i];
        }
    }

    Festival(const Festival &f) : name(f.name), city(f.city), date(f.date), n(f.n) {
        songs = new Song[n];
        for (int i = 0; i < n; i++) {
            songs[i] = f.songs[i];
        }
    }

    Festival &operator=(const Festival &f) {
        if (this != &f) {
            delete[] songs;
            name = f.name;
            city = f.city;
            date = f.date;
            n = f.n;
            songs = new Song[n];
            for (int i = 0; i < n; i++) {
                songs[i] = f.songs[i];
            }
        }
        return *this;
    }

    ~Festival() {
        delete[] songs;
    }

    void operator-=(Song &target) {
        if (n == 0) {
            cout << "Trying to delete from an empty list!" << endl;
            return;
        }

        int count = 0;
        for (int i = 0; i < n; i++) {
            if (songs[i] == target) count++;
        }

        if (count == 0) return;

        Song *temp = new Song[n - count];
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (!(songs[i] == target)) {
                temp[j++] = songs[i];
            }
        }

        delete[] songs;
        songs = temp;
        n = j;
    }

    void print(ofstream &out) const {
        out << "Festival: " << name << " - " << city << ", " << date << endl;
        for (int i = 0; i < n; i++) {
            songs[i].print(out);
        }
    }

    friend istream &operator>>(istream &in, Festival &f) {
        getline(in, f.name);
        getline(in, f.city);
        getline(in, f.date);
        in >> f.n;
        in.ignore();
        f.songs = new Song[f.n];
        for (int i = 0; i < f.n; i++) {
            in >> f.songs[i];
        }
        return in;
    }

    Festival notFromAuthor(string author) {
        Festival result;
        result.name = name;
        result.city = city;
        result.date = date;
    if (n == 0) {
        cout << "Trying to delete from an empty list!" << endl;
        result.songs = nullptr;
        result.n = 0;
        return result;
    }

        int count = 0;
        for (int i = 0; i < n; i++) {
            if (songs[i].getAuthor() != author) count++;
        }

        result.songs = new Song[count];
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (songs[i].getAuthor() != author) {
                result.songs[j++] = songs[i];
            }
        }
        result.n = j;
        return result;
    }
};

void wtf() {
    ofstream fout("vlezna.txt");
    string line;
    while (getline(cin, line)) {
        if (line == "----") break;
        fout << line << endl;
    }
}

void rff(const string &path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

int main() {
    wtf();

    Festival festival;
    ifstream in("vlezna.txt");
    in >> festival;
    in.close();

    string author;
    getline(cin, author);

    ofstream out1("izlezna1.txt");
    festival.print(out1);
    out1.close();

    ofstream out2("izlezna2.txt");
    Festival filtered = festival.notFromAuthor(author);
    filtered.print(out2);
    out2.close();

    cout << "All the data for the festival:" << endl;
    rff("izlezna1.txt");
    cout << "Songs NOT from the author " << author << ": " << endl;
    rff("izlezna2.txt");

    return 0;
}
