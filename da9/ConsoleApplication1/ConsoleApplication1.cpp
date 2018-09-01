#include <iostream> 
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <queue>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <stack>
#include <fstream>
#include <bitset>

using namespace std;

vector<bool> v_b;
vector<vector<int> >v_r;
vector<vector<int> >v_a;
void dfs(int a, int b){
    if (v_b[b]){
        v_b[b] = 0;
        v_a[a].push_back(b);
        for (int i = 0; i < v_r[b].size(); i++){
            dfs(a, v_r[b][i]);
        }
    }
}
int main()
{ 
    int n, m,x,y;
    cin >> n >> m;
    v_b.assign(n + 1, 1);
    v_r.resize(n + 1);
    v_a.resize(n + 1);
    for (int i = 0; i < m; i++){
        cin >> x >> y;
        v_r[x].push_back(y);
        v_r[y].push_back(x);
    }
    for (int i = 1; i <= n; i++){
        dfs(i, i);
    }
    for (int i = 1; i <= n; i++){
        sort(v_a[i].begin(), v_a[i].end());
    }
    for (int i = 1; i <= n; i++){
        if (v_a[i].size()){
            cout <<v_a[i][0];
        for (int j = 1; j < v_a[i].size(); j++){
            cout << " " << v_a[i][j];
        }
            cout << endl;
        }
    }
    return 0;
}
