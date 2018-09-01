// da4.cpp: определяет точку входа для консольного приложения.
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


using namespace std;
class TExample{
public:
    unsigned long int key;
    map<unsigned long int, TExample*> path;
    vector <pair<unsigned long int, unsigned long int> > red;
    TExample* blue;
    unsigned long int size;
    TExample(){
        key = 0;
        size = 0;
        blue = NULL;
    }
    TExample(unsigned long int tmpKey, unsigned long int tmpSize){
        size = tmpSize;
        key = tmpKey;
        blue = NULL;
    }
    void CreatePath(vector<unsigned long int> tmpPatern, unsigned long int k){
        TExample *tmp = this;
        TExample *path;
        for (unsigned long int i = 0; i < tmpPatern.size(); i++){
            if (tmp->path.find(tmpPatern[i]) == tmp->path.end()){
                path = new TExample(tmpPatern[i], i + 1);
                tmp->path[tmpPatern[i]] = path;
            }
            tmp = tmp->path[tmpPatern[i]];
        }
        tmp->red.push_back(make_pair(tmp->size, k));
    }
    void Go(){
        TExample* tmp;
        TExample* tmpBlue;
        queue<TExample*> tmpQueue;
        for (map<unsigned long int, TExample*>::iterator it = this->path.begin(); it != this->path.end(); ++it){
            it->second->blue = this;
            it->second->size = 1;
            tmpQueue.push(it->second);
        }
        while (tmpQueue.size()){
            tmp = tmpQueue.front();
            tmpQueue.pop();
            for (map<unsigned long int, TExample*>::iterator it = tmp->path.begin(); it != tmp->path.end(); ++it){
                it->second->size = tmp->size + 1;
                tmpBlue = tmp->blue;
                while (tmpBlue != NULL && tmpBlue->path.find(it->first) == tmpBlue->path.end()){
                    tmpBlue = tmpBlue->blue;
                }
                if (tmpBlue != NULL){
                    it->second->blue = tmpBlue->path[it->first];
                    tmpBlue = it->second->blue;
                }
                else{
                    it->second->blue = this;
                    tmpBlue = this;
                }
                for (unsigned long int i = 0; i < tmpBlue->red.size(); i++){
                    it->second->red.push_back(tmpBlue->red[i]);
                }
                tmpQueue.push(it->second);
            }
        }
    }
    void Create(vector<vector<unsigned long int> >patern){
        for (unsigned long int i = 0; i < patern.size(); i++){
            this->CreatePath(patern[i], i + 1);
        }
        this->Go();
    }
};
TExample * AhoCorasick(unsigned long int a, TExample * tmpBlue){
    while (tmpBlue->blue != NULL && tmpBlue->path.find(a) == tmpBlue->path.end()){
        tmpBlue = tmpBlue->blue;
    }
    if (tmpBlue->path.find(a) != tmpBlue->path.end()){
        tmpBlue = tmpBlue->path[a];
    }
    return tmpBlue;
}
int  main(){
    TExample *example = new TExample;
    ifstream cin("F:\\Games\\test\\test3.txt");
    vector<vector<unsigned long int> > patern(100);
    vector<unsigned long int>text(100000);
    unsigned long int tmp;
    for (int i = 0; i < 100; i++){
        int n, p;
        cin >> n;
        for (int j = 0; j < n; j++){
            cin >> p;
            patern[i].push_back(p);
        }
    }
    example->Create(patern);
    for (int i = 0; i < 100000; i++){
        cin >> tmp;
        example = AhoCorasick(tmp, example);
    }
    cout << clock();
    return 0;
}