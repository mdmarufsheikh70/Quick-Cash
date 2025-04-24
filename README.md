# 💸 QuickCash - Mobile Banking Software

QuickCash is a mobile banking simulation system written in C++. It allows users to securely manage their funds through operations like Send Money, Cash In, Cash Out, Mobile Recharge, Merchant Payment, and more. This project emphasizes security using SHA-256 hashing (`picosha2`), large number support through a custom `BigInt` class, and persistent storage via CSV file handling.

---

## 🚀 Features

- 📱 **USSD Simulation** – Start with `*147#` just like real mobile banking
- 🔐 **Secure Authentication** – PINs are hashed using SHA-256 (`picosha2`)
- 🧮 **Large Balance Support** – Handles large numbers using a custom `BigInt` class
- 💸 **Banking Operations** – Send Money, Cash In, Cash Out, Merchant Payment
- 📲 **Mobile Recharge** – For GP, Robi, Airtel, Teletalk, and Banglalink
- 🔄 **PIN Reset** – Reset your PIN securely with verification
- 🗃️ **CSV-based File Storage** – Stores phone, hashed PIN, and balance
- 🇧🇩 **Bangladeshi Operator Validation** – Accepts only valid BD phone numbers
- ⚙️ **Menu-Driven Interface** – Easy navigation and intuitive CLI

---

## 🧑‍💻 Tech Stack

- **C++**
- **picosha2** – For SHA-256 hashing
- **BigInt** – Custom implementation for large number support
- **File Handling** – CSV read/write for persistent storage

---

## 🛠 How It Works

1. **Launch the Program**  
   User dials `*147#` to begin using QuickCash.

2. **Sign Up / Sign In**  
   New users can register with phone number and PIN. Existing users sign in securely.

3. **PIN Security**  
   All PINs are hashed with SHA-256 before being stored or verified.

4. **Menu System**  
   After login, users can navigate through:
   - 💳 View Balance
   - 📤 Send Money
   - 📥 Cash In
   - 💵 Cash Out
   - 🧾 Merchant Payment
   - 🔄 Reset PIN
   - 📲 Mobile Recharge
   - ❌ Delete Account
   - 🚪 Log Out

5. **Persistent Data Storage**  
   All user data is stored in `data.csv`, including:
   - Phone number
   - Hashed PIN
   - Balance (as BigInt)

---

## ✅ All Features in QuickCash

### 1. USSD Simulation
- Simulates startup using `*147#`.

### 2. Account Management
- 🆕 **Sign Up** – Register using phone number and PIN
- 🔐 **Sign In** – Log in with phone number and PIN
- 🔄 **PIN Reset** – Reset your PIN if forgotten
- 🗑️ **Account Deletion** – Permanently remove your account

### 3. Authentication
- Uses SHA-256 hashing for PINs via `picosha2`
- PINs are never stored in plaintext

### 4. Balance Handling
- Custom `BigInt` class handles any size of balance
- Accurate arithmetic for send, receive, and comparison

### 5. Core Banking Operations
- **Send Money** to other users
- **Cash In** to your account
- **Cash Out** to withdraw funds
- **Merchant Payment** to any phone number

### 6. Mobile Recharge
Recharge for:
- Grameenphone (GP)
- Robi
- Airtel
- Teletalk
- Banglalink

### 7. Phone Number Validation
- Accepts only 11-digit Bangladeshi numbers with valid prefixes

### 8. CSV File Storage
- Stores data in `data.csv`:
  - Phone number
  - Hashed PIN
  - Balance

### 9. User Interface
- Menu-based CLI with simple navigation

### 10. Validation & Error Handling
- Duplicate phone check
- Balance checks before operations
- Valid phone number format enforcement
- Invalid menu selections and PIN rechecks

---

## 📂 File Structure
├── BigInt.hpp             
├── picosha2.h             
├── main.cpp               
├── data.csv               
├── README.md              
└── LICENSE                
