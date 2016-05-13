#include <bits/stdc++.h>
using namespace std;

int main() {
	multiset<int> s = {1,4,5,6,6,6,8,9,14};
	for(auto i : s) cout << i << " "; cout << endl;
	cout << (*(s.lower_bound(6))) << " " << (*(s.upper_bound(6))) << endl;
	cout << (*(s.lower_bound(5))) << " " << (*(s.upper_bound(5))) << endl;
	cout << (*(s.lower_bound(7))) << " " << (*(s.upper_bound(7))) << endl;
	cout << (*(s.lower_bound(0))) << " " << (*(s.upper_bound(0))) << endl;
	cout << (*(s.lower_bound(20))) << " " << (*(s.upper_bound(20))) << endl;
	for(auto i : s) cout << i << " "; cout << endl;
	auto it = s.end(); it--;
	auto it2 = s.begin(); it2++;
	cout << (*(it2)) << " " << (*(it)) << endl;
	return 0;
}
