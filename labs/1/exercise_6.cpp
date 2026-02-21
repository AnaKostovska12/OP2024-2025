/*Да се креира структура Student во која се чуваат податоци за еден студент. За студентот се чуваат информации за
името на студентот(низа од карактери), број на индекс на студентот, број на курсеви кои ги слуша, низа од кодови
на курсевите кои ги слуша.

Потоа, да се креира структура Course во која се чуваат податоци за името на курсот (низа од карактери), код на
курсот(цел број) и број на студенти кои го слушаат.

Да се направи функција:

int get_most_popular_course(struct course courses[], int num_courses)
кoja што го враќа кодот на најпопуларниот курс.
Напомена: Прво од тастатура се чита бројот на студенти, потоа бројот на курсеви. Потоа се внесуваат курсевите
и студентите, притоа за секој студент се читаат и кодовите на курсевите кои ги слуша.*/

#include <iostream>
using namespace std;

struct Course {
 char name[100];
 int code, n_of_students;

 void read_c() {
  cin >> name >> code;
  n_of_students = 0;
 }
};

struct Student {
 char ime[20];
 int indeks, n_of_courses;
 int course_codes[10];

 void read_s() {
  cin >> ime >> indeks >> n_of_courses;
 }
};

int get_most_popular_course(Course courses[], int n_of_courses) {
 int max_students = 0;
 int most_popular_course_code = -1;

 for (int i = 0; i < n_of_courses; i++) {
  if (courses[i].n_of_students > max_students) {
   max_students = courses[i].n_of_students;
   most_popular_course_code = courses[i].code;
  }
 }

 return most_popular_course_code;
}

int main() {
 int br_studenti, br_kursevi;
 Course kursevi[20];
 Student student[200];
 cin >> br_studenti >> br_kursevi;
 for (int i = 0; i < br_kursevi; ++i) {
  kursevi[i].read_c();
 }
 for (int i = 0; i < br_studenti; ++i) {
  student[i].read_s();
  for (int j = 0; j < student[i].n_of_courses; ++j) {
   int current_code;
   cin >> current_code;

   for (int k = 0; k < br_kursevi; k++) {
    if (kursevi[k].code == current_code) {
     kursevi[k].n_of_students++;
     break;
    }
   }
  }
 }
 int baran_kod = get_most_popular_course(kursevi, br_kursevi);
 for (int i = 0; i < br_kursevi; ++i) {
  if (kursevi[i].code == baran_kod) {
   cout << "Najpopularen kurs e: " << kursevi[i].name << endl;
   break;
  }
 }
 return 0;
}