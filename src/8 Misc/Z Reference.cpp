// STL Quick Reference
// most have begin(), end(), empty(), clear(), size()
// rbegin(), rend() => array, vector, string, set, multiset, map, deque
// lower/upper_bound(), equal_range() => set, multiset, map
int a1[10], a2[10] = {0}, a3[10] = {1,2,3,4,5,6,7,8,9,10}; // not STL
array<int, 10> a4 = {1,2,3,4,5,6,7,8,9,10};
pair<int, int> p1, p2 = {1,2}, p3 = make_pair(1,2);
tuple<int, char> tp1(10, 'x'), tp2 = make_tuple(30, 'y');
    get<0>(tp1) = 3, tie(ignore, mychar) = tp1 // unpack into mychar
    tuple_size<decltype(tp1)>, tuple_cat(tp1, tp2),
    forward_as_tuple(1,'a') // use as something to pass to functions
vector<int> v1, v2(100), v3(100, 0), v4(a3, a3 + 10), v5 = {1,3};
    v2.push_back(1), v2.pop_back(), v2[2], v2.empty(), v2.clear()
    front(), back(), reserve()
    find(v5.begin(), v5.end(), 3) != v5.end();
    v5.insert(find(v5.begin(), v5.end(), 1), 2); // => {2,1,3}
    v5.erase(find(v5.begin(), v5.end(), 3)); // => {2,1}
string str1, str2("hello"), str3(str2), str4(str2,1,3), str5(10,'x');
    // has the functions vector has, but also has:
    c_str(), find(), rfind(), substr(), compare(), (+)
    str2.find("el") != strong::npos;
set<int> s1, s2 = {1,2}, s3(v.begin(), v.end()); set<int, classcomp> s4;
    insert(el), erase(it), erase(value), find(el), count(el),
    s2.lower_bound("p"), s2.upper_bound("p"), s2.equal_range("p")
    pair<it, bool unique> ret = s2.emplace(3), s2.emplace_hint(it2, 3);
multiset<int> ms1 // same as set, except stores multiple copies
    it ret = ms1.emplace(it2, 3);
unordered_set<int> us1 // same as set, except without ordering
    bucket_count(), bucket_size(), bucket(el), reserve(10),
    hash_function(el), max_load_factor(max_load_factor()/2.0)
map<string, int> m1, m2 = {{"zero", 0}, {"one", 1}, {"two", 2}};
    m1["0"]=0, m1.erase("0"), m.clear(),
    m2.lower_bound("p"), m2.upper_bound("p"), m2.equal_range("p")
    m1.find("0") != m1.end();
    for(auto p : m1) cout << p1.first << " " << p1.second << endl;
    auto it = m2.lower_bound()
unordered_map<string, int> um1 // same as map, except without ordering
    // also has same utilities as unordered_set regarding hashing
queue<int> q1, q2(other stl object)
    front(), back(), push(), pop() // NO iterators begin(), end(), etc
priority_queue<int[, vector<int>, greater<int>]> pq1, pq2(a1, a1+5);
    top(), push(), pop() // NO iterators begin(), end(), etc
deque<int> dq1, dq2(4,100), dq3(dq2.begin(),dq2.end()), dq4(dq3);
    front(), back(), push_front(), push_back(), pop_front(), pop_back()
list<int> l1; // same constructors and functions as deque, but also:
    insert(it, 4), insert(it, 4, 10), insert(it, a1, a1+5),
    l1.splice(it, l2), l1.remove(89), l1.unique(), merge(), reverse()
bitset<> bs1, bs2(0xfa2), bs3("0101");
    none(), any(), test(3), count() // # set
    set(), set(1), set(1, 0), reset(), reset(1), flip(), flip(1),
    to_string(), to_ulong(), to_ullong()
numeric_limits<int>::min(), max(), is_signed, digits, has_infinity

// Bounds (equal_range gives pair {lower_bound, upper_bound})
1 4 5 6 6 6 8 9 14   // sample multiset
      ^-----^        // lower_bound(6) => 6, upper_bound(6) => 8
    ^-^              // lower_bound(5) => 5, upper_bound(5) => 6
            ^        // lower_bound(7) => 8, upper_bound(7) => 8
^                    // lower_bound(0) => 1, upper_bound(0) => 1
                   ^ // lower_bound(20) => (end), upper_bound(20) => (end)

// Comparisons
bool myfunction (int i,int j) { return (i<j); } // function version
struct myclass {
    bool operator() (int i,int j) { return (i<j);} // object version
} myobject;
int myints[] = {32,71,12,45,26,80,53,33};
std::vector<int> myvector (myints, myints+8);
sort(v.begin(), v.end(), myfunction);
sort(v.begin(), v.end(), myobject);

// Misc.
for(auto i : v) { cout << i << endl; }
for(auto &i : v) { i *= 2; }
sort(v.begin(), v.end(),
    [&](const int& a, const& int b) -> bool {return a < b;});
unique(v.begin(), v.end());
all_of(v.begin(), v.end(), [](int i){return i % 2 == 0;});
all_of, none_of, any_of, find_if_not, copy_if, minmax, minmax_element

// Random
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
shuffle(foo.begin(), foo.end(), std::default_random_engine(seed));
random_shuffle(myvector.begin(), myvector.end());
next_permutation(v.begin(), v.end());

// Regex
bool equals = regex_match("subject", regex("(sub)(.*)") );

// Timing
auto start = high_resolution_clock::now();
auto end = high_resolution_clock::now();
cout<<duration_cast<milliseconds>(end-start).count()<<endl;

// Ratios: add, subtract, multiply, divide,
// equal, not_equal, less, less_equal, greater, greater_equal
using sum = ratio_add<ratio<1,2>, ratio<2,3>>;
cout << "sum = " << sum::num << "/" << sum::den;

// Functional
[capture] (args) {return func();} // (capture = &) captures all
int RandomNumber() { return rand() % 100; }
generate(v.begin(), v.end(), RandomNumber); // like map
int myfunction (int x, int y) {return x + 2*y;}
int init = 100;
accumulate(v.begin(), v.end(), init, myfunction); // like fold
for_each(v.begin(), v.end(), [&](int x) {cout << x << endl;});
