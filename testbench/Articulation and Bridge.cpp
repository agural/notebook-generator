#include<bits/stdc++.h>
using namespace std;

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

int main() {
    ArticulationAndBridge ab1(5);
    ab1.add_edge(1, 0);
    ab1.add_edge(0, 2);
    ab1.add_edge(2, 1);
    ab1.add_edge(0, 3);
    ab1.add_edge(3, 4);
    ab1.run();
    cout << "Graph 1 Articulation Points:" << endl;
    for(int i = 0; i < ab1.N; i++) {
        if(ab1.artic[i]) cout << i << " ";
    }    cout << endl;
    cout << "Graph 1 Bridges:" << endl;
    for(auto x : ab1.bridge) {
        cout << x.first << " " << x.second << endl;
    }
 
    ArticulationAndBridge ab2(4);
    ab2.add_edge(0, 1);
    ab2.add_edge(1, 2);
    ab2.add_edge(2, 3);
    ab2.run();
    cout << "Graph 2 Articulation Points:" << endl;
    for(int i = 0; i < ab2.N; i++) {
        if(ab2.artic[i]) cout << i << " ";
    }    cout << endl;
    cout << "Graph 2 Bridges:" << endl;
    for(auto x : ab2.bridge) {
        cout << x.first << " " << x.second << endl;
    }
 
    ArticulationAndBridge ab3(7);
    ab3.add_edge(0, 1);
    ab3.add_edge(1, 2);
    ab3.add_edge(2, 0);
    ab3.add_edge(1, 3);
    ab3.add_edge(1, 4);
    ab3.add_edge(1, 6);
    ab3.add_edge(3, 5);
    ab3.add_edge(4, 5);
    ab3.run();
    cout << "Graph 3 Articulation Points:" << endl;
    for(int i = 0; i < ab3.N; i++) {
        if(ab3.artic[i]) cout << i << " ";
    }    cout << endl;
    cout << "Graph 3 Bridges:" << endl;
    for(auto x : ab3.bridge) {
        cout << x.first << " " << x.second << endl;
    }
 
    return 0;
}
