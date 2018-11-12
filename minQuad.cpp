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
  ans.resize(m);

  for(vector<double> &x: ans) {
    x.resize(n);
  } 

  int n = adj.size();
  int m = adj[0].size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      ans[j][i] = ans[j][i];
    }
  }

  return ans;
}

vector<vector<double> > matMult(vector<vector<double> > a, vector<vector<double> > b) {
  
  vector<vector<double> > ans;
  if(a[0].size() != b.size())
    return ans;
  int l = a[0].size();

  ans.resize((int)a.size());
  for(vector<double> &x: arr) {
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

signed main () {

  ifstream ip("data.csv");

  if(!ip.is_open()) 
    cout << "ERROR: File Open" << '\n';

  string date;
  string read;
  double value;

  getline(ip, date);

  vector<double> data;

  while(ip.good()){

    getline(ip,date,',');
    getline(ip,read,'\n');
    if(read == ".")
      continue;
    else
      data.pb(stod(read));
  }

  int n = data.size();

  ip.close();
  
  vector< vector<double> > fi(n);
  for(int i = 0; i < n; i++) {
    f[i].pb(data[i]);
    f[i].pb(1.0);
  }

  vector< vector<double> > transfi = transpose(fi);

  vector< vector<double> > mult = matMult(transfi, fi);

  

}