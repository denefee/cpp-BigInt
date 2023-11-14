#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include "BigInt.hpp"

void test_of_length() {
    BigInt n(12345);
    int l = Length(n);
    if (l == 5) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";}   // | На эту тему разбирали вариант самописного макроса
                                // | похожего на REQUIRE из Catch2
                                // | Или можно было взять прям Catch2
}

void test_of_streams() {
    std::cout << "Print your number: ";
    BigInt num;
    std::cin >> num;
    std::cout << "Your number is: "<< num << '\n';
}

void test_of_plus_plus() {
    BigInt num(12345);
    num++;
    if (num == 12346) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

BigInt test_of_summ() {
    BigInt n1(234);
    BigInt n2(432);

    BigInt n;
    n = n1 + n2; 
    
    return n; 
}

void test_of_minus_minus() {
    BigInt num(12345);
    num--;
    if (num == 12344) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

BigInt test_of_substract() {
    BigInt n1(54321);
    BigInt n2(43210);

    BigInt n;
    n = n1 - n2;
    
    return n; 
}

BigInt test_of_substract_only_negatives() {
    BigInt n1(-12345);
    BigInt n2(-12345);

    BigInt n;
    n = n1 - n2;
    
    return n; 
}

void test_of_equality() {
    BigInt n1(12345);
    BigInt n2(12345);
    if (n1 == n2) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

void test_of_inequality() {
    BigInt n1(12345);
    BigInt n2(12346);
    if (n1 != n2) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

void test_of_bigger() {
    BigInt n1(12345);
    BigInt n2(123);
    if (n1 > n2) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

void test_of_eqbigger() {
    BigInt n1(12345);
    BigInt n2(123);

    if (n1 >= n2 && n1 >= n1) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

void test_of_smaller() {
    BigInt n1(12345);
    BigInt n2(123);
    if (n2 < n1) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

void test_of_eqsmaller() {
    BigInt n1(123);
    BigInt n2(12345);

    if (n1 <= n2 && n1 <= n1) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

void test_of_mult() {
    BigInt a(-12);
    BigInt b(13);
    BigInt res;
    res = a*b;

    if (res == -156) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}

void test_of_giantism() {
    BigInt huge(1);
    for (int i = 0; i < 64; i++) huge*=2;
    BigInt a, b;
    a = (huge - 1)*(huge + 1);
    b = huge * huge;

    if (b - a == 1) {std::cout << "CORRECT\n";}
    else {std::cout << "ERROR\n";} 
}


int main() {
    test_of_streams();

    std::cout << "Testing of Length() result: ";
    test_of_length();

    std::cout << "Testing of operator== result: ";
    test_of_equality();

    std::cout << "Testing of operator!= result: ";
    test_of_inequality();

    std::cout << "Testing of operator> result: ";
    test_of_bigger();

    std::cout << "Testing of operator>= result: ";
    test_of_eqbigger();

    std::cout << "Testing of operator< result: ";
    test_of_smaller();

    std::cout << "Testing of operator<= result: ";
    test_of_eqsmaller();

    std::cout << "Testing of operator++ result: ";
    test_of_plus_plus();

    std::cout << "Testing of operator+ result: 234 + 432 = " << test_of_summ() << '\n';

    std::cout << "Testing of operator-- result: ";
    test_of_minus_minus();

    std::cout << "Testing of operator- result: 54321 - 43210 = " << test_of_substract() << '\n';

    std::cout << "Testing of operator- with equal negatives result: -12345 - (-12345) = " << test_of_substract_only_negatives() << '\n';

    std::cout << "Testing of operator* result: ";
    test_of_mult();

    std::cout << "Testing of giantism result: ";
    test_of_giantism();
    

    return 0;
}
