/* 백준 1602 도망자 원숭이
*
*Input: 도시의 수 N (2 <= N <= 500)
*		도로의 수 M (0 <= M <= 10,000)
*		쿼리의 수 Q (0 <= Q <= 40,000)
*		도시 i에서 멍멍이가 원숭이를 괴롭힐 수 있는 시간 b_i (1 <= b_i <= 10,000)
*		도로 i의 정보 a_i, b_i, d_i (1 <= a_i, b_i <= N, 1 <= d_i <= 10,000)
*		쿼리 i의 정보 s_i, b_i (1<= s_i, b_i <= N)

* Output: 각 쿼리의 최단 경로의 비용 (불가능한 경우 -1)
*/

#include <iostream>
#include <algorithm>

using namespace std;

#define INF 1e9

// input
int N, M, Q;
int graph[501][501]{ 0 };
pair<int, int> bullyTime[501];
int maxBullyTime[501][501]{ 0 };

void input()
{
	cin >> N >> M >> Q;
	for (int n = 1; n <= N; n++)
	{
		cin >> maxBullyTime[n][n];
		bullyTime[n].first = maxBullyTime[n][n];
		bullyTime[n].second = n;
	}
		

	// init graph
	for (int i = 1; i <= N; i++)
	{
		graph[i][i] = 0;
		for (int j = 1; j <= N; j++)
		{
			if (i != j)
				graph[i][j] = INF;
		}
	}

	for (int m = 0; m < M; m++)
	{
		int a, b, d;
		cin >> a >> b >> d;
		if (a == b)
			continue;

		if (graph[a][b] > d)
		{
			graph[b][a] = graph[a][b] = d;
			maxBullyTime[a][b] = maxBullyTime[b][a] =
				max(maxBullyTime[a][a], maxBullyTime[b][b]);
		}
	}

	sort(bullyTime + 1, bullyTime + 1 + N);
}

void constructFW()
{
	for (int k = 1; k <= N; k++)
	{
		int via = bullyTime[k].second;
		int viaBully = bullyTime[k].first;

		for (int s = 1; s <= N; s++)
		{
			if (s == via) continue;
			for (int e = 1; e <= N; e++)
			{
				if (e == s || e == via) continue;
				int new_bully = max(maxBullyTime[s][via], maxBullyTime[via][e]);

				int new_cost = graph[s][via] + graph[via][e] + new_bully;
				int ori_cost = graph[s][e] + maxBullyTime[s][e];

				if (new_cost < ori_cost)
				{
					graph[s][e] = graph[e][s] = graph[s][via] + graph[via][e];
					maxBullyTime[s][e] = maxBullyTime[e][s] = new_bully;
				}
			}
		}
	}
}

void wholeQuery()
{
	for (int q = 0; q < Q; q++)
	{
		int s, t;
		cin >> s >> t;
		if (graph[s][t] >= INF)
			cout << -1 << '\n';
		else cout << graph[s][t] + maxBullyTime[s][t] << '\n';
	}
}

int main()
{
	input();
	constructFW();
	wholeQuery();
	return 0;
}