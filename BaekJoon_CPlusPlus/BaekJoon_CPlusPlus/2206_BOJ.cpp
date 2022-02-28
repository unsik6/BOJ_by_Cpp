// 백준 2206번 벽 부수고 이동

// input: N x M 행렬 (1<= N, M <= 1,000)
//		  0인 경우 길, 1인 경우 벽
// 
// condition: (1, 1)부터 (N, M)까지 최단 거리 (단, 벽을 1회 부술 수 있다.)

#include <iostream>
#include <queue>
using namespace std;

struct vertex
{
	int x = -1;
	int y = -1;
	bool isBrokenWall = false;
};

int neverExplored = 1000001;
int pmX[4] = { -1, 1, 0, 0 };
int pmY[4] = { 0, 0, -1, 1 };

int main()
{
	int N, M;
	cin >> N >> M;
	int** mat = new int* [N];
	int*** lenMat = new int** [N];	// lenMat[row][col][0 = no broken wall, 1 = one broken wall]
	for (int n = 0; n < N; n++)
	{
		mat[n] = new int[M];
		string inputRow;
		cin >> inputRow;
		for (int i = 0; i < M; i++)
			mat[n][i] = inputRow[i] - '0';

		lenMat[n] = new int*[M];
		for (int m = 0; m < M; m++)
		{
			lenMat[n][m] = new int[2];
			for (int i = 0; i < 2; i++) lenMat[n][m][i] = neverExplored;
		}
			
	}

	/*for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < M; f++)
			cout << mat[i][f];
		cout << endl;
	}*/

	// initiate
	lenMat[0][0][0] = 1;
	lenMat[0][0][1] = 1;

	vertex start;
	start.x = 0;
	start.y = 0;

	queue<vertex> explored;
	explored.push(start);

	// BFS
	while (!explored.empty())
	{
		vertex cur = explored.front();
		explored.pop();
		if (cur.x == N - 1 && cur.y == M - 1) break;
		for (int i = 0; i < 4; i++)
		{
			vertex next;
			next.x = cur.x + pmX[i];
			next.y = cur.y + pmY[i];
			if (next.x >= 0 && next.x < N
				&& next.y >= 0 && next.y < M)
			{
				if (mat[next.x][next.y] == 1)	// is the wall
				{
					if (cur.isBrokenWall == false)
					{
						if (lenMat[next.x][next.y][1] > lenMat[cur.x][cur.y][0] + 1)
						{
							lenMat[next.x][next.y][1] = lenMat[cur.x][cur.y][0] + 1;
							next.isBrokenWall = true;
							explored.push(next);
						}
					}
					// if isBrokenWall == true then can't move more
				}
				else    // is the path
				{
					if (lenMat[next.x][next.y][cur.isBrokenWall] > lenMat[cur.x][cur.y][cur.isBrokenWall] + 1)
					{
						lenMat[next.x][next.y][cur.isBrokenWall] = lenMat[cur.x][cur.y][cur.isBrokenWall] + 1;
						next.isBrokenWall = cur.isBrokenWall;
						explored.push(next);
					}
				}
			}
		}
	}

	int min = (lenMat[N - 1][M - 1][0] < lenMat[N - 1][M - 1][1]
		? lenMat[N - 1][M - 1][0] : lenMat[N - 1][M - 1][1]);
	if (min == neverExplored) cout << -1;
	else cout << min;

	/*cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < M; f++)
		{
			cout << lenMat[i][f][0] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < M; f++)
		{
			cout << lenMat[i][f][1] << ' ';
		}
		cout << endl;
	}*/

	for (int n = 0; n < N; n++)
	{
		delete[] mat[n];
		
		for (int m = 0; m < M; m++)
			delete[] lenMat[n][m];
		delete[] lenMat[n];
	}
	delete[] mat;
	delete[] lenMat;
}