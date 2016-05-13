void Dijkstra (const VVT &w, VT &dist, VI &prev, int start) {
    int n = w.size();
    VI found (n);
    prev = VI(n, -1);
    dist = VT(n, 1000000000);
    dist[start] = 0;
    while (start != -1){
        found[start] = true;
        int best = -1;
        for (int k = 0; k < n; k++) if (!found[k]) {
            if (dist[k] > dist[start] + w[start][k]) {
                dist[k] = dist[start] + w[start][k];
                prev[k] = start;
            }
            if (best == -1 || dist[k] < dist[best]) best = k;
        }
        start = best;  
    }
}
