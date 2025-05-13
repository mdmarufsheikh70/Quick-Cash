#include <bits/stdc++.h>
#include "picosha2.h"
#include "BigInt.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

class Account
{
public:
    string phone;
    string pin;
    BigInt balance;

    Account(string p, string hashed_pin)
    {
        phone = p;
        pin = hashed_pin;
        balance = BigInt("0");
    }

    bool check_pin(const string &input_pin)
    {
        string temp = input_pin;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        string salted = "QC_SALT_" + temp;
        return pin == picosha2::hash256_hex_string(salted);
    }

};

class QuickCash
{
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
    void MobileRecharge(Account &user);
    void Payment(Account &user);
    void MyQuickCash(Account &user);
    void log_out();

    bool is_valid_pin(const string &pin)
    {
        if (pin.length() != 5)
        {
            return false;
        }

        for (char c : pin)
        {
            if (!isdigit(c))
            {
                return false;
            }

        }
        return true;
    }

    string hash_pin(const string &pin)
    {
        string temp = pin;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        string salted = "QC_SALT_" + temp;
        return picosha2::hash256_hex_string(salted);
    }


    void save_accounts_to_file()
    {
    // Backup first
        ifstream src("data.csv", ios::binary);
        ofstream backup("backup.csv", ios::binary);
        if (src && backup) {
            backup << src.rdbuf();
        }
        src.close();
        backup.close();

        ofstream file("data.csv");
        if (file.is_open())
        {
            for (const Account &acc : accounts)
            {
                file << acc.phone << "," << acc.pin << "," << acc.balance.number << endl;
            }
        file.close();
        }
    else
        {
            cout << "Error: Unable to open file for writing.\n";
        }
    }


    void load_accounts_from_file()
    {
        ifstream file("data.csv");

        if (!file.is_open())
        {
            cout << "Error: Couldn't open data.csv file." << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string phone, pin, balance_str;

            getline(ss, phone, ',');
            getline(ss, pin, ',');
            getline(ss, balance_str, ',');

            if (phone.empty() || pin.empty() || balance_str.empty())
            {
                cout << "Skipping invalid line: " << line << endl;
                continue;
            }

            Account acc(phone, pin);

            try
            {
                acc.balance = BigInt(balance_str);
            }
            catch (...)
            {
                cout << "Invalid balance for phone " << phone << ", setting balance to 0." << endl;
                acc.balance = BigInt("0");
            }

            accounts.push_back(acc);
        }

        file.close();
    }



    void GP(Account &user);
    void Robi(Account &user);
    void Airtel(Account &user);
    void Teletalk(Account &user);
    void Banglalink(Account &user);



    void pin_reset(Account &user);
    void check_balance(Account &user);
    void account_deletion(Account &user);
    void customer_support(Account &user);
};

void QuickCash ::mainMenu()
{
    while (true)
    {
        int choice;
        cout << "\n=== Main Menu ===\n";
        cout << "1. SignUp" << endl;
        cout << "2. SignIn" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Numbers only: ";
        }
        
        switch (choice)
        {
        case 1:
            SignUp();
            break;
        case 2:
            SignIn();
            break;
        case 3:
            Exit();
        default:
            cout << "Invalid choice, try again!\n";
        }
    }
}

void QuickCash::display()
{
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "                                                                     Welcome to quick cash" << endl;
    cout << "                                                                   -------------------------" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                  | 1          2          3 |" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                  | 4          5          6 |" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                  | 7          8          9 |" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                  | *          0          # |" << endl;
    cout << "                                                                  |                         |" << endl;
    cout << "                                                                   -------------------------" << endl;
    string n;
    cout << "                                                                     Dial USSD code:";
    cin >> n;
    if (n == "*147#")
    {
        cout << endl;
        mainMenu();
        cout << endl;
    }
    else
    {
        cout << "=== Invalid USSD ===";
    }
}

void QuickCash::SignUp()
{
    string phone, pin;
    cout << "Enter Phone Number: ";
    cin >> phone;
    while (phone.length() != 11 || phone.substr(0, 2) != "01") 
    {
        cout << "Invalid Bangladeshi phone number! Try again: ";
        cin >> phone;
    }

    for (auto &acc : accounts)
    {
        if (acc.phone == phone)
        {
            cout << endl;
            cout << "Phone Number already registered! try diffrent number!\n\n";
            SignUp();
            return;
        }
    }

    cout << "Enter a 5-digit PIN: ";
    cin >> pin;

    while (!is_valid_pin(pin))
    {
        cout << "Invalid PIN! Please enter exactly 5 digits: ";
        cin >> pin;
    }

    string hashed = hash_pin(pin);
    Account user(phone, hashed);
    user.balance = BigInt("100");
    accounts.push_back(user);
    save_accounts_to_file();
    cout << endl;
    cout << "Account Created Successfully!\n";
}

void QuickCash::SignIn()
{
    string phone, pin;
    cout << "Enter Phone Number: ";
    cin >> phone;

    for (auto &acc : accounts)
    {
        if (acc.phone == phone)
        {
            int chance = 5;
            while (chance > 0)
            {
                cout << "Enter a 5-digit PIN: ";
                cin >> pin;

                if (acc.check_pin(pin))
                {
                    cout << "\nSign In Successful!\n";
                    userMenu(acc);
                    return;
                }
                else
                {
                    chance--;
                    cout << "Wrong password! ";
                    if (chance > 0)
                        cout << "Tries left: " << chance << endl;
                    else
                        cout << "\nNo more tries left. Access denied.\n";
                }
            }
            return;
        }
    }

    cout << "\nInvalid Account! Enter valid number\n";
    SignIn();
}

void QuickCash::Exit()
{
    cout << endl;
    cout << "Thank you for being with Quick Cash\n";
    cout << endl;
    exit(0);
}

void QuickCash::sendMoney(Account &user)
{
    string phone;
    BigInt amount;
    cout << "Enter Recipient Phone: ";
    cin >> phone;

    if (user.phone == phone)
    {
        cout << "\nYou cannot send money to yourself!\n\nWhat you want?\n";
        cout << "1. Cash In(Bank)" << endl;
        cout << "2. Send Money" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cashIn(user);
            userMenu(user);
        case 2:
            sendMoney(user);
            userMenu(user);
        case 3:
            Exit();
            break;
        default:
            userMenu(user);
        }
    }

    for (auto &acc : accounts)
    {
        if (acc.phone == phone)
        {
            cout << "Enter Amount: ";
            cin >> amount.number;
            if (user.balance >= amount)
            {
                user.balance -= amount;
                acc.balance += amount;
                save_accounts_to_file();
                cout << endl;
                cout << "Money Sent Successfully!\n";
            }
            else
            {
                cout << endl;
                cout << "Insufficient Balance!\n";
            }
            return;
        }
    }
    cout << endl;
    cout << "Recipient Not Found!\n\n";
    sendMoney(user);
}

void QuickCash::cashIn(Account &user)
{
    BigInt bank_account;
    BigInt  bank_password;
    BigInt otp;
    cout << "Enter Bank account number: ";
    cin >> bank_account.number;
    cout << "Enter password: ";
    cin >> bank_password.number;
    cout << "Enter 6 digit OTP: ";
    cin >> otp.number;
    if (otp.number.length() == 6) {
        BigInt amount;
        cout << "Enter Amount to Cash In: ";
        cin >> amount.number;

    while (amount <= BigInt("0"))
    {
        cout << "\nInvalid amount!\n\nPlease enter a positive amount: ";
        cin >> amount.number;
        // return;
    }

        user.balance += amount;
        cout << endl;
        cout << "Cash In Successful! New Balance: " << user.balance.number << " TK\n";
        save_accounts_to_file();
    } else {
        cout << "\nInvalid OTP! Please enter exactly 6 digits OTP: \n\n" << endl;
        cashIn(user);
    }
    
}

void QuickCash::cashOut(Account &user)
{
    string phone_number;
    BigInt amount;

    cout << "Enter Quick Cash Agent number: ";
    cin >> phone_number;
    cin.ignore();

    cout << "Enter Amount to Cash Out: ";
    cin >> amount.number;
    cin.ignore();

    if (amount <= BigInt("0"))
    {
        cout << "\nInvalid amount!\n";
        return;
    }

    if (user.balance >= amount)
    {
        user.balance -= amount;
        cout << "\nCash Out Successful!\n";
        cout << "Agent No: " << phone_number << "\n";
        cout << "Amount: " << amount.number << " TK\n";
        save_accounts_to_file();
    }
    else
    {
        cout << "\nInsufficient Balance!\n";
    }
}



void QuickCash::GP(Account &user) {
    string phone;
    BigInt amount;

    cout << "Enter Grameenphone  number: ";
    cin >> phone;

    
        if (phone[0] == '0'&& phone[1] == '1' && phone[2] == '7'&& phone.length()==11)
        {
            cout << "Enter Recharge Amount: ";
            cin >> amount.number;
            if (user.balance >= amount)
            {
                user.balance -= amount;
                save_accounts_to_file();
                cout << endl;
                cout << "Mobile reacharge Successfully!\n";
            }
            else
            {
                cout << endl;
                cout << "Insufficient Balance!\n";
            }
            return;
        }
    
    cout << endl;
    cout << "Invaild Grameenphone number!";
    cout << endl;
    userMenu(user);
}



void QuickCash::Robi(Account &user) {
    string phone;
    BigInt amount;

    cout << "Enter Robi  number: ";
    cin >> phone;

    
        if (phone[0] == '0'&& phone[1] == '1' && phone[2] == '8'&& phone.length()==11)
        {
            cout << "Enter Recharge Amount: ";
            cin >> amount.number;
            if (user.balance >= amount)
            {
                user.balance -= amount;
                save_accounts_to_file();
                cout << endl;
                cout << "Mobile recharge Successfully!\n";
            }
            else
            {
                cout << endl;
                cout << "Insufficient Balance!\n";
            }
            return;
        }
    
    cout << endl;
    cout << "Invaild Robi number!";
    cout << endl;
    userMenu(user);
}



void QuickCash::Airtel(Account &user) {
    string phone;
    BigInt amount;

    cout << "Enter Airtel  number: ";
    cin >> phone;

    
        if (phone[0] == '0'&& phone[1] == '1' && phone[2] == '6'&& phone.length()==11)
        {
            cout << "Enter Recharge Amount: ";
            cin >> amount.number;
            
            if (user.balance >= amount)
            {
                user.balance -= amount;
                save_accounts_to_file();
                cout << endl;
                cout << "Mobile recharge Successfully!\n";
            }
            else
            {
                cout << endl;
                cout << "Insufficient Balance!\n";
            }
            return;
        }
    
    cout << endl;
    cout << "Invaild Airtel number!";
    cout << endl;
    userMenu(user);
}



void QuickCash::Teletalk(Account &user) {
    string phone;
    BigInt amount;

    cout << "Enter Teletalk  number: ";
    cin >> phone;

    
        if (phone[0] == '0'&& phone[1] == '1' && phone[2] == '5'&& phone.length()==11)
        {
            cout << "Enter Recharge Amount: ";
            cin >> amount.number;
            if (user.balance >= amount)
            {
                user.balance -= amount;
                save_accounts_to_file();
                cout << endl;
                cout << "Mobile recharge Successfully!\n";
            }
            else
            {
                cout << endl;
                cout << "Insufficient Balance!\n";
            }
            return;
        }
    
    cout << endl;
    cout << "Invaild Teletalk number!";
    cout << endl;
    userMenu(user);
}



void QuickCash::Banglalink(Account &user) {
    string phone;
    BigInt amount;

    cout << "Enter Banglalink  number: ";
    cin >> phone;

    
        if (phone[0] == '0'&& phone[1] == '1' && phone[2] == '9'&& phone.length()==11)
        {
            cout << "Enter Recharge Amount: ";
            cin >> amount.number;

            if (user.balance >= amount)
            {
                user.balance -= amount;
                save_accounts_to_file();
                cout << endl;
                cout << "Mobile recharge Successfully!\n";
            }
            else
            {
                cout << endl;
                cout << "Insufficient Balance!\n";
            }
            return;
        }
    
    cout << endl;
    cout << "Invaild Banglalink number!";
    cout << endl;
    userMenu(user);
}



void QuickCash::MobileRecharge(Account &user)
{

    cout << "1. GP" << endl;
    cout << "2. Robi" << endl;
    cout << "3. Airtel" << endl;
    cout << "4. Teletalk" << endl;
    cout << "5. Banglalink" << endl;
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        GP(user);
        userMenu(user);
        break;
    case 2:
        Robi(user);
        userMenu(user);
        break;
    case 3:
        Airtel(user);
        userMenu(user);
        break;
    case 4:
        Teletalk(user);
        userMenu(user);
        break;
    case 5:
        Banglalink(user);
        userMenu(user);
        break;
    default:
        userMenu(user);
        break;
    }
}



void QuickCash::Payment(Account &user)
{
    string phone_number;
    BigInt amount;

    cout << "Enter Merchantile QC account number: ";
    cin >> phone_number;
    cin.ignore();

    cout << "Enter Amount: ";
    cin >> amount.number;
    cin.ignore();

    if (amount <= BigInt("0")) {
        cout << "\nInvalid amount!\n";
        return;
    }

    if (user.balance >= amount) {
        user.balance -= amount;
        cout << "\nPayment Successful!\n";
        cout << "Merchantile No: " << phone_number << "\n";
        cout << "Amount: " << amount.number << " TK\n";
        save_accounts_to_file();
    }
    else {
        cout << "\nInsufficient Balance!" << endl;
    }
    userMenu(user);
}



void QuickCash::pin_reset(Account &user){
    string current_pin;
    string new_pin;
    string verify_new_pin;

    cout << "Enter current pin: ";
    cin >> current_pin;
    cin.ignore();

    if(hash_pin(current_pin) == user.pin) {

        while (1) {

            cout << "Enter a 5-digit new PIN: ";
            cin >> new_pin;
        
            while (!is_valid_pin(new_pin))
            {
                cout << "Invalid PIN! Please enter exactly 5 digits: ";
                cin >> new_pin;
            }
    
            cin.ignore();

            cout << "Enter new pin again: ";
            cin >> verify_new_pin;
    
            if(new_pin == verify_new_pin){

                user.pin = hash_pin(new_pin);
    
                cout << "\nPin Reset successful!" << endl;
                save_accounts_to_file();
                return;
            }
            else {
                cout << "PIN Not Matching!" <<endl;
                
            }
        }
    }
    else {
        cout << " Invalid PIN!" << endl;
        pin_reset(user);
    }

}



void QuickCash::check_balance(Account &user) {
    cout << "\n!Your current Balance: " << user.balance << "Tk" << endl;
    userMenu(user);
}



void QuickCash::account_deletion(Account &user) {
    cout << "Are you sure Y/N: " << endl;
    string decision;
    cin >> decision;
    if(decision == "Y") {
        for (size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i].phone == user.phone) {
                accounts.erase(accounts.begin() + i);
                save_accounts_to_file();
                cout << "\nAccount deleted successfully!\n";
                return; 
            }
        }
        cout << "\nAccount not found!\n";
    }
    else {
        cout<<"\nOkay!" << endl;
    }
    
}



void QuickCash::customer_support(Account &user) {
    cout << "\n       === Customer Support ===\n";
    cout << "Please, Write your objection or any issue: ";
    string objection;
    cin.ignore();
    getline(cin, objection);
    cout<<"\n!we are recieved a messege from account number "<<user.phone<<endl;
    cout << "      Thank you for being with Quick Cash\n"<< endl;
    userMenu(user);
}



void QuickCash::MyQuickCash(Account &user)
{
    cout << "1. Pin Reset" << endl;
    cout << "2. Check Balance" << endl;
    cout << "3. Account Deletion" << endl;
    cout << "4. Customer sopport" << endl;
    cout << "5. Exit" <<endl;
    cout << "Enter your choice: ";
    
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        pin_reset(user);
        userMenu(user);
        break;
    case 2:
        check_balance(user);
        userMenu(user);
        break;
    case 3:
        account_deletion(user);
        mainMenu();
        break;
    case 4:
        customer_support(user);
        userMenu(user);
        break;
    case 5:
        Exit();
        userMenu(user);
        break;
    default:
        userMenu(user);
        break;
    }
}



void QuickCash::log_out()
{
    mainMenu();
}



void QuickCash::userMenu(Account &user)
{
    while (true)
    {
        int choice;
        cout << "\n=== User Menu ===\n";
        cout << "1. Send Money" << endl;
        cout << "2. Cash Out" << endl;
        cout << "3. Cash In (Bank)" << endl;
        cout << "4. MobileRecharge " << endl;
        cout << "5. Payment" << endl;
        cout << "6. My Quick Cash" << endl;
        cout << "7. Log Out" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            sendMoney(user);
            break;
        case 2:
            cashOut(user);
            break;
        case 3:
            cashIn(user);
            break;
        case 4:
            MobileRecharge(user);
            break;
        case 5:
            Payment(user);
            break;
        case 6:
            MyQuickCash(user);
            break;
        case 7:
            log_out();
        default:
            cout << "Invalid choice, try again!\n";
            mainMenu();
        }
    }
}


int main() {
    QuickCash System;
    System.load_accounts_from_file();
    System.display();
    return 0;
}
