#include <bits/stdc++.h>

using std::set;
using std::vector;

struct DLX {
public:
  /**
   *  \brief construct function
   *  \param ele_num: universe size, indexed from 0
   *  \param     vec: collection of sets to be choosen
   *  \return None
   */
  DLX(int ele_num, vector<set<int>> vec) {
    U.assign(ele_num + 1, 0);
    S = row = column = D = L = R = U;
    H.assign(vec.size() + 1, -1);
    for (int i = 0; i <= ele_num; i++) {
      L[i] = i - 1, R[i] = i + 1;
      S[i] = 0;
      D[i] = U[i] = i;
    }
    R[ele_num] = 0, L[0] = ele_num;
    for (int i = 0; i < (int)vec.size(); i++) {
      for (int x : vec[i]) {
        link(i + 1, x + 1);
      }
    }
    ans.push_back(vector<int>());
    for (int i = 1; i <= (int)vec.size(); i++) {
      ans[0].push_back(i - 1);
    }
    vis.assign(ele_num + 1, false);
  }

  /**
   *  \brief solve set cover
   *  \param None
   *  \return choosen sets, indexed from 0
   */
  vector<vector<int>> run() {
    vector<int> now;
    dance(now);
    return ans;
  }

private:
  int newNode() {
    int ret = U.size();
    U.push_back(0), D.push_back(0);
    L.push_back(0), R.push_back(0);
    column.push_back(0), row.push_back(0);
    return ret;
  }

  void link(int r, int c) {
    S[c]++;
    int p = newNode();
    row[p] = r, column[p] = c;
    U[p] = U[c], D[U[c]] = p;
    D[p] = c, U[c] = p;
    if (H[r] == -1)
      H[r] = L[p] = R[p] = p;
    else {
      L[p] = L[H[r]], R[L[H[r]]] = p;
      R[p] = H[r], L[H[r]] = p;
    }
  }

  void remove(int c) {
    for (int i = D[c]; i != c; i = D[i]) {
      L[R[i]] = L[i];
      R[L[i]] = R[i];
    }
  }

  void resume(int c) {
    for (int i = U[c]; i != c; i = U[i]) {
      L[R[i]] = i;
      R[L[i]] = i;
    }
  }

  int A() {
    fill(vis.begin(), vis.end(), false);
    int ret = 0;
    for (int i = R[0]; i; i = R[i]) {
      if (!vis[i]) {
        vis[i] = true;
        ret++;
        for (int j = D[i]; j != i; j = D[j]) {
          for (int k = R[j]; k != j; k = R[k]) {
            vis[column[k]] = true;
          }
        }
      }
    }
    return ret;
  }

  void dance(vector<int> &now) {
    if (!R[0]) {
      if (now.size() < ans[0].size()) {
        ans.clear();
        ans.push_back(now);
      } else if (now.size() == ans[0].size()) {
        ans.push_back(now);
      }
      return;
    }
    if ((int)now.size() + A() < (int)ans[0].size()) {
      int c = R[0];
      for (int i = R[0]; i; i = R[i]) {
        if (S[i] < S[c]) {
          c = i;
        }
      }
      for (int i = D[c]; i != c; i = D[i]) {
        remove(i);
        for (int j = R[i]; j != i; j = R[j]) {
          remove(j);
        }
        now.push_back(row[i] - 1);
        dance(now);
        now.pop_back();
        for (int j = L[i]; j != i; j = L[j]) {
          resume(j);
        }
        resume(i);
      }
    }
  }
  
  vector<int> U, D, L, R, column, row, H, S;
  vector<vector<int>> ans;
  vector<bool> vis;
};
