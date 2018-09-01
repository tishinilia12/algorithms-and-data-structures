// da1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iomanip>
#include <iostream> 
#include <algorithm>

using namespace std;
const int LONG_CHAR = 50;
const int SIZE_R = 131071;
const int LONG_R = 16;
const int LONG_STR = 2060;
const int SIZE_STR = 2;
template <  typename T> class  TVector{
private:
    T *m;
    T *mv;
    int realSize;
    int size;
public:
    TVector(){
        realSize = 0;
        size = 0;
    }
    int Size(){
        return size;
    }
    void Resize(int wensize){
        if (wensize>realSize){
            if (size){
                delete[] m;
            }
            m = new T[wensize];
            realSize = wensize;
            size = wensize;
        }
        else{
            size = wensize;
        }
    }
    void Pushback(T newitem){
        if (realSize > size){
            m[size] = newitem;
            size++;
        }
        else{
            mv = new T[realSize * 2 + 1];
            for (int i = 0; i < size; i++){
                mv[i] = m[i];
            }
            mv[size] = newitem;
            if (size){
                delete[] m;
            }
            size++;
            realSize = realSize * 2 + 1;
            m = mv;
        }
    }
    void Clear(){
        if (size){
            delete[] m;
        }
        size = 0;
        realSize = 0;
    }
    T& operator[](int p){ return m[p]; }
};
class TFon{
public:
    long long namberll;
    char namber[30];
    char *str;
};
void LSD(TVector<TFon> *v, int r){
    int m[SIZE_R + 1];
    for (int i = 0; i < SIZE_R + 1; i++){
        m[i] = 0;
    }
    for (int i = 0; i < (*v).Size(); i++){
        m[((*v)[i].namberll >> r)&SIZE_R]++;
    }
    for (int i = 1; i < SIZE_R + 1; i++){
        m[i] += m[i - 1];
    }
    TVector<TFon> v2;
    v2.Resize((*v).Size());
    for (int i = (*v).Size() - 1; i >= 0; i--){
        v2[m[((*v)[i].namberll >> r)&SIZE_R] - 1] = (*v)[i];
        m[((*v)[i].namberll >> r)&SIZE_R]--;
    }
    (*v).Clear();
    *v = v2;
}
void RadixSort(TVector<TFon> *v){
    for (int i = 0; i < 3; i++){
        LSD(&(*v), i * LONG_R);
    }
}
long long FuncLl(char s[LONG_CHAR]){
    long long n = 0;
    long long j = 0;
    for (int i = 0; s[i] != '\0'; i++){
        if (s[i] >= '0' && s[i] <= '9'){
            j++;
            n += (s[i] - '0');
            n *= 10;
        }
    }
    return n;
}
char *FuncChar(char c[LONG_STR]){
    char *s;
    int n = 0;
    for (; c[n] != '\0'; n++){
    }
    s = new char[n + 2];
    for (int i = 0; i != n + 1; i++){
        s[i] = c[i];
    }
    return s;
}
int main(){
    TVector<TFon> myArray;//массив сортировки
    TFon tmp;//элемент для ввода
    char str[LONG_STR];
    while (scanf("%s %[^\n]\n", tmp.namber, str) == SIZE_STR){
        tmp.namberll = FuncLl(tmp.namber);
        tmp.str = FuncChar(str);
        myArray.Pushback(tmp);
    }
    RadixSort(&(myArray));
    for (int i = 0; i < myArray.Size(); i++){
        printf("%s\t%s\n", myArray[i].namber, myArray[i].str);
    }
    return 0;
}
