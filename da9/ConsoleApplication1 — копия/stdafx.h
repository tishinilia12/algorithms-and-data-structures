// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

/*long long sum(long long r)
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
*/
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