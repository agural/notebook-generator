// Suffix array construction in O(L log^2 L) time. LCP in O(log L) time.
// INPUT:   string s
// OUTPUT:  array suffix[] such that suffix[i] = index (from 0 to L-1)
//          of substring s[i...L-1] in the list of sorted suffixes.
struct SuffixArray {
  const int L; string s;
  vector<vector<int> > P;
  vector<pair<pair<int,int>,int> > M;

  SuffixArray(const string &s) : L(s.length()), s(s),
                                 P(1, vector<int>(L, 0)), M(L) {
    for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
    for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++) 
        M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ?
                P[level-1][i + skip] : -1000), i);
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++) 
        P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
                                   P[level][M[i-1].second] : i;
    }  
  }
  // returns the suffix array (v[i] gives the rank of the ith suffix)
  vector<int> GetSuffixArray() { return P.back(); }
  // si = s[i,i+l1), sj = s[j,j+l2); returns 1 if si > sj, 0 if equal
  int comp(int i, int l1, int j, int l2) {
    int cl = min(l1, l2);
    for(int l = 0; l < 31; l++)
      if((cl >> l) & 1) {
        if(P[l][i] != P[l][j]) return P[l][i] < P[l][j] ? -1 : 1;
        i += 1 << l, j += 1 << l; }
    return (l1 != l2) ? (l1 < l2) ? -1 : 1 : 0;
  }
  // returns the length of the LCP of s[i...L) and s[j...L)
  int LongestCommonPrefix(int i, int j) {
    int len = 0;
    if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
      if (P[k][i] == P[k][j]) {
        i += 1 << k;
        j += 1 << k;
        len += 1 << k;
      }
    }
    return len;
  }
};

int main() {
  // bobocel is the 0'th suffix
  //  obocel is the 5'th suffix
  //   bocel is the 1'st suffix
  //    ocel is the 6'th suffix
  //     cel is the 2'nd suffix
  //      el is the 3'rd suffix
  //       l is the 4'th suffix
  SuffixArray suffix("bobocel");
  vector<int> v = suffix.GetSuffixArray();
  // Expected output: 0 5 1 6 2 3 4
  //                    2
  for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
  cout << endl;
  cout << suffix.LongestCommonPrefix(0, 2) << endl;
}
