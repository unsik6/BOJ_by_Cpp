/* 백준 15972 물탱크
*
* Input: 물탱크의 세로길이 N, 가로 길이 M, 높이 H (1 <= N, M, H <= 1,000)
*		 첫번째 가로벽에 설치된 구멍 정보를 나타내는 M개의 정수
*			순서대로 각 칸의 구멍 높이 h (0 <= h < H, 구멍 없으면 -1)
*		 가로벽 i를 공유하는 칸들의 세로벽 순서대로 구멍의 높이들

* Output: 물이 더 이상 흘러나가지 않는 시점에서 남아있는 물의 양
*/
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0);
#define MAX 1'004	// 가장 바깥쪽 테두리는 물탱크 밖인데 인풋 넣을 때 귀찮아져서 한 칸 더 추가
#define pii pair<int, int>

// input
int N, M, H;
void input();


// partition info
// partitions[row][col][1,2,3,4 = 상하좌우]
int partitions[MAX][MAX][4];
int heights[MAX][MAX]{ 0 };

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// 좌표 이동
int dRow[4] = { -1, 1, 0, 0 };
int dCol[4] = { 0, 0, -1, 1 };
int RC_to_Offset(int _r, int _c) { return _r * MAX + _c; }
pii Offset_to_RC(int _os) { return {_os / MAX, _os % MAX}; }

// Solution - 다익스트라
priority_queue<pii, vector<pii>, greater<pii>> PQ_Part;	// {height, Offset}
void solution();

// Debugging
void check();

int main()
{
	FAST_IO
	input();
	solution();
	return 0;
}

void input()
{
	cin >> N >> M >> H;
	
	// 가로벽 (상단이라고 생각하고 입력 받음)
	for (int n = 1; n <= N + 1; n++)
	{
		for (int m = 1; m <= M; m++)
		{
			cin >> partitions[n][m][UP];
			partitions[n - 1][m][DOWN] = partitions[n][m][UP];
		}
	}

	// 세로벽 (좌측이라고 생각하고 입력 받음)
	for (int n = 1; n <= N; n++)
	{
		for (int m = 1; m <= M + 1; m++)
		{
			cin >> partitions[n][m][LEFT];
			partitions[n][m - 1][RIGHT] = partitions[n][m][LEFT];
		}
	}

	// 물 채우기
	for (int n = 1; n <= N; n++)
	{
		for (int m = 1; m <= M; m++)
			heights[n][m] = H;
	}
}

void solution()
{
	// preprocessing 1. 가장자리 칸들 높이 조정하면서 PQ에 삽입
	// 1) 상하 칸 확인
	for (int m = 1; m <= M; m++)
	{
		// 윗줄의 위쪽 구멍이 있음
		if (partitions[1][m][UP] != -1)
		{
			if (heights[1][m] > partitions[1][m][UP])
			{
				heights[1][m] = partitions[1][m][UP];
				PQ_Part.push({ heights[1][m], RC_to_Offset(1, m) });
			}
		}
			
		// 아랫줄의 아래쪽 구멍이 있음
		if (partitions[N][m][DOWN] != -1)
		{
			if (heights[N][m] > partitions[N][m][DOWN])
			{
				heights[N][m] = partitions[N][m][DOWN];
				PQ_Part.push({ heights[N][m], RC_to_Offset(N, m) });
			}
		}
	}
	// 2) 좌우 칸 확인
	for (int n = 1; n <= N; n++)
	{
		// 좌측줄의 왼쪽 구멍이 있음
		if (partitions[n][1][LEFT] != -1)
		{
			if (heights[n][1] > partitions[n][1][LEFT])
			{
				heights[n][1] = partitions[n][1][LEFT];
				PQ_Part.push({ heights[n][1], RC_to_Offset(n, 1) });
			}
		}
		if (partitions[n][M][RIGHT] != -1)
		{
			if (heights[n][M] > partitions[n][M][RIGHT])
			{
				heights[n][M] = partitions[n][M][RIGHT];
				PQ_Part.push({ heights[n][M], RC_to_Offset(n, M) });
			}
		}
	}

	while (!PQ_Part.empty())
	{
		pii curRC = Offset_to_RC(PQ_Part.top().second);
		int curHeight = PQ_Part.top().first;
		PQ_Part.pop();

		// 방문확인
		if (heights[curRC.first][curRC.second] != curHeight)
			continue;

		for (int i = 0; i < 4; i++)
		{
			if (partitions[curRC.first][curRC.second][i] == -1)
				continue;
			int nextR = curRC.first + dRow[i];
			int nextC = curRC.second + dCol[i];
			
			if (nextR < 1 || nextR > N || nextC < 1 || nextC > M)
				continue;
			int next_height = max(heights[curRC.first][curRC.second], 
				min(partitions[curRC.first][curRC.second][i], heights[nextR][nextC]));
			if (heights[nextR][nextC] > next_height)
			{
				heights[nextR][nextC] = next_height;
				PQ_Part.push({ next_height, RC_to_Offset(nextR, nextC) });
			}
		}
	}

	// 합치기
	int sum = 0;
	for (int n = 1; n <= N; n++)
		for (int m = 1; m <= M; m++)
			sum += heights[n][m];

	cout << sum;
}

void check()
{
	cout << "\nCHECK\n";
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			cout << "[" << r << "][" << c << "] : {";
			for (int i = 0; i < 4; i++)
			{
				cout << partitions[r][c][i] << ", ";
			}
			cout << "} H = ";
			cout << heights[r][c];
			cout << '\n';
		}
	}
}