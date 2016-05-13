#include<bits/stdc++.h>

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int main() {
	string test = "Hello, this is a string that we might, like, like to parse! ";
	auto v_space = split(test, ' ');
	auto v_comma = split(test, ',');
	cout << "|"; for(auto s : v_space) cout << s << "|"; cout << endl;
	cout << "|"; for(auto s : v_comma) cout << s << "|"; cout << endl;
	return 0;
}
