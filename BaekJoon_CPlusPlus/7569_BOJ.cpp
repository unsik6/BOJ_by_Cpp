// 백준 7569번 토마토

// input: M * N 매트릭스 (2 <= M, N, H <= 100)
//		  상자에 담긴 토마토의 정보 입력: 1 = 익음, 0 = 익지 않음, -1 = 토마토 없음
// 
// condition: 익은 토마토와 인접한 토마토는 하루 후에 익는다.
//			  며칠이 지나야 모두 익는가?

// 7576의 3차원 버젼

#include<iostream>
#include<queue>
using namespace std;

int neverExplored = 1000001;
int pmR[] = {-1, 1, 0, 0, 0, 0};
int pmC[] = { 0, 0, -1, 1, 0, 0 };
int pmH[] = { 0, 0, 0, 0, -1, 1 };

int PosToInt(int _h, int _c, int _colSize, int _r, int _rowSize)
{
	return (_h * _colSize * _rowSize) + (_c * _rowSize) + _r;
}

int main()
{
	int M, N, H;
	cin >> M >> N >> H;


	queue<int> explored;
	int*** cube = new int** [H];
	int*** lvlCube = new int** [H];
	for (int h = 0; h < H; h++)
	{
		cube[h] = new int* [N];
		lvlCube[h] = new int* [N];
		for (int n = 0; n < N; n++)
		{
			cube[h][n] = new int[M];
			lvlCube[h][n] = new int[M];

			for (int m = 0; m < M; m++)
			{
				cin >> cube[h][n][m];
				if (cube[h][n][m] == -1)
					lvlCube[h][n][m] = -1;
				else if (cube[h][n][m] == 0)
					lvlCube[h][n][m] = neverExplored;
				else
				{
					lvlCube[h][n][m] = 0;
					explored.push(PosToInt(h, n, N, m, M));
				}
			}
		}
	}

	while (!explored.empty())
	{
		int cur = explored.front();
		int curRow = cur % M;
		int curCol = ((cur - curRow) / M) % N;
		int curHei = (cur - curRow - curCol * M) / (N * M);
		explored.pop();

		for (int i = 0; i < 6; i++)
		{
			if (curRow + pmR[i] >= 0 && curRow + pmR[i] < M
				&& curCol + pmC[i] >= 0 && curCol + pmC[i] < N
				&& curHei + pmH[i] >= 0 && curHei + pmH[i] < H)
			{
				if (cube[curHei + pmH[i]][curCol + pmC[i]][curRow + pmR[i]] == 0
					&& lvlCube[curHei + pmH[i]][curCol + pmC[i]][curRow + pmR[i]]
				> lvlCube[curHei][curCol][curRow] + 1)
				{
					lvlCube[curHei + pmH[i]][curCol + pmC[i]][curRow + pmR[i]] =
						lvlCube[curHei][curCol][curRow] + 1;
					explored.push(PosToInt(curHei + pmH[i], curCol + pmC[i], N, curRow + pmR[i], M));
				}
			}
		}
	}
	
	int max = 0;
	for (int h = 0; h < H; h++)
	{
		for (int n = 0; n < N; n++)
		{
			for (int m = 0; m < M; m++)
			{
				if (lvlCube[h][n][m] == neverExplored)
				{
					max = -1;
					cout << max;
					return 0;
				}
				if (lvlCube[h][n][m] > max)
					max = lvlCube[h][n][m];
			}
		}
	}

	cout << max;


	for (int h = 0; h < H; h++)
	{
		for (int n = 0; n < N; n++)
		{
			delete[] cube[h][n];
			delete[] lvlCube[h][n];
		}
		delete[] cube[h];
		delete[] lvlCube[h];
	}
	delete[] cube;
	delete[] lvlCube;
}