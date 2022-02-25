// 백준 2178번 미로탐색

// input: N * M 매트릭스 (2 <= N, M <= 100)
// 
// condition: 0이면 막힌 길, 1이면 뚫린 길

#include <iostream>
#include <queue>
using namespace std;

int shortestLengthOfPath(bool** _maze, int _row, int _col, int _startRow, int _startCol, int _endRow, int _endCol)
{
	queue<int> willExplore;
	willExplore.push(_startRow * _col + _startCol);
	int curlvl = 1;
	int curLvlVerticesCnt = 1;
	int nextLvlVerticesCnt = 0;
	while (!willExplore.empty())
	{
		int cur = willExplore.front();
		willExplore.pop();
		int curCol = cur % _col;
		int curRow = (cur - curCol) / _col;

		_maze[curRow][curCol] = false;

		if (curRow == _endRow && curCol == _endCol) break;
		
		if (curRow > 0)
		{
			if (_maze[curRow - 1][curCol])
			{
				_maze[curRow - 1][curCol] = false;
				willExplore.push((curRow - 1) * _col + curCol);
				nextLvlVerticesCnt++;
			}
		}
		if (curRow < _row - 1)
		{
			if (_maze[curRow + 1][curCol])
			{
				_maze[curRow + 1][curCol] = false;
				willExplore.push((curRow + 1) * _col + curCol);
				nextLvlVerticesCnt++;
			}
		}
		if (curCol > 0)
		{
			if (_maze[curRow][curCol - 1])
			{
				_maze[curRow][curCol - 1] = false;
				willExplore.push(curRow * _col + (curCol - 1));
				nextLvlVerticesCnt++;
			}
		}
		if (curCol < _col - 1)
		{
			if (_maze[curRow][curCol + 1])
			{
				_maze[curRow][curCol + 1] = false;
				willExplore.push(curRow * _col + (curCol + 1));
				nextLvlVerticesCnt++;
			}
		}

		// check lvl
		if (--curLvlVerticesCnt == 0)
		{
			curlvl++;
			curLvlVerticesCnt = nextLvlVerticesCnt;
			nextLvlVerticesCnt = 0;
		}
	}

	return curlvl;
}

int main()
{
	int N, M;
	cin >> N >> M;

	bool** maze = new bool* [N];
	for (int i = 0; i < N; i++)
	{
		maze[i] = new bool[M] {false};
		string inputRow;
		cin.ignore();
		cin.clear();
		cin >> inputRow;
		for (int f = 0; f < M; f++)
			maze[i][f] = inputRow[f] - '0';
	}
	
	cout << shortestLengthOfPath(maze, N, M, 0, 0, (N - 1), (M - 1));

	for (int i = 0; i < N; i++) delete[] maze[i];
	delete[] maze;
}