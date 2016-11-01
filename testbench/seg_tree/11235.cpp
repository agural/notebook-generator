#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
static bool DBG = 0;

template<typename T> struct seg_tree {
	int S;
	T zero;
	vector<T> value;
	seg_tree<T>(int _S, T _zero = T()) {
		S = _S, zero = _zero;
		value.resize(2*S+1,zero);
	}
	void set_leaves(vector<T> &leaves) {
		copy(leaves.begin(), leaves.end(), value.begin() + S);
		for(int i = S - 1; i > 0; i--) value[i] = value[2*i] + value[2*i+1];
	}
	void upd(int i, T v) {
		i += S;
		value[i] = v;
		while(i>1) {
			i/=2;
			value[i] = value[2*i] + value[2*i+1];
		}
	}
	T query(int i, int j) {
		T res_left = zero, res_right = zero;
		for(i += S, j += S; i <= j; i /= 2, j /= 2) {
			if((i & 1) == 1) res_left = res_left + value[i++];
			if((j & 1) == 0) res_right = value[j--] + res_right;
		}
		return res_left + res_right;
	}
};

struct node {
	int left, right;
	int nl, nr, nm;
	node() {
		left = -1e8;
		right = -1e8;
		nl = 0; nr = 0; nm = 0;
	}
	node(int _left, int _right, int _nl, int _nr, int _nm) {
		left = _left;
		right = _right;
		nl = _nl;
		nr = _nr;
		nm = _nm;
	}
	node operator+(const node &n) {
		if(nm == 0) return n;
		if(n.nm == 0) return {left, right, nl, nr, nm};
		int comb = (right == n.left)? nr + n.nl : max(nr, n.nl);
		int nmax = max(max(nm, n.nm), comb);
		int nlp  = (left == right && right == n.left)? nl+n.nl:nl;
		int nrp  = (n.right == n.left && n.left == right)? n.nr+nr:n.nr;
		node ret(left, n.right, nlp, nrp, nmax);
		return ret;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cout << fixed << setprecision(15);

	int n,q;
	while(cin >> n >> q) {
		if(n == 0) break;
		vector<node> v(n);
		for(int i = 0; i < n; i++) {
			int a; cin >> a;
			node cur(a, a, 1, 1, 1);
			v[i] = cur;
		}
		seg_tree<node> st(n);
		st.set_leaves(v);

		if(DBG) {
			for(int i = 0; i < n; i++) {
				node x = st.query(i,i);
				cout << i << " " << x.left << " " << x.right << " " << x.nl << " " << x.nr << " " << x.nm << endl;
			}
			for(int i = 0; i < n-2; i++) {
				node x = st.query(i,i+2);
				cout << i << ">" << x.left << " " << x.right << " " << x.nl << " " << x.nr << " " << x.nm << endl;
			}
		}

		for(int i = 0; i < q; i++) {
			int a,b; cin >> a >> b; a--; b--;
			cout << st.query(a,b).nm << endl;
		}
	}

	return 0;
}
