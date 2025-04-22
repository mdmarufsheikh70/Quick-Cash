#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class BigInt {
public:
    std::string number;

    // Constructors
    BigInt() : number("0") {}
    BigInt(const std::string& num) : number(num) { validateNumber(); }
    BigInt(const char* num) : number(num) { validateNumber(); }
    BigInt(long long num) : number(std::to_string(num)) {}

    // Validate input
    void validateNumber() {
        if (number.empty()) number = "0";
        if (number.find_first_not_of("0123456789") != std::string::npos)
            throw std::invalid_argument("Invalid number string");

        // Remove leading zeros
        size_t pos = number.find_first_not_of('0');
        number = (pos == std::string::npos) ? "0" : number.substr(pos);
    }

    // Comparison Operators
    bool operator<(const BigInt& other) const {
        if (number.size() != other.number.size())
            return number.size() < other.number.size();
        return number < other.number;
    }

    bool operator>(const BigInt& other) const { return other < *this; }
    bool operator<=(const BigInt& other) const { return !(*this > other); }
    bool operator>=(const BigInt& other) const { return !(*this < other); }
    bool operator==(const BigInt& other) const { return number == other.number; }
    bool operator!=(const BigInt& other) const { return !(*this == other); }

    // Arithmetic Operators
    BigInt operator+(const BigInt& other) const {
        std::string a = number;
        std::string b = other.number;
        std::string result = "";

        int carry = 0;
        int i = a.size() - 1, j = b.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int digitA = (i >= 0) ? a[i--] - '0' : 0;
            int digitB = (j >= 0) ? b[j--] - '0' : 0;
            int sum = digitA + digitB + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }

        std::reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator-(const BigInt& other) const {
        if (*this < other) throw std::invalid_argument("Negative result not supported");

        std::string a = number;
        std::string b = other.number;
        std::string result = "";

        int borrow = 0;
        int i = a.size() - 1, j = b.size() - 1;

        while (i >= 0) {
            int digitA = a[i--] - '0';
            int digitB = (j >= 0) ? b[j--] - '0' : 0;

            digitA -= borrow;
            if (digitA < digitB) {
                digitA += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back((digitA - digitB) + '0');
        }

        // Remove leading zeros
        while (result.size() > 1 && result.back() == '0') result.pop_back();
        std::reverse(result.begin(), result.end());
        return BigInt(result);
    }

    BigInt operator*(const BigInt& other) const {
        int n = number.size();
        int m = other.number.size();
        std::string result(n + m, '0');

        for (int i = n - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = m - 1; j >= 0; --j) {
                int sum = (result[i + j + 1] - '0') + (number[i] - '0') * (other.number[j] - '0') + carry;
                result[i + j + 1] = (sum % 10) + '0';
                carry = sum / 10;
            }
            result[i] += carry;
        }

        // Remove leading zeros
        size_t pos = result.find_first_not_of('0');
        if (pos != std::string::npos)
            return BigInt(result.substr(pos));
        return BigInt("0");
    }

    // Compound Assignment Operators
    BigInt& operator+=(const BigInt& other) {
        *this = *this + other;
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        *this = *this - other;
        return *this;
    }

    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
    }

    // Stream Output (e.g., cout << BigInt)
    friend std::ostream& operator<<(std::ostream& out, const BigInt& value) {
        out << value.number;
        return out;
    }
};

#endif
