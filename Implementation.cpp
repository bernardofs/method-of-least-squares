#include <bits/stdc++.h>

using namespace std;

#define INF (1ll << 62)
#define pb push_back
#define ii pair<int,int>
#define OK cerr <<"OK"<< endl
#define debug(x) cerr << #x " = " << (x) << endl
#define ff first
#define ss second
#define int long long

vector<vector<double>> transpose(vector<vector<double>> adj) {
  vector<vector<double> > ans;
  int n = adj.size();
  int m = adj[0].size();
  
  ans.resize(m);

  for(vector<double> &x: ans) {
    x.resize(n);
  } 

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      ans[j][i] = adj[i][j];
    }
  }

  return ans;
}

double getSum(vector<double> &xd, int factor, vector<double> yd, int fy) {

  double sum = 0;
  int n = xd.size();

  for(int i = 0; i < n; i++) {
    double x = xd[i], y = pow(yd[i], fy);
    sum += pow(x,factor)*y;
  }

  return sum;
}

vector<vector<double> > matMult(vector<vector<double> > a, vector<vector<double> > b) {
  
  vector<vector<double> > ans;
  if(a[0].size() != b.size()) {
    cout << "Error Different Sizes" << endl;
    return ans;
  }
  int l = a[0].size();

  ans.resize((int)a.size());
  for(vector<double> &x: ans) {
    x.resize((int)b[0].size());
  }

  int n = (int)a.size();
  int m = b[0].size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      ans[i][j] = 0;
      for(int k = 0; k < l; k++) {
        ans[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  return ans;
}

double det2(vector<vector<double> > mat) {
  return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);
}

double det3(vector<vector<double> > &mat) {
  return mat[0][0]*mat[1][1]*mat[2][2] + mat[0][1]*mat[1][2]*mat[2][0] +\
         mat[0][2]*mat[1][0]*mat[2][1] - mat[0][2]*mat[1][1]*mat[2][0] -\
         mat[0][1]*mat[1][0]*mat[2][2] - mat[0][0]*mat[1][2]*mat[2][1];
}

vector<vector<double> > cofat(vector<vector<double> > &mat) {

  vector<vector<double> > cofat(3);
  for(vector<double> &x: cofat)
    x.resize(3);
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      vector<vector<double> > q(2);
      int len = 0;
      for(int k = 0; k < 3; k++) {
        if(k == i)
          continue;
        for(int l = 0; l < 3; l++) {
          if(l == j)
            continue;
          q[len].pb(mat[k][l]);
        }
        len++;
      }
      cofat[i][j] = ((i+j) % 2 == 0 ? 1 : -1)*det2(q);
    }
  }

  return cofat;
}


vector<vector<double>> inverse1(vector<vector<double>> mat) {
 swap(mat[0][0], mat[1][1]); 
 mat[0][1] = -mat[0][1];
 mat[1][0] = -mat[1][0];
 
 double det = 1.0/det2(mat);
 
 for(int i = 0; i < 2; i++)
  for(int j = 0; j < 2; j++)
   mat[i][j] *= det;
 
 return mat;
}

vector<vector<double> > inverse2(vector<vector<double> > &mat) {

  double d = 1.0/det3(mat);
  mat = cofat(mat);
  mat = transpose(mat);

  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      mat[i][j] = d*mat[i][j];
    }
  }  

  return mat;  
  
}

vector<vector<double>> inverse(vector<vector<double>> mat, int degree) {
 if(degree == 1)
  return inverse1(mat);
 else if (degree == 2)
  return inverse2(mat);
}

signed main () {

  int n, m, degree;
  cout << fixed << setprecision(10);

  ifstream ip;
  while(!ip.is_open()) {

    cout << "Type the name of the file" << endl;
    string file;
    cin >> file;
    ip.open(file);

    if(!ip.is_open()) {
      cout << "ERROR: File Open" << '\n' << endl;
    }
  }

  string date;
  string read;
  double value;
    
  vector<double> y;

  while(ip.good()){

    getline(ip,date,',');
    getline(ip,read,'\n');
    if(isdigit(read[0])) {
      y.pb(stod(read));
    }
  }

  cout << "Type expected degree of the function" << endl;
  cin >> degree;

  n = y.size();
  vector<double> x(n);
  for(double i = 0; i < n; i++)
    x[i] = i;

  ip.close();

  // get sum of all xi^value
  double xi[2*degree+1], yix[degree+1];
  for(int i = 0; i <= 2*degree; i++) {
    xi[i] = getSum(x, i, y, 0);
  }

  // get sum of all xiyi^value
  for(int i = 0; i <= degree; i++) {
   yix[i] = getSum(x, i, y, 1);
  }
    

  vector<vector<double> > mat(degree+1);
  for(vector<double> &aux: mat)
    aux.resize(degree+1);
  
  // compute matrix of the problem
  // Matrix A in A*X=B 
  for(int i = 0; i <= degree; i++) {
    for(int j = 0, k = i; j <= degree; j++, k++) {
      mat[i][j] = xi[k];
    }
  }

  vector<vector<double> > mat2(degree + 1);
  for(vector<double> &aux: mat2)
    aux.resize(1);
    
  // compute second matrix of the problem
  // Matrix B in A*X=B 
  for(int i = 0; i <= degree; i++)
   mat2[i][0] = yix[i];

  // Compute inverse of matrix A, i.e.,
  // A^(-1)*A*X = A^(-1)*B -> X = A^(-1)*B
  mat = inverse(mat, degree);
      
  // Multiplicate A^(-1)*B and find answer  
  mat = matMult(mat, mat2);

  int pot = degree;
  reverse(mat.begin(), mat.end());
  for(vector<double> &aux: mat) {
    for(double yy: aux) {
      if(pot != degree) {
        cout << (yy >= 0 ? " + " : " - ");
        cout << abs(yy);
      } else {
        cout << yy;
      }
      if(pot != 0)
        cout << "x" << (pot == 1 ? "" : "^" + to_string(pot));
      pot--;
    }
  }
  cout << endl;


}
 
