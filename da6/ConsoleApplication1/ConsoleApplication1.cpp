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

const long long NOTATION = 1000000000;
class TBigInt{
public:
    vector<long long> bigInt;
    TBigInt(int a){
        bigInt.resize(a);
    }
    TBigInt(size_t a){
        bigInt.resize(a);
    }
    TBigInt(long long a){
        bigInt.resize(a);
    }
    void display(){
        cout << bigInt[bigInt.size() - 1];
        for (long long i = (long long)(bigInt.size()) - 2ll; i >= 0; i--){
            cout << (bigInt[i] / 100000000) % 10 << (bigInt[i] / 10000000) % 10
                << (bigInt[i] / 1000000) % 10 << (bigInt[i] / 100000) % 10
                << (bigInt[i] / 10000) % 10 << (bigInt[i] / 1000) % 10
                << (bigInt[i] / 100) % 10 << (bigInt[i] / 10) % 10 << (bigInt[i]) % 10;
        }
        cout << '\n';
    }
    TBigInt(string s){
        long long tmp = 0;
        for (long long i = s.size(); i > 0; i -= 9){
            for (long long j = max(i - 9, i - i); j < i; j++){
                tmp *= 10;
                tmp += (s[j] - '0');
            }
            bigInt.push_back(tmp);
            tmp = 0;
        }
        for (long long i = bigInt.size() - 1; i>0 && bigInt[i] == 0; i--){
            bigInt.resize(i);
        }
        if (bigInt.size() == 0){
            bigInt.push_back(0ll);
        }
    }

    void operator=(TBigInt a){
        bigInt = a.bigInt;
    }
    bool operator ==(TBigInt a){
        if (bigInt.size() != a.bigInt.size()){
            return 0;
        }
        for (long long i = bigInt.size() - 1; i >= 0; i--){
            if (bigInt[i] != a.bigInt[i]){
                return 0;
            }
        }
        return 1;
    }
    bool operator<(TBigInt a){
        if (bigInt.size() < a.bigInt.size()){
            return 1;
        }
        if (bigInt.size() > a.bigInt.size()){
            return 0;
        }
        for (long long i = bigInt.size() - 1; i >= 0; i--){
            if (bigInt[i] < a.bigInt[i]){
                return 1;
            }
            if (bigInt[i] > a.bigInt[i]){
                return 0;
            }
        }
        return 0;
    }
    bool operator>(TBigInt a){
        if (bigInt.size() < a.bigInt.size()){
            return 0;
        }
        if (bigInt.size() > a.bigInt.size()){
            return 1;
        }
        for (long long i = bigInt.size() - 1; i >= 0; i--){
            if (bigInt[i] < a.bigInt[i]){
                return 0;
            }
            if (bigInt[i] > a.bigInt[i]){
                return 1;
            }
        }
        return 0;
    }
    TBigInt operator+(TBigInt a){
        long long k = 0;
        long long n = max(a.bigInt.size(), bigInt.size());
        TBigInt tmp(n + 1);
        a.bigInt.resize(n);
        bigInt.resize(n);
        for (long long i = 0; i < n; i++){
            tmp.bigInt[i] = (a.bigInt[i] + bigInt[i] + k) % NOTATION;
            k = (a.bigInt[i] + bigInt[i] + k) / NOTATION;
        }
        if (k == 0){
            tmp.bigInt.resize(n);
        }
        else{
            tmp.bigInt[n] = k;
        }
        return tmp;
    }
    TBigInt operator-(TBigInt a){
        long long k = 0;
        long long n = bigInt.size();
        TBigInt tmp(n);
        for (long long i = 0; i < a.bigInt.size(); i++){
            tmp.bigInt[i] = (NOTATION - a.bigInt[i] + bigInt[i] + k) % NOTATION;
            k = (-a.bigInt[i] + bigInt[i] + k - NOTATION + 1) / NOTATION;
        }
        for (long long i = a.bigInt.size(); i < n; i++){
            tmp.bigInt[i] = (NOTATION + bigInt[i] + k) % NOTATION;
            k = (bigInt[i] + k - NOTATION + 1) / NOTATION;
        }
        for (long long i = n - 1; i>0 && tmp.bigInt[i] == 0; i--){
            tmp.bigInt.resize(i);
        }
        return tmp;
    }
    TBigInt operator*(TBigInt a){
        long long k = 0;
        long long n = (bigInt.size() + a.bigInt.size());
        long long storageDevice;
        TBigInt tmp(n);
        for (int i = 0; i < bigInt.size(); i++){
            if (bigInt[i]){
                for (int j = 0; j < a.bigInt.size(); j++){
                    storageDevice = (bigInt[i] * a.bigInt[j] + k + tmp.bigInt[i + j]) % NOTATION;
                    k = (bigInt[i] * a.bigInt[j] + k + tmp.bigInt[i + j]) / NOTATION;
                    tmp.bigInt[i + j] = storageDevice;
                }
                tmp.bigInt[i + a.bigInt.size()] += k;
                k = 0;
            }
        }
        for (long long i = n - 1; i>0 && tmp.bigInt[i] == 0; i--){
            tmp.bigInt.resize(i);
        }
        return tmp;

    }
    TBigInt operator/(TBigInt a){
        bool y;
        long long k = 0;
        long long storageDeviceTmp;
        long long storageDevice;
        long long q = 0;
        long long d = (NOTATION / 2 - 1 + a.bigInt[a.bigInt.size() - 1]) / a.bigInt[a.bigInt.size() - 1];
        TBigInt tmp2(1);
        tmp2.bigInt[0] = d;
        a = a*tmp2;
        TBigInt tmp_this = (*this*tmp2);
        d = 0;
        int n = (tmp_this.bigInt.size() - a.bigInt.size() + 1);
        TBigInt tmp(n);
        tmp_this.bigInt.push_back(0ll);
        for (int i = int(tmp_this.bigInt.size()) - 2; i >= int(a.bigInt.size()) - 1; i--){
            y = 1;
            k = min((tmp_this.bigInt[i + 1] * NOTATION + tmp_this.bigInt[i]) / a.bigInt[a.bigInt.size() - 1], NOTATION - 1);
            if (!k)
                continue;
            q = max(k - 2, 0ll);
            storageDeviceTmp = 0;
            tmp2.bigInt[0] = q;
            TBigInt tmp_a = a*tmp2;
            tmp_a.bigInt.push_back(0ll);
            if (q){
                tmp.bigInt[i - int(a.bigInt.size()) + 1] += q;
                for (int j = i - int(a.bigInt.size()) + 1; j <= i + 1; j++){
                    storageDevice = (NOTATION - tmp_a.bigInt[j - (i - int(a.bigInt.size()) + 1)] + tmp_this.bigInt[j] + storageDeviceTmp) % NOTATION;
                    storageDeviceTmp = (-tmp_a.bigInt[j - (i - int(a.bigInt.size()) + 1)] + tmp_this.bigInt[j] + storageDeviceTmp - NOTATION + 1) / NOTATION;
                    tmp_this.bigInt[j] = storageDevice;
                }
            }
            q++;
            while (q <= k){
                q++;
                if (!tmp_this.bigInt[i + 1])
                    for (int j = i; j >= i - int(a.bigInt.size()) + 1; j--){
                        if (a.bigInt[j - i + int(a.bigInt.size()) - 1] > tmp_this.bigInt[j]){
                            y = 0;
                            break;
                        }
                        if (a.bigInt[j - i + int(a.bigInt.size()) - 1] < tmp_this.bigInt[j]){
                            break;
                        }
                    }
                if (y){
                    tmp.bigInt[i - a.bigInt.size() + 1]++;
                    storageDeviceTmp = 0;
                    for (int j = i - int(a.bigInt.size()) + 1; j < i + 1; j++){
                        storageDevice = (NOTATION - a.bigInt[j - (i - int(a.bigInt.size()) + 1)] + tmp_this.bigInt[j] + storageDeviceTmp) % NOTATION;
                        storageDeviceTmp = (-a.bigInt[j - (i - int(a.bigInt.size()) + 1)] + tmp_this.bigInt[j] + storageDeviceTmp - NOTATION + 1) / NOTATION;
                        tmp_this.bigInt[j] = storageDevice;
                    }
                    tmp_this.bigInt[i + 1] = tmp_this.bigInt[i + 1] + storageDeviceTmp;
                }
            }
        }
        for (long long i = n - 1; i>0 && tmp.bigInt[i] == 0; i--){
            tmp.bigInt.resize(i);
        }
        return tmp;
    }
    TBigInt operator^(TBigInt a){
        long long i;
        TBigInt tmp = (*this);
        TBigInt resaut("1");
        if (a.bigInt.size() == 1){
            i = a.bigInt[0];
        }
        if (a.bigInt.size() == 2){
            i = a.bigInt[1] + a.bigInt[0] * NOTATION;
        }
        while (i){
            if (i & 1){
                resaut = resaut*tmp;
            }
            tmp = tmp*tmp;
            i /= 2;
        }
        return resaut;
    }
    void operator~(){
        bigInt.clear();
    }
};

int main()
{
    string s1, s2;
    char c;
    while (cin >> s1 >> s2){
        TBigInt  bigInt1(s1);
        TBigInt  bigInt2(s2);
        cin >> c;
        if (c == '='){
            if (bigInt1 == bigInt2){
                cout << "true\n";
            }
            else{
                cout << "false\n";
            }
        }
        if (c == '<'){
            if (bigInt1 < bigInt2){
                cout << "true\n";
            }
            else{
                cout << "false\n";
            }
        }
        if (c == '>'){
            if (bigInt1 > bigInt2){
                cout << "true\n";
            }
            else{
                cout << "false\n";
            }
        }
        if (c == '+'){
            bigInt1 = bigInt1 + bigInt2;
            bigInt1.display();
        }
        if (c == '-'){
            if (bigInt1 < bigInt2){
                cout << "Error\n";
                continue;
            }
            bigInt1 = bigInt1 - bigInt2;
            bigInt1.display();
        }
        if (c == '*'){
            bigInt1 = bigInt1 * bigInt2;
            bigInt1.display();
        }
        if (c == '/'){
            if (bigInt2.bigInt.size() == 1 && bigInt2.bigInt[0] == 0){
                cout << "Error\n";
                continue;
            }
            if (bigInt1 < bigInt2){
                cout << "0\n";
                continue;
            }
            bigInt1 = bigInt1 / bigInt2;
            bigInt1.display();
        }
        if (c == '^'){
            if (bigInt2.bigInt.size() == 1 && bigInt2.bigInt[0] == 0 && bigInt1.bigInt.size() == 1 && bigInt1.bigInt[0] == 0){
                cout << "Error\n";
                continue;
            }
            if (bigInt1.bigInt.size() == 1 && bigInt1.bigInt[0] == 0){
                cout << "0\n";
                continue;
            }
            if (bigInt1.bigInt.size() == 1 && bigInt1.bigInt[0] == 1){
                cout << "1\n";
                continue;
            }
            bigInt1 = bigInt1 ^ bigInt2;
            bigInt1.display();
        }
    }
}
