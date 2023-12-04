#include "PersonHeader.h"

Person::Person(string name,unsigned short age, float balance,string place_of_birth, string password, string transactions,int lineIndex)
{
    this->name = name;
    this->age = age;
    this->balance = balance;
    this->password = password;
    this->place_of_birth = place_of_birth;
    this->transactions = transactions;
    this->lineIndex = lineIndex;
}

Person::Person(string name,unsigned short age, float balance,string place_of_birth, string password, string transactions)
{
    this->name = name;
    this->age = age;
    this->balance = balance;
    this->password = password;
    this->place_of_birth = place_of_birth;
    this->transactions = transactions;
}

Person::Person(string name,unsigned short age, float balance,string place_of_birth, string password)
{
    this->name = name;
    this->age = age;
    this->balance = balance;
    this->password = password;
    this->place_of_birth = place_of_birth;
    this->transactions = "";
}

Person::Person(string name,unsigned short age, float balance,string place_of_birth, string password,int lineIndex)
{
    this->name = name;
    this->age = age;
    this->balance = balance;
    this->password = password;
    this->place_of_birth = place_of_birth;
    this->transactions = "";
    this->lineIndex = lineIndex;
}

Person::Person()
{
    
}
int Person::getLineIndex()
{
    return lineIndex;
}

string Person::toString() {
    return  name + "," + std::to_string(age) + "," + std::to_string(balance) + "," + place_of_birth + "," + password + "," + transactions;
}


void Person::setTransaction(const string& value) {
    transactions = value;
}

string Person::getName() {
    return name;
}

unsigned short Person::getAge() {
    return age;
}

float Person::getBalance() {
    return balance;
}

string Person::getPlaceOfBirth() {
    return place_of_birth;
}

string Person::getPassword() {
    return password;
}

string Person::getTransactions() {
    return transactions;
}