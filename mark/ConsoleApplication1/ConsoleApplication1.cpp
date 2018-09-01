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
#include <sstream> 
#include <unordered_map>
#include <random> 


using namespace std;

void f(unordered_map<string, int>&m, int &n, string &sSum, vector<vector<int>>&v, vector<int> &zzz){
    int count = 0;
    istringstream iss(sSum, istringstream::in);
    string s1, s;
    iss >> s1;
    if (m.find(s1) == m.end()){
        m[s1] = n;
        v.push_back(zzz);
        n++;
    }
    while (iss >> s){
        if (m.find(s) == m.end()){
            m[s] = n;
            v.push_back(zzz);
            n++;
        }
        v[m[s1]].push_back(m[s]);
        s1 = s;
        s.clear();
    }
}

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "learn") == 0){
        unordered_map<string, int>m;
        vector<vector<int>>v;
        vector<int> zzz;
        ifstream cin(argv[2]);
        ofstream cout(argv[3]);
        string sLine,sSum;
        int n = 0, leng;
        while (cin >> leng){
            getline(cin, sLine);
            for (int i = 0; i < leng; i++){
                getline(cin, sLine);
                sSum += sLine + " ";
            }
            f(m, n, sSum, v, zzz);
            getline(cin, sLine);
            sSum.clear();
        }
        cout << m.size() << " ";
        for (unordered_map<string, int>::iterator it = m.begin(); it != m.end(); it++){
            cout << (*it).second << " " << (*it).first << " ";
        }
        for (int i = 0; i < v.size(); i++){
            cout << v[i].size() << " ";
            for (int j = 0; j < v[i].size(); j++){
                cout << v[i][j] << " ";
            }
        }
        return 0;
    }
    if (strcmp(argv[1], "generate")==0){
        ifstream cin(argv[2]);
        ofstream cout(argv[3]);
        random_device rd;
        mt19937 gen(rd());
        istringstream iss(argv[4], istringstream::in);
        int n, c, m, thisPosion = -1, length;
        iss >> length;
        length++;
        cin >> n;
        vector<string>myMap(n);
        vector<vector<int>>v;
        vector<int> zzz;
        for (int i = 5; i < argc - 1; i++){
            cout << argv[i] << " ";
        }
        for (int i = 0; i < n; i++){
            cin >> c;
            cin >> myMap[c];
            if (myMap[c] == argv[argc-1]){
                thisPosion = c;
            }
        }
        while (cin >> n){
            for (int i = 0; i < n; i++){
                cin >> c;
                zzz.push_back(c);
            }
            v.push_back(zzz);
            zzz.clear();
        }
        while (zzz.size() < length && v[thisPosion].size()){
            zzz.push_back(thisPosion);
            uniform_int_distribution<> dist(0, v[thisPosion].size()-1);
            thisPosion = v[thisPosion][dist(gen)];
        }
        for (int i = 0; i < length; i++){
            cout << myMap[zzz[i]] << " ";
        }
        if (myMap[zzz[length - 1]][myMap[zzz[length - 1]].size() - 1] != '?'){
            cout << "?";
        }
        cout << "\n";
        return 0;
    }
}