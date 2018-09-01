// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

/*
system("\"C:\\Program Files\\Graphviz2.38\\bin\\dotty.exe\" C:\\123.gv"); выполнить 
long long sum(long long r)
{
	long long result = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
		result += t[r];
	return result;
}
void inc(long long i, long long delta)
{
	for (; i < 430000; i = (i | (i + 1)))
		t[i] += delta;
}*/

/*int find_set(int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (rand() % 2)
		swap(a, b);
	if (a != b)
		parent[b] = a;
}
for(set<char>::iterator it = c.begin();it!=c.end();it++){
cout << *it;
}
ifstream cin("bureau.in");
ofstream cout("bureau.out");
*/
/*#include <iostream> 
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
#include <bitset>*/
// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
//s.insert(s1.begin(), s1.end());- обьединить s1 и s
//copy( mySet.begin(), mySet.end(), ostream_iterator<int>(cout, " "));-вывести set
//islower(s[i])
//getline(cin,s,
//pq.pop()  - выкидывает член pq
//myPrQueue.top() - смотрит myPrQueue
//priority-queue<int>pq; - ввод приорити къю
//fixed << setprecision(9) - константный вывод 
//binary-search(v.begin(),v.end(),x)-найти х на v
//lower-bound(v.begin(),v.end(),x) - найти 1 х на v
//upper-bound(v.begin(),v.end(),x) - max x +1 Ha v
//sort(v.begin(),v.end()) - сортировка дл€ вектора v
//v.push-back(x) - добавить последний член x
//v.pop-back() - убрать последний член 
// - добавить в набор s x
//s.size() -  длина набора  s
//v.resize(123) - изменить размер вектора v на 123
//sort(a, )cout << fixed << setprecision(15)
/*

bitset<2000> n;
n = (bitset<2000>)(7);
cout << n.count();

for(set<char>::iterator it = c.begin();it!=c.end();it++){
s+=*it;
}
set<int> s;
if(s.find(42) != s.end())
vector<int> combine(vector<int> a, vector<int> b) {
	if (a[0] > b[0]){
		return a;
	}
	if (b[0] > a[0]){
		return b;
	}
	a[1] += b[1];
	a[2] = min(a[2], b[2]);
	return a;
}
void build(int a[], int v, int tl, int tr) {
	if (tl == tr){
		t[v][0] = a[tl];
		t[v][1] = 1;
		t[v][2] = tl + 1;
	}
	else {
		int tm = (tl + tr) / 2;
		build(a, v * 2, tl, tm);
		build(a, v * 2 + 1, tm + 1, tr);
		t[v] = combine(t[v * 2], t[v * 2 + 1]);
	}
}

vector<int> get_max(int v, int tl, int tr, int l, int r) {
	if (l > r){
		vector<int>zo;
		zo.resize(3);
		zo[0] = -3;
		zo[1] = 0;
		zo[2] = 0;
		return zo;
	}
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return combine(
		get_max(v * 2, tl, tm, l, min(r, tm)),
		get_max(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
		);
}
using namespace std;
long long gcd(long long x1, long long x3){
return x3 ? gcd(x3, x1 % x3) : x1;
}
int n;
priority_queue<pair <long long, long long >> pq;
vector <vector< pair <long long, long long >>> g;
vector < long long>  cl, p, res;
int main() {
long long m, k, c, ch, i;
cin >>n >>m;
g.resize(n);
for (i = 0; i<m; i++){
int a, b;
cin >>a >> b>>ch;
g[a - 1].push_back(make_pair(-ch, b - 1));
g[b - 1].push_back(make_pair(-ch, a - 1));
}
p.assign(n, -1);
cl.assign(n, -10010010010000);
pq.push(make_pair(0, 0));
cl[0] = 0;
while (!pq.empty()){
pair <long long, long long > to = pq.top();
pq.pop();
for (i = 0; i < g[to.second].size(); i++){
if (cl[g[to.second][i].second] <= to.first + g[to.second][i].first){
cl[g[to.second][i].second] = to.first + g[to.second][i].first;
p[g[to.second][i].second] = to.second;
pq.push(make_pair(to.first + g[to.second][i].first,g[to.second][i].second));
}
}
}
if (cl[n-1] == -10010010010000){
cout << "-1";
return 0;
}
for (i = n-1; i != -1;i=p[i]){
res.push_back(i);
}
for (i = res.size()-1; i >= 0; i--){
cout << res[i]+1 << " ";
}
return 0;
}

vector<int> prefix_function(string s) {
int n = (int)s.length();
vector<int> pi(n);
for (int i = 1; i<n; ++i) {
int j = pi[i - 1];
while (j > 0 && s[i] != s[j])
j = pi[j - 1];
if (s[i] == s[j])  ++j;
pi[i] = j;
}
return pi;
}

*/