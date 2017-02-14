#include<iostream>
#include<cmath>
using namespace std;
int main() {
    int a = 12345;
    int b = 6789;
}

int Karatsuba(int num1, int num2) {
    if(abs(num1) < 10 || abs(num2) < 10)return num1 * num2;

    int number_size = floor(log10 (abs(num1))) + 1;
    int max_size = getNumberSize(num1, num2);

    // return Karatsuba() + Karatsuba() + Karatsuba(); 
}
