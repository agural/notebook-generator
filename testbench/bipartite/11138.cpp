#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
static bool DBG = 1;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct bipartite_graph {
	int A, B;
	vvi adj;
	vi visit,match;

	bipartite_graph(int _A, int _B) {
		A = _A, B = _B;
		adj.resize(A + B);
	}
	void edge (int i, int j) {
		adj[i].push_back(A+j);
		adj[A+j].push_back(i);
	}
	bool augment(int loc, int run) {
		if(visit[loc] == run) return 0;
		visit[loc] = run;
		for(int nbr : adj[loc]) {
			if(match[nbr] == -1 || augment(match[nbr], run)) {
				match[loc] = nbr, match[nbr] = loc;
				return 1;
			}
		}
		return 0;
	}
	int matching() {
		visit = vi(A+B, -1);
		match = vi(A+B, -1);
		int ans = 0;
		for(int i = 0; i < A; i++) ans += augment(i,i);
		return ans;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cout << fixed << setprecision(15);
	
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		int a,b; cin >> a >> b;
		bipartite_graph bg(a,b);
		int c;
		for(int i = 0; i < a; i++) {
			for(int j = 0; j < b; j++) {
				cin >> c;
				if(c) bg.edge(i,j);
			}
		}
		cout << "Case " << tc << ": a maximum of " << bg.matching() << " nuts and bolts can be fitted together" << endl;
	}
	
	return 0;
}
