/*
 *  1423 Big Number
 *  Description: In many applications very large integers numbers are required. 
 *      Some of these applications are using keys for secure 
 *      transmission of data, encryption, etc. 
 *      In this problem you are given a number, you have to determine 
 *      the number of digits in the factorial of the number.
 *  Input: Input consists of several lines of integer numbers. The first line 
 *      contains an integer n, which is the number of cases to be 
 *      tested, followed by n lines, one integer 1 <= m <= 10^7 on each line.
 *  Output: The output contains the number of digits in the 
 *      factorial of the integers appearing in the input.
 *
 *
 */

#include <iostream>
#include <cmath>

using namespace std;

double e = 2.71828182845904523536;
double pi = 3.14159265358979323846;

int stirling_num_digit(int n){
    double digit;
    digit = 0.5 * log10(2*pi*n) + n * log10(n/e);
    return (int)digit + 1;
}

int main(){
    int n, num;

    cin >> n; 
    while(n--){
        cin >> num;
        cout << stirling_num_digit(num) << endl;
    }

    return 0;
}
