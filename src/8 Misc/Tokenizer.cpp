// char tokens
vector<string> &split(const string &s, char delim, vector<string> &elems){
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
// string tokens
vector<string> split(string str, string token) {
    vector<string> result;
    int next;
    while((next = str.find(token)) != string::npos) {
        result.push_back(str.substr(0, next));
        str = str.substr(next + token.size());
    }
    return result;
}

int main() {
    string test = "Hello, this is a string that we might, like, like to parse! ";
    auto v_space = split(test, ' ');
    auto v_comma = split(test, ',');
    cout << "|"; for(auto s : v_space) cout << s << "|"; cout << endl;
    cout << "|"; for(auto s : v_comma) cout << s << "|"; cout << endl;
    // |Hello,|this|is|a|string|that|we|might,|like,|like|to|parse!|
    // |Hello| this is a string that we might| like| like to parse! |
    return 0;
}
