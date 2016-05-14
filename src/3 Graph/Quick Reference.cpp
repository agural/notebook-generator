typedef pair<int,int> ii; typedef vector<int> vi; typedef vector<ii> vii;
// Dijkstra (SSSP sparse) | adj is an adjacency list
priority_queue<ii, vii, greater<ii>> Q;
vi dist(N, INF), dad(N, -1); Q.push({0, s}); dist[s] = 0;
while (!Q.empty()) { ii p = Q.top(); Q.pop();
  for(auto p2 : adj[p.second]) {
    if(dist[p.second] + p2.second < dist[p2.first]) {
      dist[p2.first] = dist[p.second] + p2.second;
      dad[p2.first] = p.second; Q.push({dist[p2.first], p2.first}); }}}
// Dijkstra (SSSP dense) | w is an adjacency matrix
vi found(n, 0), prev(n,-1), dist(n, INF); dist[s] = 0;
while(s != -1) { found[s] = 1; int best = -1;
  for(int k = 0; k < n; k++) if(!found[k]){
    if(dist[k]>dist[s]+w[s][k]){dist[k]=dist[s]+w[s][k];prev[k]=s;}
	if(best == -1 || dist[k] < dist[best]) best = k;} s = best;}
// Bellman-Ford (SSSP neg weights) | adj is an edge list (src,dst,w)
vi dist(n, INF); dist[s] = 0;
for(int i=1;i<n;i++) for(int j=0;j<m;j++) if(dist[adj[j].src] != INF)
  dist[adj[j].dst] = min(dist[adj[j].dst],dist[adj[j].src]+adj[j].w);
for(int j=0;j<m;j++) if(dist[adj[j].src] != INF)
  if(dist[adj[j].src]+adj[j].w<dist[adj[j].dst]) cout<<"Neg cycle!\n";
// Floyd-Warshall (APSP) | w is an adjacency matrix
for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++)
  w[i][j] = min(w[i][j], w[i][k]+w[k][j]);
// Kruskal (MST) | adj is an edge list (w,src,dst) sorted by w
union_find u(n); vector<Edge> result;
for(auto e : adj) if(u.unio(e.src, e.dst)) result.push_back(e);
