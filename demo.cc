#include <bits/stdc++.h>
#include "DLX.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  int n, m;
  cin >> n >> m;
  string s;
  getline(cin, s);
  vector<set<int>> a(m);
  for (int i = 0; i < m; i++) {
    getline(cin, s);
    stringstream ss(s);
    int t;
    while (ss >> t) {
      a[i].insert(t);
    }
  }
  vector<vector<int>> ret = DLX(n, a).run();
  for (int i = 0; i < (int)ret.size(); i++) {
    cout << "# " << i << endl;
    for (auto x : ret[i]) {
      cout << x << " ";
    }
    cout << endl;
  }
  cout << endl;
  return 0;
}
