#include <iostream>
#include <bits/stdc++.h>
#include "BigInt.hpp"

using namespace std;

void test_of_length() {
    BigInt n("12345");
    int l = Length(n);
    if (l == 5) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_streams() {
    cout << "Print your number: ";
    BigInt num;
    cin >> num;
    cout << "Your number is: "<< num << '\n';
}

void test_of_plus_plus() {
    BigInt num("12345");
    num++;
    if (num == 12346) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

BigInt test_of_summ() {
    BigInt n1("234");
    BigInt n2("432");

    BigInt n;
    n = n1 + n2;
    
    return n; 
}

void test_of_minus_minus() {
    BigInt num("12345");
    num--;
    if (num == 12344) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

BigInt test_of_substract() {
    BigInt n1("54321");
    BigInt n2("43210");

    BigInt n;
    n = n1 - n2;
    
    return n; 
}

void test_of_equality() {
    BigInt n1("12345");
    BigInt n2("12345");
    if (n1 == n2) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_inequality() {
    BigInt n1("12345");
    BigInt n2("12346");
    if (n1 != n2) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_bigger() {
    BigInt n1("12345");
    BigInt n2("123");
    if (n1 > n2) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_eqbigger() {
    BigInt n1("12345");
    BigInt n2("123");

    if (n1 >= n2 && n1 >= n1) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_smaller() {
    BigInt n1("12345");
    BigInt n2("123");
    if (n2 < n1) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_eqsmaller() {
    BigInt n1("123");
    BigInt n2("12345");

    if (n1 <= n2 && n1 <= n1) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_mult() {
    BigInt a("12");
    BigInt b("13");
    BigInt res;
    res = a*b;

    if (res == 156) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}

void test_of_giantism() {
    BigInt huge("1");
    for (int i = 0; i < 64; i++) huge*=2;
    BigInt a, b;
    a = (huge - 1)*(huge + 1);
    b = huge * huge;

    if (b - a == 1) {cout << "CORRECT\n";}
    else {cout << "ERROR\n";} 
}


int main() {
    test_of_streams();

    cout << "Testing of Length() result: ";
    test_of_length();

    cout << "Testing of operator== result: ";
    test_of_equality();

    cout << "Testing of operator!= result: ";
    test_of_inequality();

    cout << "Testing of operator> result: ";
    test_of_bigger();

    cout << "Testing of operator>= result: ";
    test_of_eqbigger();

    cout << "Testing of operator< result: ";
    test_of_smaller();

    cout << "Testing of operator<= result: ";
    test_of_eqsmaller();

    cout << "Testing of operator++ result: ";
    test_of_plus_plus();

    cout << "Testing of operator+ result: 234 + 432 = " << test_of_summ() << '\n';

    cout << "Testing of operator-- result: ";
    test_of_minus_minus();

    cout << "Testing of operator- result: 54321 - 43210 = " << test_of_substract() << '\n';

    cout << "Testing of operator* result: ";
    test_of_mult();

    cout << "Testing of giantism result: ";
    test_of_giantism();
    

    return 0;
}