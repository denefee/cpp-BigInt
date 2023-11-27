#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>

class BigInt{
	std::string digits;
	bool sign = true;
public:
	// Constructors:
	BigInt(int64_t n = 0);
	BigInt(const std::string&); 
	BigInt(const char *);
	BigInt(const BigInt&);

	// Helper functions:
	friend int Length(const BigInt &); // | size_t , а вообще можно было сделать методом класса
	int operator[](const int)const;

	// Operator overloading
	BigInt &operator=(const BigInt &);

	BigInt &operator++();
	BigInt operator++(int temp);
	BigInt &operator--();
	BigInt operator--(int temp);

	friend BigInt &operator+=(BigInt &, const BigInt &);
	friend BigInt operator+(const BigInt &, const BigInt &);
	friend BigInt operator-(const BigInt &, const BigInt &);
	friend BigInt &operator-=(BigInt &, const BigInt &);

	friend bool operator==(const BigInt &, const BigInt &);
	friend bool operator!=(const BigInt &, const BigInt &);
	friend bool operator>(const BigInt &, const BigInt &);
	friend bool operator>=(const BigInt &, const BigInt &);
	friend bool operator<(const BigInt &, const BigInt &);
	friend bool operator<=(const BigInt &, const BigInt &);
	
	friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);

	friend std::ostream &operator<<(std::ostream &,const BigInt &);
	friend std::istream &operator>>(std::istream &, BigInt &);
};

BigInt::BigInt(const std::string &s) {
	int p = 0;
	if (s[0] == '-') {
		sign = false;
		p++;
	} 
	for (int i = p; i < s.size(); i++) {
		if(!isdigit(s[i])) {
			throw std::invalid_argument("Oops2");
		}
		digits.push_back(s[i] - '0');
	}
}

BigInt::BigInt(int64_t number) {
	std::string temp = "";
	if (number < 0) {
		sign = false;
		number = -number;
	}

	while (number) {
		temp.push_back(number % 10);
		number /= 10;
	}

	std::reverse(temp.begin(), temp.end());
	digits = temp;
}

BigInt::BigInt(const char *s) {
	digits = s;
	if (s[0]=='-') {
		sign = false;
		s++;
	}
	while(*s) {
		if (!isdigit(*s)) throw std::invalid_argument("Oops1");
		s++;
	}
}

BigInt::BigInt(const BigInt &a): digits(a.digits), sign(a.sign) {}

int Length(const BigInt &a) {
	return a.digits.size();
}

int BigInt::operator[](const int index) const {
	if (digits.size() <= index || index < 0)
		throw("error: out of range");
	return digits[index];
}

bool operator==(const BigInt &a, const BigInt &b) {
	return (a.digits == b.digits)&&(a.sign == b.sign);
}

bool operator!=(const BigInt &a, const BigInt &b) {
	return !(a == b);
}

bool operator<(const BigInt&a, const BigInt&b) {
	if (a.sign != b.sign)
		return !(a.sign);

	int n = Length(a), m = Length(b);
	if (n != m)
		return (n < m)&&(a.sign);
	for (int i = 0; i < n; i++)
		if(a.digits[i] != b.digits[i])
			return a.digits[i] < b.digits[i];
	return false;
}

bool operator>(const BigInt&a, const BigInt&b) {
	return b < a;
}

bool operator>=(const BigInt&a, const BigInt&b) {
	return !(a < b);
}

bool operator<=(const BigInt&a, const BigInt&b) {
	return !(a > b);
}

BigInt &BigInt::operator=(const BigInt &a) {
	digits = a.digits;
	sign = a.sign;
	return *this;
}

BigInt &BigInt::operator++() {
	if (sign) {
		int n = digits.size();
		for (int i = n-1; i >= 0; i--) {
			if (digits[i] == 9) {
				digits[i] = 0;
				if (i == 0) {
					digits = '1' + digits;
					break;
				}
			}
			else {
				digits[i]++;
				break;
			}
		}
		return *this;
	}
	else {
		BigInt temp = BigInt(digits);
		temp--;
		if ((Length(temp) == 1)&&(temp[0] == 0))
			temp.sign = true;
		digits = temp.digits;
		sign = temp.sign;
		return *this;
	}
}

BigInt BigInt::operator++(int num) {
	BigInt temp;
	temp = *this;
	++(*this);
	return temp;
}

BigInt &BigInt::operator--() {
	if (sign) {
		if (digits[0] == 0 && digits.size() == 1) {
			digits[0] = 1;
			sign = false;
		}

		int i, n = digits.size();
		for (i = n-1; digits[i] == 0 && i >= 0; i--)
			digits[i] = 9;
		digits[i]--;
		if (n > 1 && digits[n - 1] == 0)
			digits.pop_back();
		return *this;
	}

	else {
		BigInt temp = BigInt(digits);
		temp++;
		digits = temp.digits;
		return *this;
	}
}

BigInt BigInt::operator--(int num) {
	BigInt temp;
	temp = *this;
	--(*this);
	return temp;
}

BigInt &operator+=(BigInt &a, const BigInt& b) {
	BigInt a_tmp = a;
	BigInt b_tmp = b;
	
	a_tmp.sign = true;
	b_tmp.sign = true;

	if ((!b.sign)&&(!a.sign)) {
		a_tmp += b_tmp;
		a.digits = a_tmp.digits;
		return a;
	}

	if ((a.sign)&&(!b.sign)) {
		a -= b_tmp;
		return a;
	}

	if ((!a.sign)&&(b.sign)) {
		b_tmp-= a_tmp;
		a.digits = b_tmp.digits;
		a.sign = b_tmp.sign;
		return a;
	}

	if ((b.sign)&&(a.sign)) {
		int t = 0, s, i;
		int n = Length(a), m = Length(b);
		if (m > n)
			a.digits.append(m - n, 0);
		n = Length(a);
		for (i = 0; i < n; i++){
			if (i < m)
				s = (a.digits[i] + b.digits[i]) + t;
			else
				s = a.digits[i] + t;
			t = s / 10;
			a.digits[i] = (s % 10);
		}
		if (t)
			a.digits.push_back(t);
		return a;
	}
	return a;
}

BigInt operator+(const BigInt &a, const BigInt &b) {
	BigInt temp;
	temp = a;
	temp += b;
	return temp;
}

BigInt &operator-=(BigInt&a, const BigInt &b) {
	BigInt a_tmp = a;
	BigInt b_tmp = b;
	a_tmp.sign = b_tmp.sign = true;

	if ((a.sign)&&(!b.sign)) {
		a += b_tmp;
		return a;
	}

	if ((!a.sign)&&(b.sign)) {
		a_tmp += b_tmp;
		a.digits = a_tmp.digits;
		return a;
	}

	if ((!a.sign)&&(!b.sign)) {
		b_tmp -= a_tmp;
		a = std::move(b_tmp);
		return a;
	}

	if ((a.sign)&&(b.sign)) {        
		if (a < b) {
			b_tmp -= a_tmp;
			a.digits = std::move(b_tmp.digits);
			a.sign = false;
			return a;
		}
		int n = Length(a), m = Length(b);
		int i, t = 0, s;
		for (i = 0; i < n; i++){
			if(i < m)
				s = a.digits[i] - b.digits[i]+ t;
			else
				s = a.digits[i]+ t;
			if(s < 0)
				s += 10,
				t = -1;
			else
				t = 0;
			a.digits[i] = s;
		}
		while (n > 1 && a.digits[n - 1] == 0) {
			a.digits.pop_back(),
			n--;
		}
		return a;
	}
	return a;
}

BigInt operator-(const BigInt& a, const BigInt&b) {
	BigInt temp = a;
	temp -= b;
	return temp;
}

BigInt &operator*=(BigInt &a, const BigInt &b) {
    BigInt result;
    BigInt zero("0");
    if (a == zero || b == zero) {
        a = zero;
        return a;
    }

    int n = Length(a), m = Length(b);
    for (int i = 0; i < n + m; i++) {
        result.digits.push_back(0);
    }
    for (int i = 0; i < n; i++) {
        int carry = 0;
        for (int j = 0; j < m; j++) {
            int product = a.digits[i] * b.digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = product % 10;
            carry = product / 10;
        }
        result.digits[i + m] += carry;
    }
    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

	if (a.sign == b.sign)
		result.sign = true;
	else 
		result.sign = false;

    a = result;
    return a;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
    BigInt temp;
	temp = a; 
    temp *= b;  
    return temp;
}

std::istream &operator>>(std::istream &in, BigInt&a){
	std::string s;
	in >> s;
	a = BigInt(s);
	return in;
}

std::ostream &operator<<(std::ostream &out, const BigInt &a){
	if (a.sign) {
		for (int i = 0; i < a.digits.size(); i++)
			out << (short)a.digits[i];
		return out;
	}
	else {
		out << '-';
		for (int i = 0; i < a.digits.size(); i++)
			out << (short)a.digits[i];
		return out;
	}
}
