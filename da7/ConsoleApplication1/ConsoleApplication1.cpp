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

int main()
{
    int n, w, m,x=0,y=0;
    long long c;
    cin >> n >> m;
    vector<vector<pair<long long, vector<int> > > > v(m+1, vector<pair<long long, vector<int> > >(n+1));
    for (int i = 0; i < n; i++){
        cin >> w >> c;
        for (int j = m - w; j >= 0; j--){
            for (long long k = i; k > 0; k--){
                if ((v[j][k].first) && (v[j][k].first / k * (k + 1) + c *(k + 1))>v[j + w][k + 1].first){
                    v[j + w][k + 1].first = v[j][k].first / k * (k + 1) + c *(k + 1);
                    v[j + w][k + 1].second = v[j][k].second;
                    v[j + w][k + 1].second.push_back(i+1);
                }
            }
        }
        if (w <=m && c > v[w][1].first){
            v[w][1].first = c;
            v[w][1].second = v[0][0].second;
            v[w][1].second.push_back(i + 1);
        }
    }
    for (int j = m; j >= 0; j--){
        for (long long k = n; k >= 0; k--){
            if (v[x][y].first < v[j][k].first){
                x = j;
                y = k;
            }
        }
    }
    cout << v[x][y].first;
    if (v[x][y].second.size())
        cout << endl << v[x][y].second[0];
    for (int i = 1; i < v[x][y].second.size(); i++){
        cout << " " << v[x][y].second[i];
    }
    cout << endl;
    return 0;
}
