#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
static bool DBG = 0;

template<typename T, typename U> struct seg_tree_lazy {
	int S, H;
	T zero;
	vector<T> value;
	U noop;
	vector<bool> dirty;
	vector<U> prop;

	seg_tree_lazy<T,U>(int _S, T _zero = T(), U _noop=U()) {
		zero = _zero, noop = _noop;
		for(S = 1, H = 1; S < _S; ) S *= 2, H++;
		value.resize(2*S, zero);
		dirty.resize(2*S, 0);
		prop.resize(2*S, noop);
	}
	void set_leaves(vector<T> &leaves) {
		copy(leaves.begin(), leaves.end(), value.begin() + S);
		for(int i = S-1; i > 0; i--) value[i] = value[2*i] + value[2*i+1];
	}
	void apply(int i, U &update) {
		value[i] = update(value[i]);
		if(i < S) {
			prop[i] = prop[i] + update;
			dirty[i] = 1;
		}
	}
	void rebuild(int i) {
		for(int l = i/2; l; l/=2) {
			T combined = value[2*l] + value[2*l+1];
			value[l] = prop[l](combined);
		}
	}
	void propagate(int i) {
		for(int h = H; h > 0; h--) {
			int l = i >> h;
			if(dirty[l]) {
				apply(2*l, prop[l]);
				apply(2*l+1, prop[l]);
				prop[l] = noop;
				dirty[l] = 0;
			}
		}
	}
	void upd(int i, int j, U update) {
		i += S, j += S;
		propagate(i), propagate(j);
		for(int l = i, r = j; l <= r; l/=2, r/=2) {
			if((l&1)==1) apply(l++, update);
			if((r&1)==0) apply(r--, update);
		}
		rebuild(i), rebuild(j);
	}
	T query(int i, int j) {
		i += S, j += S;
		propagate(i), propagate(j);
		T res_left = zero, res_right = zero;
		for(; i <= j; i/=2, j/=2) {
			if((i&1)==1) res_left = res_left + value[i++];
			if((j&1)==0) res_right = value[j--] + res_right;
		}
		return res_left + res_right;
	}
};

struct pirate {
	int sum, width;
	pirate operator+(const pirate &n) {
		return { sum + n.sum, width + n.width };
	}
};

struct update {
	int type; // -2 for no change, -1 to invert, 0 to set to 0, 1 to set to 1
	//int value;
	pirate operator()(const pirate &n) {
		if(type == -2) return {n.sum, n.width};
		if(type == -1) return {n.width - n.sum, n.width};
		if(type ==  0) return {n.width * 0, n.width};
		if(type ==  1) return {n.width * 1, n.width};
	}
	update operator+(const update &u) {
		if(u.type >=  0) return u;
		if(u.type == -2) return { type };
		if(u.type == -1) return { (type>=0)?1-type:-3-type };
	}
};

void diag(seg_tree_lazy<pirate, update> lst) {
	cout << "LST Diagnostics: ";
	for(int i = 0; i < min(20, lst.S); i++) {
		cout << lst.query(i, i).sum << " ";
	}	cout << endl;
}

int main() {
	int TC, m, t, q; string s;
	cin >> TC;
	for(int tc = 1; tc <= TC; tc++) {
		stringstream ss;
		cin >> m;
		for(int i = 0; i < m; i++) {
			cin >> t;
			cin >> s;
			for(int j = 0; j < t; j++) ss << s;
		}

		s = ss.str();
		if(DBG) cout << tc << ": " << s << endl;
		vector<pirate> vp(s.size());
		for(int i = 0; i < s.size(); i++) {
			vp[i].sum = (s[i] == '1');
			vp[i].width = 1;
		}
		seg_tree_lazy<pirate, update> lst(vp.size(), {0,1}, {-2});
		lst.set_leaves(vp);

		cout << "Case " << tc << ":" << endl;
		int Q,a,b; char c;
		cin >> Q;
		int qn = 0;
		if(DBG) diag(lst);
		for(int q = 1; q <= Q; q++) {
			//if(DBG) cout << q << " here" << endl;
			cin >> c >> a >> b;// a--; b--;
			if(c == 'F') { // set to 1
				lst.upd(a,b,{1});
				if(DBG) cout << "1 (" << a << "," << b << ") => ";
				if(DBG) diag(lst);
				continue;
			}
			if(c == 'E') { // set to 0
				lst.upd(a,b,{0});
				if(DBG) cout << "0 (" << a << "," << b << ") => ";
				if(DBG) diag(lst);
				continue;
			}
			if(c == 'I') { // invert
				lst.upd(a,b,{-1});
				if(DBG) cout << "~ (" << a << "," << b << ") => ";
				if(DBG) diag(lst);
				continue;
			}
			// God's query
			qn++;
			cout << "Q" << qn << ": " << lst.query(a,b).sum << endl;
		}
	}
}

