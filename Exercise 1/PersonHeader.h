#include <string>
#include <iostream>
using namespace std;

class Person
{
    private:
        string name;
        unsigned short age = 0;
        float balance;
        string place_of_birth;
        string password;
        string transactions = "";
        int lineIndex;
    public:
        Person(string name,unsigned short age, float balance,string place_of_birth, string password, string transactions);
        Person(string name,unsigned short age, float balance,string place_of_birth, string password, string transactions,int lineIndex);
        Person(string name,unsigned short age, float balance,string place_of_birth, string password);
        Person(string name,unsigned short age, float balance,string place_of_birth, string password,int lineIndex);
        Person();
        void setTransaction(const string& value);
        string getName();
        string toString();
        unsigned short getAge();

        float getBalance();
        int getLineIndex();

        string getPlaceOfBirth();

        string getPassword();

        string getTransactions();


};