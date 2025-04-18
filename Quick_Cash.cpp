#include <bits/stdc++.h>
#include "picosha2.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string> 
using namespace std;



class Account {
    public:
        string phone;
        string pin;
        long long int balance;
    
        Account(string p, string hashed_pin) {
            phone = p;
            pin = hashed_pin;
            balance = 0;
        }
    
        bool check_pin(const string& input_pin) {
            return pin == picosha2::hash256_hex_string(input_pin);
        }
    };



class QuickCash {
private:
    vector<Account> accounts;
public:
    void mainMenu();
    void display();
    void SignUp();
    void SignIn();
    void Exit();
    void userMenu(Account &user);
    void sendMoney(Account &user);
    void cashIn(Account &user);
    void cashOut(Account &user);
    void MobileRecharge();
    void Payment();
    void MyQuickCash();
    void log_out();


 
    bool is_valid_pin(const string& pin) {
        if (pin.length() != 4) {
            return false;
        }

        for (char c : pin) {
        if (!isdigit(c)) {
            return false;
        }

        return true;
        }
    }
    
    string hash_pin(const string& pin) {
        return picosha2::hash256_hex_string(pin);
    }



    void save_accounts_to_file() {
        ofstream file("data.csv");
        if (file.is_open()) {
            for (const Account &acc : accounts) {
                file << acc.phone << "," << acc.pin << "," << acc.balance << endl;
            }
            file.close();
        } else {
            cout << "Error: Unable to open file for writing.\n";
        }
    }
    


    void load_accounts_from_file() {
        ifstream file("data.csv");
    
        if (!file.is_open()) {
            cout << "Error: Couldn't open data.csv file." << endl;
            return;
        }
    
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string phone, pin, balance_str;
    
            getline(ss, phone, ',');
            getline(ss, pin, ',');
            getline(ss, balance_str, ',');
    
            if (phone.empty() || pin.empty() || balance_str.empty()) {
                cout << "Skipping invalid line: " << line << endl;
                continue;
            }
    
            Account acc(phone, pin);
    
            try {
                acc.balance = stoi(balance_str);
            } catch (...) {
                cout << "Invalid balance for phone " << phone << ", setting balance to 0." << endl;
                acc.balance = 0;
            }
    
            accounts.push_back(acc);
        }
    
        file.close();
    }
};



void QuickCash :: mainMenu() {
    while (true) {
        int choice;
        cout << "\n=== Main Menu ===\n";
        cout << "1. SignUp"<<endl;
        cout << "2. SignIn"<<endl;
        cout << "3. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: SignUp();
            break;
            case 2: SignIn();
            break;
            case 3: Exit();
            default: cout << "Invalid choice, try again!\n";
        }
    }
}



void QuickCash:: display(){
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                                                                     Welcome to quick cash"         <<endl;
    cout<<"                                                                   -------------------------"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                  | 1          2          3 |"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                  | 4          5          6 |"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                  | 7          8          9 |"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                  | *          0          # |"<<endl;
    cout<<"                                                                  |                         |"<<endl;
    cout<<"                                                                   -------------------------"<<endl;
    string n;
    cout<<"                                                                     Dail USSD code:";cin>>n;
    if(n=="*147#"){
        cout<<endl;
        mainMenu();
        cout<<endl;
    }
    else{
        cout << "=== Invalid USSD ===";
    }
}



void QuickCash::SignUp() {
    string phone, pin;
    cout << "Enter Phone Number: ";
    cin >> phone;
    

    for (auto &acc : accounts) {
        if (acc.phone == phone) {
            cout << endl;
            cout << "Phone Number already registered! try diffrent number\n";
            SignUp();
            return;
        }
    }

    cout << "Enter a 4-digit PIN: ";
    cin >> pin;

    while (!is_valid_pin(pin)) {
        cout << "Invalid PIN! Please enter exactly 4 digits: ";
        cin >> pin;
    }

    string hashed = hash_pin(pin);
    Account user(phone, hashed);
    user.balance=100;    
    accounts.push_back(user);
    save_accounts_to_file();
    cout << endl;
    cout << "Account Created Successfully!\n";
}




void QuickCash::SignIn() {
    string phone, pin;
    cout << "Enter Phone Number: ";
    cin >> phone;

    for (auto &acc : accounts) {
        if (acc.phone == phone) {
            int chance = 5;
            while (chance > 0) {
                cout << "Enter a 4-digit PIN: ";
                cin >> pin;

                if (acc.check_pin(pin)) {
                    cout << "\nSign In Successful!\n";
                    userMenu(acc);
                    return;
                } else {
                    chance--;
                    cout << "Wrong password! ";
                    if (chance > 0)
                        cout << "Tries left: " << chance << endl;
                    else
                        cout << "No more tries left. Access denied.\n";
                }
            }
            return;
        }
    }

    cout << "\nInvalid Account! Enter valid number\n";
    SignIn();
}



void QuickCash::Exit(){
    cout<<endl;
    cout << "Thank you for being with Quick Cash\n";
    cout<<endl;
    exit(0); 
}



void QuickCash::sendMoney(Account &user) {
    string phone;
    int amount;
    cout << "Enter Recipient Phone: ";
    cin >> phone;

    if (user.phone == phone) {
        cout << "\nYou cannot send money to yourself!\n\nWhat you want?\n";
        cout << "1. Cash IN"<<endl;
        cout << "2. Send Money"<<endl;
        cout << "3. Exit"<<endl;
        cout<<"Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1: cashIn(user);  
            userMenu(user);
        case 2: sendMoney(user);
            userMenu(user);
        case 3: Exit();
            break;
        default: mainMenu();
            userMenu(user);
        }
    }

    for (auto &acc : accounts) {
        if (acc.phone == phone) {
            cout << "Enter Amount: ";
            cin >> amount;
            if (user.balance >= amount) {
                user.balance -= amount;
                acc.balance += amount;
                save_accounts_to_file();
                cout << endl;
                cout << "Money Sent Successfully!\n";
            } else {
                cout << endl;
                cout << "Insufficient Balance!\n";
            }
            return;
        }
    }
    cout << endl;
    cout << "Recipient Not Found!\n";
    sendMoney(user);
}



void QuickCash::cashIn(Account &user) {
    int amount;
    cout << "Enter Amount to Cash In: ";
    cin >> amount;

    while (amount <= 0) {
        cout << "\nInvalid amount!\n\nPlease enter a positive amount: ";
        cin >> amount;
        //return;
    }

    user.balance += amount;
    cout << endl;
    cout << "Cash In Successful! New Balance: " << user.balance << " TK\n";
    save_accounts_to_file();
}



void QuickCash::cashOut(Account &user) {
    string phone_number;
    long long int amount;
    
    cout << "Enter Quick Cash Agent number: ";
    cin >> phone_number;
    cin.ignore();

    cout << "Enter Amount to Cash Out: ";
    cin >> amount;
    cin.ignore();

    if (amount <= 0) {
        cout << "\nInvalid amount!\n";
        return;
    }

    if (user.balance >= amount) {
        user.balance -= amount;
        cout << "\nCash Out Successful!\n";
        cout << "Agent: " << phone_number << "\n";
        cout << "Amount: " << amount << " TK\n";
        save_accounts_to_file();
    } else {
        cout << "\nInsufficient Balance!\n";
    }
}




void QuickCash::MobileRecharge() {
    cout<<endl;
    cout << "Please Wait! the feature is Coming soon.\n";
}

void QuickCash::Payment() {
    cout<<endl;
    cout << "Please Wait! the feature is Coming soon.\n";
}

void QuickCash::MyQuickCash() {
    cout<<endl;
    cout << "Please Wait! the feature is Coming soon.\n";
}

void QuickCash::log_out() {
    mainMenu();
}

void QuickCash::userMenu(Account &user) {
    while (true) {
        int choice;
        cout << "\n=== User Menu ===\n";
        cout << "1. Send Money"<<endl;
        cout << "2. Cash IN"<<endl;
        cout << "3. Cash Out"<<endl;
        cout << "4. MobileRecharge "<<endl;
        cout << "5. Payment"<<endl;
        cout << "6. My Quick Cash"<<endl;
        cout << "7. Log Out"<<endl;
        cout<<"Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sendMoney(user);
            break;
            case 2: cashIn(user);
            break;
            case 3: cashOut(user);
            break;
            case 4: MobileRecharge();
            break;
            case 5: Payment();
            break;
            case 6: MyQuickCash();
            break;
            case 7: log_out();
            default: cout << "Invalid choice, try again!\n";
        }
    }
}



int main() {
    QuickCash system;
    system.load_accounts_from_file();
    system.display();
    return 0;
}