/* Да се напише класа која опишува една e-mail порака. Во класата треба да се имплементира метод за
прикажување на целокупната порака на екран. Потоа да се напише главна програма во која се внесуваат
параметрите на пораката, се инстанцира објект од оваа класа и се печати на екран неговата содржина.
За проверување на валидноста на e-mail пораката (постоење на знакот @ во адресата) да се напише
соодветна функција. */

#include <iostream>
#include <cstring>
using namespace std;

class email {
private:
    char to[30];
    char from[30];
    char subject[100];
    char message[1000];
public:
    // Default constructor
    email() {}

    // Parameterized constructor
    email(char *too, char *fromm, char *subjectt, char *messagee) {
        strcpy(to, too);
        strcpy(from, fromm);
        strcpy(subject, subjectt);
        strcpy(message, messagee);
    }

    // Destructor
    ~email() {}

    // Function to display the email content
    void get_everything() {
        cout << "To: " << to << endl;
        cout << "From: " << from << endl;
        cout << "Subject: " << subject << endl;
        cout << "Message: " << message << endl;
    }

    // Setters
    void set_to(char *too) {
        strcpy(to, too);
    }
    void set_from(char *fromm) {
        strcpy(from, fromm);
    }
    void set_subject(char *subjectt) {
        strcpy(subject, subjectt);
    }
    void set_message(char *messagee) {
        strcpy(message, messagee);
    }
};

// Function to validate if the email address contains one '@' character
bool dobra(char *vrednost) {
    int counter = 0;
    for (int i = 0; i < strlen(vrednost); i++) {
        if (vrednost[i] == '@') counter++;  // Compare with '@' character
    }
    return counter == 1;  // Return true if exactly one '@' is found
}

int main() {
    char to[30], from[30], subject[100], message[1000];

    // Input email details
    cout << "Enter To address: ";
    cin.getline(to, 30);
    cout << "Enter From address: ";
    cin.getline(from, 30);
    cout << "Enter Subject: ";
    cin.getline(subject, 100);
    cout << "Enter Message: ";
    cin.getline(message, 1000);

    // Create email object
    email mail(to, from, subject, message);

    // Validate the input (Only 'to' and 'from' should have an '@')
    if (dobra(to) && dobra(from) && !dobra(subject) && !dobra(message)) {
        mail.get_everything();  // Print email details
    } else {
        cout << "Invalid email input." << endl;
    }

    return 0;
}