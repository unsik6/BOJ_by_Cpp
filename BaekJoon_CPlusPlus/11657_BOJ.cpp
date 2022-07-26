/* 백준 11657번 타임머신
*
* Input: <첫번째 줄>
			도시의 개수 N (1 <= N <= 500)
*			버스 노선의 개수 M (1<= M <= 6,000)
*		 <두번째 줄 ... >
*			각 줄에 버스 노선의 정보 A, B, C (1 <= A, B <= N, -10,000 <= C <= 10,000)
*
* Output: 1번 도시에서 출발하여,
		  만약 무한히 과거로 가는 경우가 있다면 -1를 출력
*		  아닌 경우, 각 도시에 가는데 걸리는 시간을 줄로 구분하여 출력 (경로 없으면 -1)
* 
* Point:
*		가중치가 음수로 치달을 경우, 즉 음수 사이클이 발생한 경우 음수 쪽에서 오버플로우가 발생할 수 있으니 long을 사용한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 999999999

vector<pair<int, int>> adjacentLists[501];
long distances[501];

int main()
{
	int n, m, src, dst, wht;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> src >> dst >> wht;
		adjacentLists[src].push_back(make_pair(dst, wht));
	}

	// 초기화
	for (int i = 2; i <= n; i++)
		distances[i] = INF;
	distances[1] = 0;


	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 0; k < adjacentLists[j].size(); k++)
			{
				if (distances[j] == INF) continue;
				else
				{
					long newD = distances[j] + adjacentLists[j][k].second;
					if (newD < distances[adjacentLists[j][k].first])
					{
						distances[adjacentLists[j][k].first] = newD;
					}
				}
			}
		}
	}

	for (int j = 1; j <= n; j++)
	{
		for (int k = 0; k < adjacentLists[j].size(); k++)
		{
			if (distances[j] == INF) continue;
			else
			{
				long newD = distances[j] + adjacentLists[j][k].second;
				if (newD < distances[adjacentLists[j][k].first])
				{
					cout << -1;
					return 0;
				}
			}
		}
	}

	for (int i = 2; i <= n; i++)
	{
		if (distances[i] == INF) cout << -1 << '\n';
		else cout << distances[i] << '\n';
	}
	
	return 0;
}