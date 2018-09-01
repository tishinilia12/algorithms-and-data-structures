// work4.cpp: определяет точку входа для консольного приложения.
//

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
#include <cstring>

using namespace std;

typedef long long li;
typedef array<li, 2> hv;

inline li mod(li a, li m) {
	return (a%m + m) % m;
}

string c_pr(string str, int pos) {
	int t = 0;
	string s = "";
	for (int i = pos; t < str.size(); i++, t++) {
		if (i == str.size()) i = 0;
		s += str[i];
	}
	return s;
}
bool asd(int count,const string &s1, const char *&s2, vector<pair<pair<li, li>, li> > &p,int a) {
	for (int i = 0; i < s1.size(); i++) {
		if (s2[i + p[count].second] < s1[i]) {
			return 0;
		}
		if (s2[i + p[count].second] > s1[i]) {
			return 1;
		}
	}
	return 1^a;
}
void suf_arr(const char *s, vector<li> &r, int f) {
	li n = strlen(s) + 1;
	vector<pair<pair<li, li>, li> > p(n);
	vector<li> c(n);
	li k = 0;
	for (int h = 0; c[p[n - 1].second] + 1 != n; h = max(2 * h, 1), k++) {
		for (li i = 0; i < n; i++) {
			p[i] = { { h == 0 ? s[i] : c[i], c[(i + h) % n] },i };
		}
		stable_sort(p.begin(), p.end());
		for (li i = 1; i < n; i++) {
			c[p[i].second] = c[p[i - 1].second] + (p[i].first != p[i - 1].first);
		}
	}
	for (li i = 0; i < n; i++) r[i] = p[i].second;
	/*
	vector<li> lcp(n - 1);
	int len = 0;
	for (int i = 0; i < n - 1; i++) {
		int pos = c[i];
		if (pos + 1 < n) {
			for (int j = p[pos + 1].second; s[i + len] == s[j + len]; len++) {
			}
			lcp[pos] = len;
		}
		len = max(len - 1, 0);
	}
	*/
	for (int i = 0; i < f; i++) {
		string str1;
		cin >> str1;
		int ans = 0;
		int l = 0, r = n;
		while (r-l!=1) {
			int mid = (l + r) / 2;
			if (asd(mid, str1, s,p,0)) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		ans = l;
		l = 0; r = n;
		while (r - l != 1) {
			int mid = (l + r) / 2;
			if (asd(mid, str1, s, p,1)) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		cout <<  l-ans << endl;
	}
}

int main() {
	int n,k;
	string str;
	cin >> str>> k;
	vector<li> r(str.size() + 1);
	suf_arr(str.c_str(), r, k);

	//system("pause");
	return 0;
}
