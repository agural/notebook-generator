#include<bits/stdc++.h>

using namespace std;

int main() {
	int m = 100, t = 200;
	cout << 1 << endl;
	cout << m << endl;
	for(int i = 0; i < m; i++) {
		cout << t << endl;
		for(int j = 0; j < 50; j++) {
			cout << ((rand() % 2)? '0':'1');
		}	cout << endl;
	}
	int Q = 1000;
	cout << Q << endl;
	for(int i = 0; i < Q; i++) {
		int a = rand() % 1000000;
		int b = rand() % 1000000;
		int c = rand() % 4;
		char d = (c == 0)? 'F' :
		         (c == 1)? 'E' :
				 (c == 2)? 'I' : 'S';
		cout << d << " " << a << " " << b << endl;
	}
}
