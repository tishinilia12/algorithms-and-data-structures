// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//
#include <iostream> 
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

using namespace std;
long long gcd(long long x1, long long x3){
    return x3 ? gcd(x3, x1 % x3) : x1;
}
int main(){
    long long n, q, i, j, ans, a, b, c;
    string s, s1;
    long double k;
    cin >> s >> a >> s1 >> k >> b;
    if (a*k>(long double)b){
        cout << "Power up, Evolve";
    }
    else if (a*k<(long double)b){
        cout << "Evolve, Power up";
    }
    else cout << "Whatever";
}