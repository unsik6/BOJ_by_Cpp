// 백준 7562번 나이트 이동

// input: T = 테스트 케이스
//		  각 테스트 케이스 별로
//			체스판 한 변의 길이 I (4 <= I <= 300), 체스판의 좌표 = {0 .. I-1}{0 .. I-1}
//			나이트 좌표, 목표 좌표
// 
// condition: 체스판의 나이트의 움직임과 같다.

#include <iostream>
#include <queue>
using namespace std;

struct position
{
	int x = -1;
	int y = -1;
};
int neverExplored = 100000;
int pmX[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int pmY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };


int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int I;
		cin >> I;
		int** board = new int* [I];
		for (int i = 0; i < I; i++)
		{
			board[i] = new int[I];
			for (int f = 0; f < I; f++)
			{
				board[i][f] = neverExplored;
			}
		}

		int kniX, kniY, tarX, tarY;
		cin >> kniX >> kniY >> tarX >> tarY;
		position start;
		start.x = kniX;
		start.y = kniY;

		board[kniX][kniY] = 0;

		queue<position> explored;
		explored.push(start);
		
		while (!explored.empty())
		{
			position cur = explored.front();
			explored.pop();
			for (int p = 0; p < 8; p++)
			{
				position next;
				next.x = cur.x + pmX[p];
				next.y = cur.y + pmY[p];
				if (next.x >= 0 && next.x < I
					&& next.y >= 0 && next.y < I)
				{
					if (board[next.x][next.y] > board[cur.x][cur.y] + 1)
					{
						board[next.x][next.y] = board[cur.x][cur.y] + 1;
						explored.push(next);
					}
				}
			}

		}

		cout << board[tarX][tarY] << '\n';


		for (int i = 0; i < I; i++)
		{
			delete[] board[i];
		}
		delete[] board;
	}
}