// Generic flow using an adjacency matrix.  If you
// want just regular max flow, setting all edge costs to 1 gives
// running time O(|E|^2 |V|).
//
// Running time: O(min(|V|^2 * totflow, |V|^3 * totcost))
//
// INPUT: cap -- a matrix such that cap[i][j] is the capacity of
//               a directed edge from node i to node j
//
//        cost -- a matrix such that cost[i][j] is the (positive)
//                cost of sending one unit of flow along a 
//                directed edge from node i to node j
//
//        excess -- a vector such that the total flow from i == excess[i]
//
//
// OUTPUT: cost of the resulting flow; the matrix flow will contain
//         the actual flow values (all nonnegative).
//         The vector excess will contain node excesses that could not be
//         eliminated.  Remember to check it.
//
// To use this, create a MinCostCirc object, and call it like this:
//
//   MinCostCirc circ(N);
//   circ.cap = <whatever>; circ.cost = <whatever>;
//   circ.excess[foo] = bar;
//   circ.flow[i][j] = something;  (if you want)
//   int finalcost = circ.solve();
//
// If you want min-cost max-flow, leave excess blank and call min_cost_max_flow.
// Andy says to use caution in min-cost max-flow mode if you have negative
// costs.

typedef vector<int64_t> VI64;
typedef vector<int> VI;
typedef vector<VI64> VVI64;

const int64_t INF = 1LL<<60;

struct MinCostCirc {
  int N;
  VVI64 cap, flow, cost;
  VI dad, found, src, add;
  VI64 pi, dist, excess;

  MinCostCirc(int N) : N(N), cap(N, VI64(N)), flow(cap), cost(cap),
		       dad(N), found(N), src(N), add(N),
		       pi(N), dist(N+1), excess(N) {}

  void search() {
    fill(found.begin(), found.end(), false);
    fill(dist.begin(), dist.end(), INF);

    int here = N;
    for (int i = 0; i < N; i++)
      if (excess[i] > 0) {
	src[i] = i;
	dist[i] = 0;
	here = i;
      }

    while (here != N) {
      int best = N;
      found[here] = 1;
      for (int k = 0; k < N; k++) {
	if (found[k]) continue;
	int64_t x = dist[here] + pi[here] - pi[k];
	if (flow[k][here]) {
	  int64_t val = x - cost[k][here];
	  assert(val >= dist[here]);
	  if (dist[k] > val) {
	    dist[k] = val;
	    dad[k] = here;
	    add[k] = 0;
	    src[k] = src[here];
	  }
	}
	if (flow[here][k] < cap[here][k]) {
	  int64_t val = x + cost[here][k];
	  assert(val >= dist[here]);
	  if (dist[k] > val) {
	    dist[k] = val;
	    dad[k] = here;
	    add[k] = 1;
	    src[k] = src[here];
	  }
	}

	if (dist[k] < dist[best]) best = k;
      }
      here = best;
    }

    for (int k = 0; k < N; k++)
      if (found[k])
	pi[k] = min(pi[k] + dist[k], INF);
  }
    
  int64_t solve() {
    int64_t totcost = 0;
    int source, sink;
    for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
	if (cost[i][j] < 0)
	  {
	    flow[i][j] += cap[i][j];
	    totcost += cost[i][j] * cap[i][j];
	    excess[i] -= cap[i][j];
	    excess[j] += cap[i][j];
	  }
    
    bool again = true;
    while (again) {
      search();
      int64_t amt = INF;
      fill(found.begin(), found.end(), false);
      again = false;
      for(int sink = 0; sink < N; sink++)
	{
	  if (excess[sink] >= 0 || dist[sink] == INF || found[src[sink]]++)
	    continue;
	  again = true;
	  int source = src[sink];
	  
	  for (int x = sink; x != source; x = dad[x])
	    amt = min(amt, flow[x][dad[x]] ? flow[x][dad[x]] :
		      cap[dad[x]][x] - flow[dad[x]][x]);
	  amt = min(amt, min(excess[source], -excess[sink]));
	  for (int x = sink; x != source; x = dad[x]) {
	    if (add[x]) {
	      flow[dad[x]][x] += amt;
	      totcost += amt * cost[dad[x]][x];
	    } else {
	      flow[x][dad[x]] -= amt;
	      totcost -= amt * cost[x][dad[x]];
	    }
	    excess[x] += amt;
	    excess[dad[x]] -= amt;
	  }
	  assert(amt != 0);
	  break;  // Comment out at your peril if you need speed.
	}
    }
    
    return totcost;
  }

  // returns (flow, cost)
  pair<int,int> min_cost_max_flow(int source, int sink) {
    excess[source] = INF;
    excess[sink] = -INF;
    pair<int, int> ret;
    ret.second = solve();
    ret.first = INF - excess[source];
    return ret;
  }
};
