  using namespace std;
  #include <iostream>
  #include <cstring>
  class Date;
  class SMS;
  class Date {
  private:
      friend SMS;
      int year;
      int month;
      int day;
      public:
      Date(){}
      Date(int year, int month, int day) {
          this->year = year;
          this->month = month;
          this->day = day;
      }

      ~Date(){}
      void print() {
          cout << year << "/" << month << "/" << day << endl;
      }
  };
  class SMS {
      friend Date;
      friend void povolni (SMS *sms,int n,Date finale);
      Date datum;
      char content[50];
      char sender[50];
      char receiver[50];
      public:
   bool datebefore(Date m) {
       if (datum.year<m.year) {
           return true;
       }
       else if ( datum.year>m.year){
           return false;
       }
       else {
           if (datum.month<m.month) {
               return true;
           }
           else if ( datum.month>m.month) {
               return false;
           }
           else {
               if (datum.day<m.day) {
                   return true;
               }
               else if ( datum.day>=m.day) {
                   return false;
               }
           }
       }
       return false;
   };
   void print() {
       datum.print();
       cout << sender << " " << receiver << " " << content;
   }



  };

  void povolni(SMS *sms,int n,Date finale) {
          for(int i=0;i<n;i++) {
              if (sms[i].datebefore(finale) && (strlen(sms[i].content)<70)) {
                  sms[i].print();
              }
          }
  }
  int main() {
      int n;
      char content[50];
      char sender[50];
      char receiver[50];
      int year;
      int month;
      int day;
      Date finale;
      cin>>n;
      SMS sms[n];
      for (int i = 0; i < n; i++) {
          cin>>day>>month>>year>>sender>>receiver;
          cin.ignore();
          cin.getline(content,50);
      }
      cin>>day>>month>>year;
      finale=Date(year,month,day);
       povolni(sms, n, finale) ;
  }