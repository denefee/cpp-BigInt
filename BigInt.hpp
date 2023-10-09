#include <bits/stdc++.h>

using namespace std;

class BigInt{
	string digits;
public:
	// Constructors:
	BigInt(unsigned long long n = 0);
	BigInt(string &);
	BigInt(const char *);
	BigInt(BigInt &);

	// Helper functions:
	friend bool Null(const BigInt &);
	friend int Length(const BigInt &);
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

	friend ostream &operator<<(ostream &,const BigInt &);
	friend istream &operator>>(istream &, BigInt &);
};

BigInt::BigInt(string &s) {
	string digits = "";
	int n = s.size();
	for (int i = 0; i < n; i++) {
		if(!isdigit(s[i]))
			throw("type error: not a number");
		digits.push_back(s[i] - '0');
	}
}

BigInt::BigInt(unsigned long long number) {
	string temp = "";
	while (number) {
		temp.push_back(number % 10);
		number /= 10;
	}
	for (int i = temp.size()-1; i >= 0; i--) {
		digits.push_back(temp[i]);
	}
}

BigInt::BigInt(const char *s) {
	digits = "";
	for (int i = 0; i < strlen(s); i++)
	{
		if(!isdigit(s[i]))
			throw("type error: not a number");
		digits.push_back(s[i] - '0');
	}
}

BigInt::BigInt(BigInt &a) {
	digits = a.digits;
}

bool Null(const BigInt &a) {
	if (a.digits.size() == 1 && a.digits[0] == 0)
		return true;
	return false;
}

int Length(const BigInt &a) {
	return a.digits.size();
}

int BigInt::operator[](const int index) const {
	if(digits.size() <= index || index < 0)
		throw("error: out of range");
	return digits[index];
}

bool operator==(const BigInt &a, const BigInt &b) {
	return a.digits == b.digits;
}

bool operator!=(const BigInt & a, const BigInt &b) {
	return !(a == b);
}

bool operator<(const BigInt&a, const BigInt&b) {
	int n = Length(a), m = Length(b);
	if(n != m)
		return n < m;
	while(n--)
		if(a.digits[n] != b.digits[n])
			return a.digits[n] < b.digits[n];
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
	return *this;
}

BigInt &BigInt::operator++() {
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

BigInt BigInt::operator++(int num) {
	BigInt temp;
	temp = *this;
	++(*this);
	return temp;
}

BigInt &BigInt::operator--() {
    if (digits[0] == 0 && digits.size() == 1)
        throw("error: underflow");

    int i, n = digits.size();
    for (i = n-1; digits[i] == 0 && i >= 0; i--)
        digits[i] = 9;
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}

BigInt BigInt::operator--(int num) {
	BigInt temp;
	temp = *this;
	--(*this);
	return temp;
}

BigInt &operator+=(BigInt &a, const BigInt& b) {
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

BigInt operator+(const BigInt &a, const BigInt &b) {
	BigInt temp;
	temp = a;
	temp += b;
	return temp;
}

BigInt &operator-=(BigInt&a, const BigInt &b) {
	if (a < b)
		throw("error: underflow");
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
	while (n > 1 && a.digits[n - 1] == 0)
		a.digits.pop_back(),
		n--;
	return a;
}

BigInt operator-(const BigInt& a, const BigInt&b) {
	BigInt temp;
	temp = a;
	temp -= b;
	return temp;
}

BigInt &operator*=(BigInt &a, const BigInt &b) {
	if (Null(a) || Null(b)) {
		a = BigInt();
		return a;
	}
	int n = a.digits.size(), m = b.digits.size();
	vector<int> v(n + m, 0);
	for (int i = n-1; i >= 0; i--)
		for (int j = m-1; j >= 0; j--){
			v[i + j] += (a.digits[i] ) * (b.digits[j]);
		}
	n += m;
	a.digits.resize(v.size());
	for (int s, i = n-1, t = 0; i >= 0; i--) {
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.digits[i] = v[i] ;
	}
	for (int i = 0; i < n && !v[i]; i--)
			a.digits.pop_back();
	return a;
}

BigInt operator*(const BigInt&a, const BigInt&b){
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}

istream &operator>>(istream &in, BigInt&a){
	string s;
	in >> s;
	int n = s.size();
	for (int i = 0; i < n; i++) {
		if(!isdigit(s[i]))
			throw("type error: not a number");
		a.digits.push_back(s[i] - '0');
	}
	return in;
}

ostream &operator<<(ostream &out, const BigInt &a){
	for (int i = 0; i < a.digits.size(); i++)
		out << (short)a.digits[i];
	return out;
}
