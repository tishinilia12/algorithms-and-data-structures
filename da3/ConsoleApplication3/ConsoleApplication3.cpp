// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream> 
#include <vector>
#include <algorithm>
using namespace std;

void LSD(vector<int> *v,int r){
	int m[512], size_r = 511;
	for (int i = 0; i < 512; i++){
		m[i] = 0;
	}
	for (int i = 0; i < (*v).size();i++){
		m[((*v)[i] >> r)&size_r]++;
	}
	for (int i = 1; i < 512; i++){
		m[i] += m[i - 1];
	}
	vector<int> v2;
	v2.resize((*v).size());
	for (int i = (*v).size()-1; i >= 0; i--){
		v2[m[((*v)[i] >> r)&size_r] - 1] = (*v)[i];
		m[((*v)[i] >> r)&size_r]--;
	}
	(*v).clear();
	*v = v2;
}
void radixsort(vector<int> *v){
	for (int i = 0; i < 4; i++){
		LSD(&(*v), i * 8);
	}
}
int main(){
	int n;
	vector<int> v;
	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; i++){
		v[i]=rand();
	}
	radixsort(&v);
	for (int i = 0; i < n; i++){
		cout << v[i]<<" ";
	}
	return 0;
}
