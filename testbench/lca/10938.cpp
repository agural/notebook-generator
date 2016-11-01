#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
static bool DBG = 1;

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;

struct lca {
	int L, N;
	vector<int> depth, size, link;

	lca() {}
	lca(const vvi &graph, int root = 0) {
		N = graph.size();
		for(L = 0; (1 << L) <= N; L++);
		depth.resize(N);
		size.resize(N);
		link.resize(L*N);
		init(root, root, graph);
	}

	void init(int loc, int par, const vvi &graph) {
		link[loc] = par;
		for(int l = 1; l < L; l++)
			link[l*N + loc] = link[(l-1)*N + link[(l-1)*N + loc]];
		for(int nbr : graph[loc]) {
			if(nbr == par) continue;
			depth[nbr] = depth[loc] + 1;
			init(nbr, loc, graph);
			size[loc] += size[nbr];
		}
		size[loc]++;
	}
	int above(int loc, int dist) {
		for(int l = 0; l < L; l++)
			if((dist >> l)&1)
				loc = link[l*N + loc];
		return loc;
	}
	int find(int u, int v) {
		if(depth[u] > depth[v]) swap(u,v);
		v = above(v, depth[v] - depth[u]);
		if(u == v) return u;
		for(int l = L-1; l >= 0; l--) {
			if(link[l*N + u] != link[l*N + v])
				u = link[l*N + u], v = link[l*N + v];
		}
		return link[u];
	}
};

int main () {
	int n;
	while(cin >> n) {
		if(n == 0) break;
		int a,b;
		vvi adj(n,vi());
		for(int i = 0; i < n-1; i++) {
			cin >> a >> b; a--; b--;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		lca lca(adj, 0);

		int l; cin >> l;
		for(int i = 0; i < l; i++) {
			cin >> a >> b; a--; b--;
			int c = lca.find(a,b);
			int ad = lca.depth[a] - lca.depth[c];
			int bd = lca.depth[b] - lca.depth[c];
			int d = ad + bd;
			int f = (ad>bd)?a:b;
			int dist = d/2;
			if(d % 2) {
				int a1 = lca.above(f, dist  ) + 1;
				int a2 = lca.above(f, dist+1) + 1;
				cout << "The fleas jump forever between " << min(a1,a2) << " and " << max(a1,a2) << "." << endl;
			} else {
				int a1 = lca.above(f, dist) + 1;
				cout << "The fleas meet at " << a1 << "." << endl;
			}
		}
	}
}

