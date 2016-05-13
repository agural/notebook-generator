// Not well-tested. Use at your own risk.
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

struct ArticulationAndBridge {
    int N, root, root_children, dfs_ctr;
    vi dfs_low, dfs_num, dfs_parent, artic;
    vii bridge;
    vvii adj_list;
    
    ArticulationAndBridge (int N) : N(N), dfs_num(N, -1), dfs_low(N, 0),
        dfs_parent(N, 0), artic(N, 0), adj_list(N) {}
    void add_edge(int u, int v) {
        adj_list[u].push_back({v, 0});
        adj_list[v].push_back({u, 0});
    }
    void apab(int u) {
        dfs_low[u] = dfs_num[u] = dfs_ctr++;         // dfs_low[u] <= dfs_num[u]
        for(auto v : adj_list[u]) {
            if(dfs_num[v.first] == -1) {             // tree edge
                dfs_parent[v.first] = u;
                if(u == root) root_children++;       // special case u is root
                apab(v.first);
                if(dfs_low[v.first] >= dfs_num[u])   // articulation point
                    artic[u] = true;
                if(dfs_low[v.first] > dfs_num[u])    // bridge
                    bridge.push_back(make_pair(u, v.first));
                dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
            } else if (v.first != dfs_parent[u])    // back-edge
                dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);
        }
    }
    void run() {
        dfs_ctr = 0;
        for(int i = 0; i < N; i++) {
            if(dfs_num[i] == -1) {
                root = i; root_children = 0; apab(i);
                artic[root] = (root_children > 1);
            }
        }
    }
};
