/* Да се дефинира апстрактна класа QuizAttempt (ID).
Класата содржи чисто виртуелни функции score() и print(), што ја прави апстрактна.
Од неа се изведуваат:
1. MCQuizAttempt (Multiple Choice) - точен одговор носи 1 поен, неточен -0.25.
2. TFQuizAttempt (True/False) - точен одговор носи 1 поен, неточен -0.50.
Да се имплементира глобална функција за пресметка на просек на сите кои положиле (score > 5). */

#include <iostream>
#include <cstring>
using namespace std;

 class QuizAttempt{
  protected:
    char id[7];

    public:
      QuizAttempt(char *id="") {
        strcpy(this->id, id);
      }
      QuizAttempt(const QuizAttempt &n) {
        strcpy(this->id, n.id);
      }
      QuizAttempt &operator=(const QuizAttempt &n) {
        if(this != &n) {
          strcpy(this->id, n.id);
        }
        return *this;
      }
    virtual double score() = 0; // Чисто виртуелна функција
    virtual void print() = 0;
    bool  operator>=( QuizAttempt &n) {
      return this->score()>=n.score();
    }
 };

 class MCQuizAttempt : public QuizAttempt {
   private:
     char correctAnswers[11];
     char studentAnswers[11];
     public:
       MCQuizAttempt(char *id,char *correctAnswers,char *studentAnswers)
           :QuizAttempt(id)
     {
         strcpy(this->correctAnswers,correctAnswers);
         strcpy(this->studentAnswers,studentAnswers);
       }

       double score()  override{
         double suma=0;
         for(int i=0;i<10;i++){
           if(correctAnswers[i]==studentAnswers[i]){
             suma+=1;
           }
           else suma-=0.25;
         }
         return suma;
       }
     void print()  override{
           for(int i=0;i<10;i++){
               cout<<i+1<<". Correct: "<<correctAnswers[i];
               cout<<" Answer: "<<studentAnswers[i];
               cout<<" Points: ";
               if(correctAnswers[i]==studentAnswers[i]){
                   cout<<"1"<<endl;
               }
               else cout<<"-0.25"<<endl;
           }
           cout<<"Total score: "<<score()<<endl;
       }

 };

 class TFQuizAttempt : public QuizAttempt {
 private:
     bool correctAnswers[11];
     bool studentAnswers[11];
 public:
       TFQuizAttempt(char *id,bool *correctAnswers,bool *studentAnswers) {
         strcpy(this->id,id);
         for(int i=0;i<10;i++){
           this->correctAnswers[i] = correctAnswers[i];
           this->studentAnswers[i] = studentAnswers[i];
         }
       }

     double score()  override{
           double suma=0;
           for(int i=0;i<10;i++){
               if(correctAnswers[i]==studentAnswers[i]){
                   suma+=1;
               }
               else suma-=0.50;
           }
           return suma;
       }
       void print()  override{
         for(int i=0;i<10;i++){
           cout<<i+1<<". Correct: "<<correctAnswers[i];
           cout<<" Answer: "<<studentAnswers[i];
          cout<<" Points: ";
          if(correctAnswers[i]==studentAnswers[i]){
            cout<<"1"<<endl;
          }
          else cout<<"-0.50"<<endl;
         }
         cout<<"Total score: "<<score()<<endl;
       }
 };

 double averagePointsOfPassedStudents (QuizAttempt ** attempts, int n){
    int polozheni=0;
    double suma=0;
    for(int i=0;i<n;i++){
      if(attempts[i]->score()>5){
        polozheni++;     suma+=attempts[i]->score();
      }
    }
    return (polozheni > 0) ? (suma/polozheni) : 0;
 }

 QuizAttempt *readMCQuizAttempt() {
     char ID[7];
     char correct[11];
     char answers[11];
     cin >> ID >> correct >> answers;
     return new MCQuizAttempt(ID, correct, answers);
 }

 QuizAttempt *readTFQuizAttempt() {
     char ID[7];
     bool correct[10];
     bool answers[10];
     cin >> ID;
     for (int i = 0; i < 10; i++) cin >> correct[i];
     for (int i = 0; i < 10; i++) cin >> answers[i];
     return new TFQuizAttempt(ID, correct, answers);
 }

 int main() {
     int testCase;
     cin >> testCase;

     if (testCase == 1) {
         cout << "Test MCQuizAttempt" << endl;
         QuizAttempt *attempt = readMCQuizAttempt();
         cout << "Score: " << attempt->score() << endl;
         attempt->print();
     } else if (testCase == 2) {
         cout << "Test TFQuizAttempt" << endl;
         QuizAttempt *attempt = readTFQuizAttempt();
         cout << "Score: " << attempt->score() << endl;
         attempt->print();
     } else if (testCase == 3) {
         cout << "Test operator >=" << endl;
         int n;
         cin >> n;
         QuizAttempt **attempts = new QuizAttempt *[n];
         for (int i = 0; i < n; i++) {
             int type;
             cin >> type;
             if (type == 1) attempts[i] = readMCQuizAttempt();
             else attempts[i] = readTFQuizAttempt();
         }

         for (int i = 0; i < n; i++) {
             for (int j = 0; j < n; j++) {
                 if (i != j) {
                     if ((*attempts[i]) >= (*attempts[j])) cout << i << " >= " << j << endl;
                     else cout << i << " < " << j << endl;
                 }
             }
         }
     } else {
         int n;
         cin >> n;
         QuizAttempt **attempts = new QuizAttempt *[n];
         for (int i = 0; i < n; i++) {
             int type;
             cin >> type;
             if (type == 1) attempts[i] = readMCQuizAttempt();
             else attempts[i] = readTFQuizAttempt();
             attempts[i]->print();
             cout << endl;
         }
         cout << "Average score of passed students is: " << averagePointsOfPassedStudents(attempts, n) << endl;
     }
     return 0;
 }