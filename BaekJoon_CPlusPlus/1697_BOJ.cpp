// 백준 1697번 숨바꼭질

// input: 수빈의 위치 (0 <= N <= 100,000)
//		  동생의 위치 (0 <= K <= 100,000)
// 
// condition: 위치가 X일 경우, 이동 가능 위치: X + 1, X - 1, X * 2

// BFS
// X와  X + 1, X - 1, X * 2는 연결되어 있는 정점이다.
// 또한, 수빈이가 i번째 이동 후 정점이 K 초과인 경우는  (K - X / 2 - 1 > X - K)이며,
// 이때 좌항의 -1은 i번째 이동에서 X * 2하는 이동이다.
// 정리하면, K + K/3 - 2/3 > X이고, K와 X 모두 정수이기 때문에
// int 계산을 고려하여 K/3은 floor(K/3)이므로,
// K + K/3 + 2 > X 이다.

#include<iostream>
#include<queue>
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	int size = K + K / 3 + 2;
	int* route = new int[size + 1];
	for (int i = 0; i < size + 1; i++) route[i] = size + 1;
	// if N >= K then N can move only index 1
	if (N == K) cout << 0;
	else if (N > K) cout << N - K;
	else
	{
		queue<int> explored;
		explored.push(N);
		route[N] = 0;
		while (!explored.empty())
		{
			int cur = explored.front();
			explored.pop();
			if (cur - 1 > 0) // if cur == 0 then only way is cur++ because if cur < 0 then cur * 2 is more far position
			{
				if (route[cur - 1] > route[cur] + 1)
				{
					route[cur - 1] = route[cur] + 1;
					explored.push(cur - 1);
				}
			}
			if (cur + 1 <= size)
			{
				if (route[cur + 1] > route[cur] + 1)
				{
					route[cur + 1] = route[cur] + 1;
					explored.push(cur + 1);
				}
			}
			if (cur * 2 <= size)
			{
				if (route[cur * 2] > route[cur] + 1)
				{
					route[cur * 2] = route[cur] + 1;
					explored.push(cur * 2);
				}
			}
		}

		cout << route[K];
	}
}