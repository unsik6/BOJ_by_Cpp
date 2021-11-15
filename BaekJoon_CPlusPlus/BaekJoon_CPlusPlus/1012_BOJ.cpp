// 백준 1012번 유기농 배추

// Input: T = 테스트 케이스의 개수, M = 배추밭 가로 길이, N = 배추밭 새로 길이, K = 배추 위치 개수
//			  (1 <= N, M <= 50) (1 <= K <= 2500)
//			  (X, Y) = 배추 좌표 (0 <= x, y < M, N)
// condition: 배추는 한칸에 한 마리
//			  배추가 상하좌우로 붙어 있으면 인접


// DFS 알고리즘
// 혼자서 했을 때는 재귀함수로 했음.
// 나중에 알고리즘 제대로 공부할 때 참고

#include<iostream>
using namespace std;

void Change(bool**, int, int, int, int);

int main()
{
	int T, M, N, K;
	cin >> T;
	for(int t = 0; t < T; t++)
	{
		cin >> M >> N >> K;
		bool** field = new bool*[N];
		for (int n = 0; n < N; n++)
		{
			field[n] = new bool[M];
			for (int m = 0; m < M; m++)
				field[n][m] = 0;
		}
		
		int x, y;
		for(int k = 0; k < K; k++)
		{
			cin >> x >> y;
			field[y][x] = 1;
		}

		int regionCnt = 0;
		x = 0, y = 0;
		while (true)
		{
			if (field[y][x] == 1)
			{
				Change(field, M, N, x, y);
				regionCnt++;
			}
			if (x == M - 1)
			{
				if (y == N - 1) break;
				else
				{
					x = 0;
					y++;
				}
			}
			else x++;
		}

		cout << regionCnt << "\n";
	}
}

void Change(bool** _f, int _m, int _n, int _x, int _y)
{
	if (_f[_y][_x] == 0) return;
	
	_f[_y][_x] = 0;
	if (_y - 1 >= 0)
		Change(_f, _m, _n, _x, _y - 1);
	if (_y + 1 < _n)
		Change(_f, _m, _n, _x, _y + 1);
	if (_x - 1 >= 0)
		Change(_f, _m, _n, _x - 1, _y);
	if (_x + 1 < _m)
		Change(_f, _m, _n, _x + 1, _y);
}