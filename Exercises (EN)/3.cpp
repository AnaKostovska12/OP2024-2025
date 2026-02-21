#include <iostream>
#include <cstring>
using namespace std;

class Character {
private:
    char a;

public:
    Character() {
        a = 'a';
    }

    Character(char a) {
        this->a = a;
    }

    ~Character() {}

    bool operator==(const Character &other) const {
        return this->a == other.a;
    }

    Character &operator=(const Character &other) {
        if (this != &other) {
            this->a = other.a;
        }
        return *this;
    }

    Character &operator=(char c) {
        this->a = c;
        return *this;
    }

    Character toUpper() const {
        return Character(toupper(a));
    }

    friend ostream &operator<<(ostream &out, const Character &c) {
        out << c.a;
        return out;
    }

    char getChar() const {
        return a;
    }
};

class CharSequence {
private:
    Character *sequence;
    int length;

public:
    CharSequence() {
        sequence = nullptr;
        length = 0;
    }

    ~CharSequence() {
        delete[] sequence;
    }

    CharSequence(const CharSequence &other) {
        length = other.length;
        sequence = new Character[length];
        for (int i = 0; i < length; i++) {
            sequence[i] = other.sequence[i];
        }
    }

    CharSequence &operator=(const CharSequence &other) {
        if (this != &other) {
            delete[] sequence;
            length = other.length;
            sequence = new Character[length];
            for (int i = 0; i < length; i++) {
                sequence[i] = other.sequence[i];
            }
        }
        return *this;
    }

    CharSequence(char *seq) {
        length = strlen(seq);
        sequence = new Character[length];
        for (int i = 0; i < length; i++) {
            sequence[i] = Character(seq[i]);
        }
    }

    Character &operator[](int i) {
        return sequence[i];
    }

    CharSequence &operator+=(const Character &c) {
        Character *temp = new Character[length + 1];
        for (int i = 0; i < length; i++) {
            temp[i] = sequence[i];
        }
        temp[length] = c;
        delete[] sequence;
        sequence = temp;
        length++;
        return *this;
    }

    bool operator==(const CharSequence &cs) const {
        if (length != cs.length) return false;
        for (int i = 0; i < length; i++) {
            if (!(sequence[i] == cs.sequence[i])) return false;
        }
        return true;
    }

    int countChar(char c) const {
        int count = 0;
        for (int i = 0; i < length; i++) {
            if (sequence[i] == Character(c)) {
                count++;
            }
        }
        return count;
    }

    CharSequence toUpperCase() const {
        CharSequence temp;
        temp.length = length;
        temp.sequence = new Character[length];
        for (int i = 0; i < length; i++) {
            temp.sequence[i] = sequence[i].toUpper();
        }
        return temp;
    }

    friend ostream &operator<<(ostream &out, const CharSequence &cs) {
        for (int i = 0; i < cs.length; i++) {
            out << cs.sequence[i];
        }
        return out;
    }
};

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if (n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if (n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if (n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if (n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for (int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if (n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs.countChar('e') << endl;
    } else if (n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    } else if (n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}
