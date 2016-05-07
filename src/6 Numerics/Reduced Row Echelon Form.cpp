// Reduced row echelon form via Gauss-Jordan elimination 
// with partial pivoting.  This can be used for computing
// the rank of a matrix.
//
// Running time: O(n^3)
//
// INPUT:    a[][] = an nxn matrix
//
// OUTPUT:   rref[][] = an nxm matrix (stored in a[][])
//           returns rank of a[][]

const double EPSILON = 1e-7;

typedef vector<double> VD;
typedef vector<VD> VVD;

// returns rank

int rref (VVD &a){
  int i,j,r,c;
  int n = a.size();
  int m = a[0].size();
  for (r=c=0;c<m;c++){
    j=r;
    for (i=r+1;i<n;i++) if (fabs(a[i][c])>fabs(a[j][c])) j = i;
    if (fabs(a[j][c])<EPSILON) continue;
    for (i=0;i<m;i++) swap (a[j][i],a[r][i]);
    
    double s = a[r][c];
    for (j=0;j<m;j++) a[r][j] /= s;
    for (i=0;i<n;i++) if (i != r){
      double t = a[i][c];
      for (j=0;j<m;j++) a[i][j] -= t*a[r][j];
    }
    r++;
  }
  return r;
}
