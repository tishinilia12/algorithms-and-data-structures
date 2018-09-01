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
    int n,x,y,mL=0,mR,count=0;
    cin >> n;
    vector<vector<int> >v(n,vector<int>(3)),answer;
    for (int i = 0; i < n; i++){
        cin >> x >> y;
        v[i][0] = i;
        v[i][1] = x;
        v[i][2] = y;
    }
    cin >> mR;
    if (mL > mR){
        swap(mL, mR);
    }
    while (mL < mR && count<= n){
        count++;
        vector<int>tmp(3, INT_MIN);
        for (int i = 0; i < n; i++){
            if (v[i][1]<=mL && v[i][2]>tmp[2]){
                tmp[2] = v[i][2];
                tmp[1] = v[i][1];
                tmp[0] = v[i][0];
            }
        }
        mL = tmp[2];
        answer.push_back(tmp);
    }
    if (mL < mR){
        cout << 0 << endl;
        return 0;
    }
    cout << answer.size() << endl;
    sort(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); i++){
        cout << answer[i][1] << " " << answer[i][2] << endl;
    }
    return 0;
}
