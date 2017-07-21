#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

int main() {
	stringstream sin;
	string line;
	while (getline(cin, line)) {
		int A[100], B[100];
		int a = 0, b = 0, num, i, j;
		sin.clear();
		sin << line;
		while (sin >> num)
			A[a++] = num;
		getline(cin, line);
		sin.clear();
		sin << line;
		while (sin >> num)
			B[b++] = num;
		int Act = 0, Bct = 0;
		for (i = 0; i < a; i++) {
			for (j = 0; j < b; j++) {
				if (A[i] == B[j]) {
					Act++;
					break;
				}
			}
		}
		for (i = 0; i < b; i++) {
			for (j = 0; j < a; j++) {
				if (B[i] == A[j]) {
					Bct++;
					break;
				}
			}
		}
		if (a == Act && a < b)
			puts("A 為 B 的真子集");
		else if (b == Bct && b < a)
			puts("B 為 A 的真子集");
		else if (a == b && Act == a && Bct == b)
			puts("A、B 集合相同");
		else if (Act == 0 && Bct == 0)
			puts("A、B 集合互斥");
		else
			puts("非以上任一狀況");
	}
	return 0;
}