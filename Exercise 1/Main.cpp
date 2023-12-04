#include "Person.cpp"
using namespace std;
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

Person* currentPerson = nullptr;

void PrintSeparator() {
    cout << "\033[0m-----------------------------------------\033[0m" << endl;
}

void DisplayTransaction(Person* p) {
    PrintSeparator();
    cout << "\033[96m💹 Your Recent Transactions 💹\033[0m" << endl;

    string* transactions = new string(p->getTransactions());
    istringstream* ss = new istringstream(*transactions);
    string* transaction = new string();
    vector<string>* transactionList = new vector<string>();

    cout << "\033[96m";
    if(transactionList->size() > 0) {
        cout << "Here are your recent transactions:\n";
        int* max = new int(3);
        istringstream* iss = new istringstream();
        string* name = new string();
        double* amount = new double();

        for (auto it = transactionList->rbegin(); it != transactionList->rend(); ++it) {
            if (*max == 0) {
                break;
            }

            iss->clear();
            iss->str(*it);
            
            getline(*iss, *name, ':');
            *iss >> *amount;

            if (*amount < 0) {
                cout << "- To " << *name << ", you paid $" << fixed << setprecision(2) << -*amount << endl;
            } else {
                cout << "- From " << *name << ", you received $" << fixed << setprecision(2) << *amount << endl;
            }
            (*max)--;
        }

        delete iss;
        delete name;
        delete amount;
    } else {
        cout << "Your transaction history is empty." << endl;
    }
    cout << "\033[0m";

    delete transactions;
    delete ss;
    delete transaction;
    delete transactionList;
}



Person*  GetUser(string* name, string* password)
{
    ifstream*file = new ifstream("Users.txt");
    string* line = new string();

    int* userLineIndex = new int(0);
    vector<string>* fields = new vector<string>();
    stringstream* ss = new stringstream();
    string* field = new string();
    unsigned short* age = new  unsigned short();
    double* balance = new double();
    string* transactions = new string("");
    Person* outPerson = new Person();
    bool* completed = new bool(false);
    while (getline(*file, *line)) 
    {
        ss = new stringstream(*line);
        field = new string();
        fields = new vector<string>();


    
        while (getline(*ss, *field, ',')) {
            fields->push_back(*field);
        }
        //cout << fields[4];
        if (fields->size() >= 5 && (*fields)[0] == *name && (*fields)[4] == *password) {
            age = new  unsigned short(stoi((*fields)[1]));
            balance = new double(stod((*fields)[2]));
            if(fields->size() == 5)
            {
                *outPerson =  Person((*fields)[0], *age, *balance, (*fields)[3], (*fields)[4], *userLineIndex);
                *completed = true;
                break;
            }
            transactions = new string((*fields)[5]);
            *outPerson = Person((*fields)[0], *age, *balance, (*fields)[3], (*fields)[4], *transactions, *userLineIndex);
            *completed = true;
            break;
        }

        (*userLineIndex)++;

    }

    delete ss;
    delete field;
    delete fields;
    delete age;
    delete balance;
    //cout << "Password or Username Incorrect. " <<endl;
    delete file;
    delete line;
    delete userLineIndex;


    if(*completed == true){
        cout << "Correct Details. " <<endl;
        delete completed;
        return outPerson;
    }
    else{
        cout << "Password or Username Incorrect. " <<endl;
        delete outPerson;
        delete completed;
        return nullptr;
    }
}

void UpdateFile(Person* person) {
    PrintSeparator();
    cout << "\033[95mUpdating file...\033[0m" << endl;
    cout << person->toString() << endl;
    
    int* lineIndex = new int(person->getLineIndex());
    ifstream* fileIn = new ifstream("Users.txt");
    vector<std::string>* lines = new vector<string>();
    string* line = new string();

    while (getline(*fileIn, *line)) {
        lines->push_back(*line);
    }
    fileIn->close();


    
    if (*lineIndex >= 0 && *lineIndex < lines->size()) {
        (*lines)[*lineIndex] = person->toString();
    }
    ofstream* fileOut = new ofstream("Users.txt");
    for (const auto& ln : *lines) {
        *fileOut << ln << std::endl;
    }
    
    delete fileIn;
    delete fileOut;
    delete lines;
    delete line;
    delete lineIndex;

}

void Login() {
    PrintSeparator();
    cout << "\n🔐 \033[96mLogin\033[0m 🔐" << endl;

    string* name = new string();
    string* password = new string();

    cout << "\n👤 \033[96mName\033[0m: ";
    cin >> *name;
    cout << "🔑 \033[96mPassword\033[0m: ";
    cin >> *password;

    Person* user = GetUser(name, password);
    if (currentPerson != nullptr && user != currentPerson) {
        delete currentPerson;
    }
    currentPerson = user;

    if (currentPerson != nullptr) {
        cout << "\n🎉 \033[95mWelcome, " << currentPerson->getName() << "!\033[0m" << endl;
        cout << "📅 Your age is: " << currentPerson->getAge() << endl;
        cout << "📍 Born in: " << currentPerson->getPlaceOfBirth() << endl;
        cout << "💰 Your balance is: $" << fixed << setprecision(2) << currentPerson->getBalance() << endl;
        
        cout << "\n🔄 Displaying recent transactions..." << endl;
        DisplayTransaction(currentPerson);
    } else {
        cout << "\n❌ \033[31mLogin failed. Username or password is incorrect.\033[0m" << endl;
    }
    
    delete name;
    delete password;
}



void AddTransaction(string& transactions) {
    PrintSeparator();
    cout << "\033[32m💰 Add Transactions 💰\033[0m" << endl;

    int* choice = new int(0);
    int* count = new int(0);
    string* name = new string();
    double* amount = new double();

    cout << "How many transactions would you like to input? ";
    cin >> *count;
    cin.ignore();

    while (*count > 0) {
        PrintSeparator();
        cout << "1 - \033[32mAdd Transaction\033[0m" << endl;
        cout << "2 - \033[32mExit\033[0m" << endl;
        cin >> *choice;

        if (*choice == 1) {
            cout << "Who is the other party? : ";
            cin.ignore();
            getline(cin, *name);
            cout << "What was the amount (Include minus in front if you paid): ";
            cin >> *amount;

            if (!transactions.empty()) {
                transactions += "|";
            }
            transactions += *name + ":" + to_string(*amount);
            (*count)--;

        } else if (*choice == 2) {
            cout << "\033[32mExiting transaction addition.\033[0m" << endl;
            break;
        } else {
            cout << "\033[32mInvalid choice. Try again.\033[0m" << endl;
        }
    }

    delete name;
    delete amount;
    delete choice;
    delete count;

    cout << "\033[32m✅ Transactions added successfully.\033[0m" << endl;
    PrintSeparator();
}




void Transaction() {
    if (currentPerson == nullptr) {
        cout << "\033[31m❗ Please login first.\033[0m" << endl;
        return;
    }
    PrintSeparator();
    cout << "\033[32m💸 Make a Transaction 💸\033[0m" << endl;
    string* transactions = new string(currentPerson->getTransactions());
    AddTransaction(*transactions);
    currentPerson->setTransaction(*transactions);
    UpdateFile(currentPerson);
    cout << "\033[32m✅ Transaction successfully recorded.\033[0m" << endl;
    delete transactions;
}



void Register() {
    PrintSeparator();
    cout << "\n📝 \033[33mRegister New Account\033[0m 📝" << endl;
    int* age = new int(0);
    string* transactions = new string();
    double* balance = new double();
    string* name = new string();
    string* placeOfBirth = new string();
    string* password = new string();

    cout << "\n👤 \033[33mName\033[0m: ";
    cin >> *name;
    cout << "🎂 \033[33mAge\033[0m: ";
    cin >> *age;
    cout << "💰 \033[33mBalance\033[0m: ";
    cin >> *balance;

    cin.ignore(1000, '\n');

    cout << "🌍 \033[33mPlace Of Birth\033[0m: ";
    getline(cin, *placeOfBirth);
    cout << "🔒 \033[33mPassword\033[0m: ";
    getline(cin, *password);

    ofstream file("Users.txt", ios::app);
    if (file.is_open()) {
        file << *name << "," << *age << "," << *balance << "," << *placeOfBirth << "," << *password << "," << *transactions << "\n";
        file.close();
        cout << "\n✅ \033[33mRegistration successful.\033[0m" << endl;
    } else {
        cerr << "\n❌ \033[31mUnable to open file.\033[0m" << endl;
    }

    delete age;
    delete transactions;
    delete balance;
    delete name;
    delete placeOfBirth;
    delete password;
}

// color stuff https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
void PrintHeader() {
    cout << "\033[36m" <<  
            "*****************************************\n"
            "*           😎 Bank App                 *\n"
            "*****************************************\n" 
         << "\033[0m"; 
}

void Options()
{
        PrintSeparator();
        cout << "\033[95m";
        cout << "\n📌 Main Menu 📌" << endl;
        cout << "1️⃣ - Login" << endl;
        cout << "2️⃣ - Register" << endl;
        cout << "3️⃣ - Make a Transaction" << endl;
        cout << "4️⃣ - Exit" << endl;
        cout << "\033[0m";
        PrintSeparator();
        cout << "Select an option: ";
}


int main() {
    PrintHeader();
    int* user_Input = new int(0);

    while (true) {
        Options();
        
        cin >> *user_Input;

        switch (*user_Input) {
            case 1:
                cout << "🔓 Logging in..." << endl;
                Login();
                break;
            case 2:
                cout << "📝 Registering a new account..." << endl;
                Register();
                break;
            case 3:
                cout << "💸 Processing a Transaction..." << endl;
                Transaction();
                break;
            case 4:
                cout << "👋 Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "❗ Invalid choice. Please try again." << endl;
                break;
        }

        if (*user_Input == 4) {
            break;
        }
    }
    PrintSeparator();
    cout << "\033[95m🌟 Thank you for using Bank App 🌟\033[0m" << endl;
    
    delete user_Input;
    delete currentPerson;
    return 0;
}