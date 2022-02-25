// 백준 7576번 토마토

// input: M * N 매트릭스 (2 <= M, N <= 1,000)
//		  상자에 담긴 토마토의 정보 입력: 1 = 익음, 0 = 익지 않음, -1 = 토마토 없음
// 
// condition: 익은 토마토와 인접한 토마토는 하루 후에 익는다.
//			  며칠이 지나야 모두 익는가?

// 아이디어 도출
// 처음에 입력받은 익은 토마토들이 모두 BFS의 시작점이라고 생각한다.
// 모든 익은 토마토들에 대해서 BFS를 진행하고, lvl을 부여한다.
// 이때 처음에 입력받은 익은 토마토들에 따라 레벨이 다를 수 있으므로 가장 낮은 레벨을 부여한다.
// 레벨을 부여하면서 레벨의 최대값을 찾는다.
// BFS는 O(N * M)이기 때문에 총 실행은 O((N * M)^2)이며 초당 1억번의 실행을 한다고 하면 10000초가 소모된다.
// 
// 이를 줄이려면 첫번째 외의 BFS에서 제한을 걸면 된다.
// 첫번째에는 일반적인 BFS를 진행한다.
// 두번째부터는 BFS를 진행할 때, 어떤 정점이 기존의 레벨보다 높거나 같다면,
// 그 정점을 기준으로는 더 진행하지 않아도 된다.
// 왜냐하면 해당 정점보다 더 깊은 정점은 무조건 기존의 레벨보다 높기 때문이다.
// 그러면 결국 탐색시 겹치는 토마토가 급격하게 줄어들며, 겹치는 경우가 가장 많은 최악의 경우에는 O(N*M /2)이므로
// O(N*M)시간에 수행할 수 있다.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int NeverExplored = 10000001;

int main()
{
	int N, M;
	cin >> N >> M;

	vector<int> firstRipen;
	int** mat = new int* [M];
	for (int i = 0; i < M; i++)
	{
		mat[i] = new int[N] {-1};
		for (int f = 0; f < N; f++)
		{
			cin >> mat[i][f];
			if (mat[i][f] == 1)
				firstRipen.push_back(i * N + f);
		}
	}

	int** lvlMat = new int* [M];
	for (int i = 0; i < M; i++)
	{
		lvlMat[i] = new int[N];
		for (int f = 0; f < N; f++)
		{
			if (mat[i][f] == 1) lvlMat[i][f] = 0;
			else if (mat[i][f] == -1) lvlMat[i][f] = -1;
			else lvlMat[i][f] = NeverExplored;
		}
	}

	// start BFS to all firstRipen
	for (int start : firstRipen)
	{
		queue<int> explored;
		explored.push(start);
		int nextLvl = 1;
		int curLvlElemsCnt = 1;
		int nextLvlElemCnt = 0;
		while (!explored.empty())
		{
			int curVertex = explored.front();
			int curCol = curVertex % N;
			int curRow = (curVertex - curCol) / N;
			explored.pop();
			curLvlElemsCnt--;

			if (curRow > 0)
			{
				if (mat[curRow - 1][curCol] == 0
					&& lvlMat[curRow - 1][curCol] > nextLvl)
				{
					lvlMat[curRow - 1][curCol] = nextLvl;
					explored.push((curRow - 1) * N + curCol);
					nextLvlElemCnt++;
				}
			}
			if (curRow < M - 1)
			{
				if (mat[curRow + 1][curCol] == 0
					&& lvlMat[curRow + 1][curCol] > nextLvl)
				{
					lvlMat[curRow + 1][curCol] = nextLvl;
					explored.push((curRow + 1) * N + curCol);
					nextLvlElemCnt++;
				}
			}
			if (curCol > 0)
			{
				if (mat[curRow][curCol - 1] == 0
					&& lvlMat[curRow][curCol - 1] > nextLvl)
				{
					lvlMat[curRow][curCol - 1] = nextLvl;
					explored.push(curRow * N + (curCol - 1));
					nextLvlElemCnt++;
				}
			}
			if (curCol < N -1)
			{
				if (mat[curRow][curCol + 1] == 0
					&& lvlMat[curRow][curCol + 1] > nextLvl)
				{
					lvlMat[curRow][curCol + 1] = nextLvl;
					explored.push(curRow * N + (curCol + 1));
					nextLvlElemCnt++;
				}
			}

			if (curLvlElemsCnt == 0)
			{
				nextLvl++;
				curLvlElemsCnt = nextLvlElemCnt;
				nextLvlElemCnt = 0;
			}
		}
	}
	int max = 0;
	for (int i = 0; i < M; i++)
	{
		for (int f = 0; f < N; f++)
		{
			if (lvlMat[i][f] == NeverExplored)
			{
				max = -1;
				break;
			}
			else if (max < lvlMat[i][f]) max = lvlMat[i][f];
		}
	}
		

	cout << max;




	for (int i = 0; i < M; i++)
	{
		delete[] mat[i];
		delete[] lvlMat[i];
	}
	delete[] mat;
	delete[] lvlMat;
}