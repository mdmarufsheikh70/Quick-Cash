# 💸 QuickCash - C++ Mobile Banking Software

QuickCash is a mobile banking simulation system written in C++. It allows users to securely manage their funds with operations like Send Money, Cash In, Cash Out, Mobile Recharge, Payment, and more. Built with strong emphasis on security and data persistence using CSV file handling, hashing (picosha2), and BigInt arithmetic.

---

## 🚀 Features

- 📱 **User Authentication** with hashed PINs (using SHA-256 via `picosha2`)
- 💰 **Balance Handling** with custom `BigInt` class (supports large number operations)
- 💳 **Mobile Recharge** for GP, Robi, Airtel, Teletalk, and Banglalink
- 💸 **Send Money, Cash In, Cash Out, Merchant Payments**
- 🔒 **PIN Reset** with secure verification
- 🧾 **CSV-based File Storage** for account data persistence
- ☎️ **USSD-like Interface** (`*147#` simulation)
- 🇧🇩 Bangladeshi operator logic and phone validation

---

## 🧑‍💻 Tech Stack

- **C++**
- **picosha2** - SHA-256 hashing
- **BigInt** - Custom big integer handling class
- **File Handling** - CSV read/write for persistent storage

---

## 🛠 How It Works

1. **Launch the Program**  
   User dials `*147#` to start interacting with the QuickCash system.

2. **SignUp or SignIn**  
   New users create accounts, while existing users log in using their phone number and PIN.

3. **Secure PIN Verification**  
   All entered PINs are hashed before storage and compared securely.

4. **User Menu**  
   - Send Money
   - Cash In / Cash Out
   - Mobile Recharge (by operator)
   - Merchant Payments
   - Check Balance
   - PIN Reset / Account Deletion

5. **Data Persistence**  
   All operations are saved into a CSV file (`data.csv`) to maintain continuity between sessions.

---

## 📂 File Structure

```bash
QuickCash/
├── BigInt.hpp
├── picosha2.h
├── main.cpp
├── data.csv           # Stored account data
└── README.md
