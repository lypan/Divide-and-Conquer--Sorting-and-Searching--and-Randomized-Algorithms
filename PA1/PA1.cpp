#include <iostream> 
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int getNumberLength(int num);
pair<int, int> splitNumber(int num, int numLen);
int Karatsuba(int num1, int num2);

void splitString(string &str, int &strLen, string &strFirst, string &strSecond);
string KaratsubaStr(string &str1, string &str2);
string addStr(string &str1, string &str2);
string substractStr(string &str1, string &str2);

int main()
{
	//int num1 = 46;
	//int num2 = 134;

	//string str1 = to_string(num1);
	//string str2 = to_string(num2);

	string str1 = "3141592653589793238462643383279502884197169399375105820974944592";
	string str2 = "2718281828459045235360287471352662497757247093699959574966967627";


	//cout << Karatsuba(num1, num2) << endl;
	cout << KaratsubaStr(str1, str2) << endl;
	//cout << num1 * num2 << endl;

	system("pause");
	return 0;
}

int Karatsuba(int num1, int num2) {
	if (num1 == 0 || num2 == 0)return 0;
	if (num1 < 10 || num2 < 10)return num1 * num2;

	int len1 = getNumberLength(num1);
	int len2 = getNumberLength(num2);

	int minLen = min(len1, len2);

	pair<int, int> p1 = splitNumber(num1, minLen);
	pair<int, int> p2 = splitNumber(num2, minLen);


	int z2 = Karatsuba(p1.first, p2.first);
	int z0 = Karatsuba(p1.second, p2.second);
	int z1 = Karatsuba(p1.first + p1.second, p2.first + p2.second) - z2 - z0;

	int multiFactor = pow(10, minLen - 1);
	int result = z2 * multiFactor * multiFactor + z1 * multiFactor + z0;

	return result;
}

int getNumberLength(int num) {
	return (int)(log10(num) + 1);
}

pair<int, int> splitNumber(int num, int numLen) {
	int dividend = pow(10, numLen - 1);

	pair<int, int> p(num / dividend, num % dividend);

	return p;
}

string KaratsubaStr(string &str1, string &str2) {

	if (str1 == "0" || str2 == "0")return "0";
	if (str1.size() == 1 || str2.size() == 1) {
		return to_string(stoi(str1) * stoi(str2));
	}

	string str1First, str1Second;
	string str2First, str2Second;

	int len = max(str1.length(), str2.length());

	if (len > str1.length()) {
		str1First = "0";
		str1Second = str1;
	}
	else {
		str1First = str1.substr(0, len / 2);
		str1Second = str1.substr(len / 2);
	}
	if (len > str2.length()) {
		str2First = "0";
		str2Second = str2;
	}
	else {
		str2First = str2.substr(0, len / 2);
		str2Second = str2.substr(len / 2);
	}

	len = len - len / 2;

	string z2 = KaratsubaStr(str1First, str2First);
	string z0 = KaratsubaStr(str1Second, str2Second);

	string z1 = KaratsubaStr(addStr(str1First, str1Second), addStr(str2First, str2Second));
	z1 = substractStr(z1, addStr(z2, z0));
	string result = addStr(z2 + string(len * 2, '0'), z1 + string(len, '0'));
	result = addStr(result, z0);
	return result;
}


void splitString(string &str, int &strLen, string &strFirst, string &strSecond) {
	strFirst = str.substr(0, str.length() - (strLen - 1));
	strSecond = str.substr(strFirst.size());
}

string addStr(string &str1, string &str2) {
	// assume two strings are positive numbers

	int index1 = str1.size() - 1;
	int index2 = str2.size() - 1;

	string result = "";
	int carry = 0;
	int sum = 0;


	while (index1 >= 0 || index2 >= 0) {
		int v1 = (index1 >= 0) ? str1[index1] - '0' : 0;
		int v2 = (index2 >= 0) ? str2[index2] - '0' : 0;

		sum = v1 + v2 + carry;
		carry = sum / 10;
		sum = sum % 10;

		index1--;
		index2--;

		result = to_string(sum) + result;
	}
	if (carry != 0)result = to_string(1) + result;
	return result;
}

string substractStr(string &str1, string &str2) {
	// assume two strings are positive numbers, and str1 > str2

	int index1 = str1.size() - 1;
	int index2 = str2.size() - 1;

	string result = "";
	int borrow = 0;
	int sum = 0;


	while (index1 >= 0 || index2 >= 0) {
		int v1 = (index1 >= 0) ? str1[index1] - '0' : 0;
		int v2 = (index2 >= 0) ? str2[index2] - '0' : 0;

		sum = (v1 + borrow) - v2;
		if (sum < 0) {
			// make it positive
			sum += 10;
			borrow = -1;
		}
		else {
			borrow = 0;
		}


		index1--;
		index2--;

		result = to_string(sum) + result;
	}
	// trim leading zero
	result.erase(0, result.find_first_not_of('0'));
	return result;

}
