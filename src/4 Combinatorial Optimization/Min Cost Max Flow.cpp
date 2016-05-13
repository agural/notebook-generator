// Min cost max flow algorithm using an adjacency matrix.  If you
// want just regular max flow, setting all edge costs to 1 gives
// running time O(|E|^2 |V|).
//
// Running time: O(min(|V|^2 * totflow, |V|^3 * totcost))
//
// INPUT: cap -- a matrix such that cap[i][j] is the capacity of
//               a directed edge from node i to node j
//        cost -- a matrix such that cost[i][j] is the (positive)
//                cost of sending one unit of flow along a 
//                directed edge from node i to node j
//        source -- starting node
//        sink -- ending node
//
// OUTPUT: max flow and min cost; the matrix flow will contain
//         the actual flow values (note that unlike in the MaxFlow
//         code, you don't need to ignore negative flow values -- there
//         shouldn't be any)
typedef vector<ll> vll;
typedef vector<vll> vvll;
const ll INF = 1LL << 60;

struct MCMF {
	int N;
	vll found, dad, dist, pi;
	vvll cap, flow, cost;
    
	MCMF(int N) : 	N(N), cap(N, vll(N)), flow(cap), cost(cap),
					dad(N), found(N), pi(N), dist(N+1) {};
    
    void add_edge(int from, int to, ll ca, ll co) {
		cap[from][to] = ca; cost[from][to] = co; }    
    bool search(int source, int sink) {
		fill(found.begin(), found.end(), 0);
		fill(dist.begin(), dist.end(), INF);
		dist[source] = 0;
		while(source != N) {
			int best = N;
			found[source] = 1;
			for(int k = 0; k < N; k++) {
				if(found[k]) continue;
				if(flow[k][source]) {
					ll val = dist[source] + pi[source] - pi[k] - cost[k][source];
					if(dist[k] > val) {
						dist[k] = val;
						dad[k] = source;
				    }
				}
				if(flow[source][k] < cap[source][k]) {
					ll val = dist[source] + pi[source] - pi[k] + cost[source][k];
					if(dist[k] > val) {
						dist[k] = val;
						dad[k] = source;
					}
				}
				if(dist[k] < dist[best]) best = k;
			}
			source = best;
		}
		for(int k = 0; k < N; k++)
			pi[k] = min((ll)(pi[k] + dist[k]), INF);
		return found[sink];
    }
    pair<ll,ll> mcmf(int source, int sink) {
		ll totflow = 0, totcost = 0;
		while(search(source, sink)) {
			ll amt = INF;
			for(int x = sink; x != source; x = dad[x])
				amt = min(amt, (ll)(flow[x][dad[x]] != 0 ?
					flow[x][dad[x]] : cap[dad[x]][x] - flow[dad[x]][x]));
			for(int x = sink; x != source; x = dad[x]) {
				if(flow[x][dad[x]] != 0) {
				    flow[x][dad[x]] -= amt;
				    totcost -= amt * cost[x][dad[x]];
				} else {
				    flow[dad[x]][x] += amt;
				    totcost += amt * cost[dad[x]][x];
				}
			}
			totflow += amt;
		}
		return {totflow, totcost};
    }
};
