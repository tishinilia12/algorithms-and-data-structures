// da2.cpp: определяет точку входа для консольного приложения.
//

//#include <cstdint>
#include <algorithm>
//#include <cinttypes>
#include <string.h>
#include <bitset>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <fstream>
//#include <time.h>

using namespace std;
int cnt = 0;
class TItem{
public:
    char* str;
    int length;
    TItem(){
        str = (char*)malloc(sizeof(char));
        str[0] = '\0';
        length = 0;
    }
    TItem(istream& is){
        str = (char*)malloc(257 * sizeof(char));
        is >> str;
        length = strlen(str);
        if (length != 256)
            str = (char*)realloc(str, (length + 1) * sizeof(char));
    }
    TItem(string s){
        length = s.size();
        str = strdup(s.c_str());

    }
    TItem(FILE* fin){
        fread(&length, sizeof(int), 1, fin);
        str = (char*)malloc(length + 1 * sizeof(char));
        fread(str, sizeof(char), length, fin);
        str[length] = '\0';
    }
    ~TItem() {
        free(str);
    }
    int GetKeyBit(int n) {
        if (n < 0)
            return 1;
        if (n >= this->length * 5)
            return 0;
        int i = n / 5;
        int position = n % 5;
        // cout << (bitset<8>)str[i]<<" ";
        return (str[i] >> position) & 1;
    }
    void operator = (TItem& obj) {
        length = obj.length;
        str = strdup(obj.str);
    }
};
int equally(TItem* first, TItem* second){
    int end = min(first->length, second->length);
    if (end == 0){
        return 0;
    }
    int i = 0;
    while (tolower(first->str[i]) == tolower(second->str[i]) && i < end){
        ++i;
    }
    if (i == max(first->length, second->length)){
        return -1;
    }
    return i;
}
bool operator == (TItem& first, TItem& second) {
    if (first.length == second.length) {
        int i = 0;
        int end = first.length;
        while (tolower(first.str[i]) == tolower(second.str[i]) && i < end){
            ++i;
        }
        if (i == end){
            return true;
        }
    }
    return false;
}
bool ravno(TItem* first, TItem* second) {
    if (first->length == second->length) {
        int i = 0;
        int end = first->length;
        while (tolower(first->str[i]) == tolower(second->str[i]) && i < end){
            ++i;
        }
        if (i == end){
            return true;
        }
    }
    return false;
}

bool operator != (TItem& first, TItem& second) {
    if (first == second){
        return false;
    }
    return true;
}
class TTree{
public:
    unsigned long long val;
    int path;
    TItem* key;
    TTree* left;
    TTree* right;
    TTree(){
        TItem* tmpItem = new TItem;
        left = this;
        right = this;
        key = tmpItem;
        path = -1;
        val = 0;
    }
    ~TTree(){
        delete key;
    }
    void InsertF(TItem* tmpkey, unsigned long long tmpVal);
    void Insert(TItem* tmpkey, unsigned long long tmpVal);
    void Find(TItem* tmpkey);
    void Delete(TItem* tmpkey);
    void Clear(){
        if (this->path < this->right->path){
            this->right->Clear();
        }
        if (this->path < this->left->path){
            this->left->Clear();
        }
        delete this;
    }
    void Load(FILE* fin){
        int c = cnt;
        cnt = 0;
        while (c != cnt){
            unsigned long long value;
            TItem* item = new TItem(fin);
            fread(&value, sizeof(unsigned long long), 1, fin);
            this->InsertF(item, value);
        }
    }
    void SaveItem(FILE* fout){
        fwrite(&(key->length), sizeof(int), 1, fout);
        fwrite(key->str, sizeof(char), key->length, fout);
        fwrite(&val, sizeof(unsigned long long), 1, fout);
    }
    void Save(FILE* fout){
        if (this->path < this->right->path){
            this->right->Save(fout);
        }
        if (this->path < this->left->path){
            this->left->Save(fout);
        }
        this->SaveItem(fout);

    }
    TTree(TItem* tmpkey, unsigned long long tmpVal, int tmpPath){
        left = this;
        right = this;
        key = tmpkey;
        path = tmpPath;
        val = tmpVal;
    }

};

TTree* Node(TTree* tree, int path, TItem* key){
    if (key->GetKeyBit(path)){
        return tree->right;
    }
    return tree->left;
}
void TTree::InsertF(TItem* tmpkey, unsigned long long tmpVal){
    TTree* tmp;
    int chek;
    int tmpPath = -3;
    tmp = this;
    while (tmp->path > tmpPath){
        tmpPath = tmp->path;
        if (tmpkey->GetKeyBit(tmp->path)){
            tmp = tmp->right;
        }
        else{
            tmp = tmp->left;
        }
    }
    chek = equally(tmp->key, tmpkey);
    if (chek == -1){
        return;
    }
    else{
        chek *= 5;
        for (int i = chek; i < chek + 5; i++){
            if (tmp->key->GetKeyBit(i) != tmpkey->GetKeyBit(i)){
                tmpPath = i;
                break;
            }
        }
        TTree* tmpTree = new TTree(tmpkey, tmpVal, tmpPath);
        TTree* tmp1;
        if (tmpPath > tmp->path){
            tmp1 = Node(tmp, tmp->path, tmpkey);
            while (tmp->path<tmp1->path && tmpPath>tmp1->path){
                tmp = tmp1;
                tmp1 = Node(tmp, tmp->path, tmpkey);
            }
            if (tmpkey->GetKeyBit(tmp->path)){
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->right;
                }
                else{
                    tmpTree->right = tmp->right;
                }
                tmp->right = tmpTree;
            }
            else{
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->left;
                }
                else{
                    tmpTree->right = tmp->left;
                }
                tmp->left = tmpTree;
            }
        }
        else{
            tmp = this;
            TTree* tmp1;
            tmp1 = Node(tmp, tmp->path, tmpkey);
            while (tmp1->path < tmpPath){
                tmp = tmp1;
                tmp1 = Node(tmp, tmp->path, tmpkey);
            }
            if (tmpkey->GetKeyBit(tmp->path)){
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->right;
                }
                else{
                    tmpTree->right = tmp->right;
                }
                tmp->right = tmpTree;
            }
            else{
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->left;
                }
                else{
                    tmpTree->right = tmp->left;
                }
                tmp->left = tmpTree;
            }
        }
        cnt++;
    }
}
void TTree::Insert(TItem* tmpkey, unsigned long long tmpVal){
    TTree* tmp;
    int chek;
    int tmpPath = -3;
    tmp = this;
    while (tmp->path > tmpPath){
        tmpPath = tmp->path;
        if (tmpkey->GetKeyBit(tmp->path)){
            tmp = tmp->right;
        }
        else{
            tmp = tmp->left;
        }
    }
    chek = equally(tmp->key, tmpkey);
    if (chek == -1){
        cout << "Exist" << "\n";
        delete tmpkey;
        return;
    }
    else{
        chek *= 5;
        for (int i = chek; i < chek + 5; i++){
            if (tmp->key->GetKeyBit(i) != tmpkey->GetKeyBit(i)){
                tmpPath = i;
                break;
            }
        }
        TTree* tmpTree = new TTree(tmpkey, tmpVal, tmpPath);
        TTree* tmp1;
        if (tmpPath > tmp->path){
            tmp1 = Node(tmp, tmp->path, tmpkey);
            while (tmp->path<tmp1->path && tmpPath>tmp1->path){
                tmp = tmp1;
                tmp1 = Node(tmp, tmp->path, tmpkey);
            }
            if (tmpkey->GetKeyBit(tmp->path)){
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->right;
                }
                else{
                    tmpTree->right = tmp->right;
                }
                tmp->right = tmpTree;
            }
            else{
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->left;
                }
                else{
                    tmpTree->right = tmp->left;
                }
                tmp->left = tmpTree;
            }
        }
        else{
            tmp = this;
            TTree* tmp1;
            tmp1 = Node(tmp, tmp->path, tmpkey);
            while (tmp1->path < tmpPath){
                tmp = tmp1;
                tmp1 = Node(tmp, tmp->path, tmpkey);
            }
            if (tmpkey->GetKeyBit(tmp->path)){
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->right;
                }
                else{
                    tmpTree->right = tmp->right;
                }
                tmp->right = tmpTree;
            }
            else{
                if (tmpkey->GetKeyBit(tmpPath)){
                    tmpTree->left = tmp->left;
                }
                else{
                    tmpTree->right = tmp->left;
                }
                tmp->left = tmpTree;
            }
        }
        cout << "OK" << "\n";
        cnt++;
    }
}
void TTree::Find(TItem* tmpkey){
    TTree* tmp;
    int tmpPath = -3;
    tmp = this;
    while (tmp->path > tmpPath){
        tmpPath = tmp->path;
        if (tmpkey->GetKeyBit(tmp->path)){
            tmp = tmp->right;
        }
        else{
            tmp = tmp->left;
        }
    }
    if (ravno(tmp->key, tmpkey)){
        cout << "OK: " << tmp->val << "\n";
    }
    else{
        cout << "NoSuchWord" << "\n";
    }
    delete tmpkey;
}
void TTree::Delete(TItem* tmpkey){
    TTree* tmp;
    TTree* tmp1 = this;
    TTree* tmpFather;
    int tmpPath = -3;
    tmp = this;
    while (tmp->path > tmpPath){
        tmpPath = tmp->path;
        if (tmpkey->GetKeyBit(tmp->path)){
            tmp = tmp->right;
        }
        else{
            tmp = tmp->left;
        }
    }
    if (ravno(tmp->key, tmpkey)){
        while (tmp1 != tmp){
            tmpFather = tmp1;
            if (tmpkey->GetKeyBit(tmp1->path)){
                tmp1 = tmp1->right;
            }
            else{
                tmp1 = tmp1->left;
            }
        }
        TTree* tmp3 = Node(tmp, tmp->path, tmp->key);
        if (tmp == tmp3){
            if (tmp->key->GetKeyBit(tmpFather->path)){
                if (tmp->key->GetKeyBit(tmp->path)){
                    tmpFather->right = tmp->left;
                }
                else{
                    tmpFather->right = tmp->right;
                }
            }
            else{
                if (tmp->key->GetKeyBit(tmp->path)){
                    tmpFather->left = tmp->left;
                }
                else{
                    tmpFather->left = tmp->right;
                }
            }
            delete tmp;
        }
        else{
            tmp1 = tmp;
            TTree* tmp2 = tmp;
            while (tmp3 != tmp){
                tmp1 = tmp2;
                tmp2 = tmp3;
                tmp3 = Node(tmp2, tmp2->path, tmp->key);
            }
            if (tmp2->key->GetKeyBit(tmp1->path)){
                if (tmp2->key->GetKeyBit(tmp2->path)){
                    tmp1->right = tmp2->right;
                }
                else{
                    tmp1->right = tmp2->left;
                }
            }
            else{
                if (tmp2->key->GetKeyBit(tmp2->path)){
                    tmp1->left = tmp2->right;
                }
                else{
                    tmp1->left = tmp2->left;
                }
            }
            tmp2->path = tmp->path;
            tmp2->left = tmp->left;
            tmp2->right = tmp->right;
            if (tmp->key->GetKeyBit(tmpFather->path)){
                tmpFather->right = tmp2;
            }
            else{
                tmpFather->left = tmp2;
            }
            delete tmp;
        }
        cout << "OK" << "\n";
        cnt--;
    }
    else{
        cout << "NoSuchWord" << "\n";
    }
    delete tmpkey;
}
int  main(){
    TTree *tree = new TTree();
    string tmp;
    while (cin >> tmp){
        if (tmp[0] == '='){
            string path;
            cin >> path;
            while (1)
            {
                FILE* fout;
                fout = fopen(path.c_str(), "wb");
                fwrite(&cnt, sizeof(int), 1, fout);
                if (tree->right != tree)tree->right->Save(fout);
                fclose(fout);
                FILE*fin;
                fin = fopen(path.c_str(), "rb");
                fread(&cnt, sizeof(int), 1, fin);
                if (tree->right != tree)tree->right->Clear();
                tree->right = tree;
                tree->Load(fin);
                printf("OK\n");
                fclose(fin);
                cout << cnt << "\n";
            }
        }
        else if (tmp[0] == '-'){
            TItem* tmpItem = new TItem(cin);
            tree->Delete(tmpItem);
        }
        else if (tmp[0] == '+'){
            TItem* tmpItem = new TItem(cin);
            unsigned long long tmpVal;
            cin >> tmpVal;
            tree->Insert(tmpItem, tmpVal);
        }
        else if (tmp[0] == '!'){
            string s;
            cin >> s;
            if (s[0] == 'L'){
                string path;
                cin >> path;
                FILE* fin;
                if ((fin = fopen(path.c_str(), "rb")) != NULL) {
                    fread(&cnt, sizeof(int), 1, fin);
                    if (tree->right != tree)tree->right->Clear();
                    tree->right = tree;
                    tree->Load(fin);
                    printf("OK\n");
                    fclose(fin);
                }
                else {
                    printf("ERROR: Couldn't create file\n");
                }
            }
            else{
                string path;
                cin >> path;
                FILE* fout;
                if ((fout = fopen(path.c_str(), "wb")) != NULL) {
                    fwrite(&cnt, sizeof(int), 1, fout);
                    if (tree->right != tree)tree->right->Save(fout);
                    printf("OK\n");
                    fclose(fout);
                }
                else {
                    printf("ERROR: Couldn't create file\n");
                }
            }
        }
        else{
            TItem* tmpItem = new TItem(tmp);
            tree->Find(tmpItem);
        }
    }
    tree->Clear();
    //printf("clock = %d\n", clock());
    return 0;
}