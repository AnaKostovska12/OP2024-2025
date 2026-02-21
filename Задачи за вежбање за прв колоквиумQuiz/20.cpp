#include<stdio.h>
#include <iostream>
#include <cstring>
#include <iostream>
#include <cstring>
using namespace std;

struct Pacient {
    char ime[100];
    bool zdrastveno;
    int pregledi;
};

struct doktor {
    char ime[100];
    int br_pac;
    Pacient niza[200];
    float cena;

    float zaraboteno() {
        float counter = 0;
        for (int i = 0; i < br_pac; i++) {
            if (!niza[i].zdrastveno) {
                counter += niza[i].pregledi;
            }
        }
        return cena * counter;
    }

    // Method to calculate the total number of consultations for the doctor
    int vkupno_pregledi() {
        int zbir = 0;
        for (int i = 0; i < br_pac; i++) {
            zbir += niza[i].pregledi;
        }
        return zbir;
    }
};

void najuspesen_doktor(doktor *niza, int n) {
    doktor temp = niza[0];
    float max_zaraboteno = temp.zaraboteno();

    for (int i = 1; i < n; i++) {
        float currentEarnings = niza[i].zaraboteno();

        if (currentEarnings > max_zaraboteno) {
            max_zaraboteno = currentEarnings;
            temp = niza[i];
        } else if (currentEarnings == max_zaraboteno) {

            int currentTotalPregledi = niza[i].vkupno_pregledi();
            int tempTotalPregledi = temp.vkupno_pregledi();

            if (currentTotalPregledi > tempTotalPregledi) {
                temp = niza[i];
            }
        }
    }

    cout << temp.ime << " " << max_zaraboteno << ".00 " << temp.vkupno_pregledi() << endl;
}

int main()
{
	int i, j, n, broj;
	doktor md[200];
	scanf("%d", &n);
	for (i = 0; i < n; i++){

		scanf("%s", &md[i].ime);

		scanf("%d", &md[i].br_pac);

		scanf("%f", &md[i].cena);

		for (j = 0; j < md[i].br_pac; j++){
			scanf("%s", &md[i].niza[j].ime);
			scanf("%d", &md[i].niza[j].zdrastveno);
			scanf("%d", &md[i].niza[j].pregledi);
		}
	}
	najuspesen_doktor(md, n);

	return 0;
}
