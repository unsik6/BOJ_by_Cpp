/* 백준 25207번 바벨탑의 저주 // IUPC #3
*
* Input: 첫째 줄: 노드의 수 N (1 <= N <= 500,000)
*		 둘째 줄: a1~aN까지의 N개의 정수 (-10^9 <= ai <= 10^9)
*		 N-1개의 줄: 두 정수 i, j (i번 노드가 j번 노드의 부모)
*
* Output: 첫째 줄: 저주 노드의 수
*		  둘째 줄: 저주 노드들의 노드 번호를 작은 수부터 공백으로 구분하여 출력
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 500001

struct info { int pIdx; int lvl; int nodeNum; };

vector<int> result;

int elemArr[MAX];
int parArr[MAX];
vector<int> children[MAX];

vector<info> dfsArr[MAX];
vector<info> dfsrArr[MAX];

info DFS(int _root, vector<info>& _dfsArr, int _lvl)
{
	if (children[_root].empty())
	{
		result.push_back(_root);
	}
	else
	{
		int pdelta = 1;
		for (int i = 0; i < children[_root].size(); i++)
		{
			info childInfo = (DFS(children[_root][i], dfsArr[children[_root][i]], _lvl + 1));
			for (int j = 0; j < dfsArr[children[_root][i]].size(); j++)
			{
				_dfsArr.push_back(dfsArr[children[_root][i]][j]);
				_dfsArr[_dfsArr.size() - 1].pIdx += pdelta;
			}
			pdelta++;
			_dfsArr.push_back(childInfo);
		}
	}
	info tmp{ 0, _lvl, _root };
	return tmp;	
}

info rDFS(int _root, vector<info>& _dfsrArr, int _lvl)
{
	int pdelta = 1;
	for (int i = children[_root].size() - 1; i >= 0; i--)
	{
		info childInfo = (rDFS(children[_root][i], dfsrArr[children[_root][i]], _lvl + 1));
		for (int j = 0; j < dfsrArr[children[_root][i]].size(); j++)
		{
			_dfsrArr.push_back(dfsrArr[children[_root][i]][j]);
			_dfsrArr[_dfsrArr.size() - 1].pIdx += pdelta;
		}
		pdelta++;
		_dfsrArr.push_back(childInfo);
	}
	info tmp{ 0, _lvl, _root };
	return tmp;
}

int main()
{
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> elemArr[i];
	}

	for (int i = 1; i <= N - 1; i++)
	{
		int p, c;
		cin >> p >> c;
		parArr[c] = p;
		children[p].push_back(c);
	}

	for (int i = 1; i <= N; i++)
	{
		if (children[i].empty()) continue;
		sort(children[i].begin(), children[i].end());
	}

	DFS(1, dfsArr[1], 0);
	rDFS(1, dfsrArr[1], 0);
	
	for (int i = 1; i <= N; i++)
	{
		if (dfsArr[i].empty())
			continue;
		else
		{
			bool isCursed = true;
			for (int j = 0; j < dfsArr[i].size(); j++)
			{
				if (elemArr[dfsArr[i][j].nodeNum] != elemArr[dfsrArr[i][j].nodeNum]
					|| dfsArr[i][j].pIdx != dfsrArr[i][j].pIdx
					|| dfsArr[i][j].lvl != dfsArr[i][j].lvl)
				{
					isCursed = false;
					break;
				}
			}
			if (isCursed)
			{
				result.push_back(i);
			}
		}
	}

	sort(result.begin(), result.end());
	cout << result.size() << '\n';
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << ' ';

	return 0;
}