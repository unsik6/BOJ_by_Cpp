/* 백준 1197번 최소 스패닝 트리
*
* Input: 정점 개수 V (1 <= V <= 10,000)
*		 간선 개수 E (1 <= E <= 100,000)
*		 E개의 세 정수 (src, dst, wt) (1 <= wt <= 1,000,000)
*
* Output: 최소 스패닝 트리의 가중치의 합
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Info
{
	int dst;
	long long wt;
};

void print(int* _flag, int _v, long long* _distance)
{
	for (int i = 1; i < _v + 1; i++)
	{
		cout << _flag[i] << ' ';
	}
	cout << endl;
	for (int i = 1; i < _v + 1; i++)
	{
		cout << _distance[i] << ' ';
	}
	cout << endl << endl;

}

int main()
{
	int v, e;
	cin >> v >> e;

	vector<Info*>* adjList = new vector<Info*>[v + 1];
	for (int i = 0; i < e; i++)
	{
		int src, dst; long long wt;
		cin >> src >> dst >> wt;
		adjList[src].push_back(new Info{ dst, wt });
		adjList[dst].push_back(new Info{ src, wt });
	}

	int ret = 0;

	long long* distance = new long long[v + 1];
	for (int i = 0; i < v + 1; i++)
	{
		distance[i] = 3000000000;
	}
	int* flag = new int[v + 1]{ 0 };
	flag[1] = 2;
	for (int i = 0; i < adjList[1].size(); i++)
	{
		flag[adjList[1][i]->dst] = 1;
		distance[adjList[1][i]->dst] = adjList[1][i]->wt;
	}

	/*print(flag, v, distance);*/
	
	for (int i = 2; i < v + 1; i++)
	{
		int nextIdx = -1;
		long long minWt = 3000000000;

		for (int j = 1; j < v + 1; j++)
		{
			if (flag[j] == 1 && distance[j] < minWt)
			{
				nextIdx = j;
				minWt = distance[j];
			}
		}

		flag[nextIdx] = 2;
		ret += distance[nextIdx];
		
		for (int j = 0; j < adjList[nextIdx].size(); j++)
		{
			if (flag[adjList[nextIdx][j]->dst] == 0)
			{
				flag[adjList[nextIdx][j]->dst] = 1;
				distance[adjList[nextIdx][j]->dst] = adjList[nextIdx][j]->wt;
			}
			else if (flag[adjList[nextIdx][j]->dst] == 1)
			{
				if (distance[adjList[nextIdx][j]->dst] > adjList[nextIdx][j]->wt)
					distance[adjList[nextIdx][j]->dst] = adjList[nextIdx][j]->wt;
			}
		}
	}
	
	cout << ret;

}