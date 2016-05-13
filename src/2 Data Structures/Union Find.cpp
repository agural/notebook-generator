// (struct) also keeps track of sizes
struct union_find {
	vector<int> P,S;

	union_find(int N) {
		P.resize(N), S.resize(N, 1);
		for(int i = 0; i < N; i++) P[i] = i;
	}
	int rep(int i) {return (P[i] == i) ? i : P[i] = rep(P[i]);}
	bool unio(int a, int b) {
		a = rep(a), b = rep(b);
		if(a == b) return false;
		P[b] = a;
		S[a] += S[b];
		return true;
	}
};
// (Shorter) union-find set: the vector/array contains the parent of each node
int find(vector <int>& C, int x){return (C[x]==x) ? x : C[x]=find(C, C[x]);} //C++
int find(int x){return (C[x]==x)?x:C[x]=find(C[x]);} //C
