/* 백준 16298번 뱀과 사다리 게임
*
* Input: 10x10 보드판
*		 사다리 수 N (1 <= N <= 15) (정보: x < y, (x, y != 1, 100) : x -> y)
*		 뱀 수 (1 <= M <= 15)	(정보: u > v : u -> v)

* Output: 1에서 시작하여 100에 도착하는 최소 주사위 굴리는 횟수
*
* 최단 경로 문제이다. 단, 주사위로 전진만 가능하다는 점과 사다리와 뱀에 의해 이미 방문한 지점을 재방문해야 최단 경로가 나올 수 있다.
* 그러므로 flag를 사용하지 않는다.
*/

#include <iostream>
#include <queue>

using namespace std;

int dis[101];

int ladders[101]{ 0 };		//ladders[x] = y
int snakes[101]{ 0 };		// snakes[u] = v

struct cmp
{
	bool operator()(int _a, int _b)
	{
		{
			return (dis[_a] < dis[_b]);
		}
	}
};


int main()
{
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;
		ladders[x] = y;
	}
	for (int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		snakes[u] = v;
	}
	for (int i = 0; i < 101; i++)
		dis[i] = 10000;

	priority_queue<int, vector<int>, cmp> pq;
	pq.push(1);
	dis[1] = 0;

	while (!pq.empty())
	{
		int cur = pq.top();
		pq.pop();

		for (int dice = 1; dice < 7; dice++)
		{
			int dst = cur + dice;

			// 100 지점을 넘어가면 더이상 진행할 수 없다.
			if (dst > 100) continue;

			// 사다리와 뱀에 의해 목적지가 바뀌는 경우
			if (snakes[dst] != 0)
				dst = snakes[dst];
			else if (ladders[dst] != 0)
				dst = ladders[dst];

			if (dis[dst] > dis[cur] + 1)
			{
				dis[dst] = dis[cur] + 1;
				pq.push(dst);
			}
		}
	}

	cout << dis[100];

	return 0;
}