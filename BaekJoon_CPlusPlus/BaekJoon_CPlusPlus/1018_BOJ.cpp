// 백준 1018번 체스판 다시 칠하기

// input: 8 <= (M, N) <= 50
//		  이후 각 보드의 행

// condition: 8*8 체스 보드판을 만들 때 칠해야 하는 최소 수

// 브루트포스 알고리즘: 가능한 또는, 유의미한 케이스들을 모두 검사하는 것이다.
// 체스판을 만드는 2가지 경우를 저장하고, if문을 통해 비교한다.
// 만약 원하는 시작칸(좌상단 기준)이 B라면 B로 시작하는 저장된 체스판을,
// 아니라면 W로 시작하는 저장된 체스판을 검사한다.

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// set the sample board
	char** bBoard = new char*[8];
	char** wBoard = new char* [8];
	bool checkForFor = false;
	for (int i = 0; i < 8; i++)
	{
		checkForFor = !checkForFor;
		bBoard[i] = new char[8];
		wBoard[i] = new char[8];
		for (int f = 0; f < 8; f++)
		{
			if (checkForFor)
			{
				bBoard[i][f] = 'B';
				wBoard[i][f] = 'W';
			}
			else
			{
				bBoard[i][f] = 'W';
				wBoard[i][f] = 'B';
			}
			checkForFor = !checkForFor;
		}
	}

	int N, M;
	cin >> N >> M;
	char** board = new char* [N];
	for (int i = 0; i < N; i++)
	{
		board[i] = new char[M];
		for (int f = 0; f < M; f++)
			cin >> board[i][f];
	}
	
	vector<int> v_cnt;	// save the counts of cases
	for (int i = 0; i < N - 7; i++)
	{
		for (int f = 0; f < M - 7; f++)
		{
			for (int bw = 0; bw < 2; bw++)
			{
				char** target = (bw == 0 ? bBoard : wBoard);
				int countOfCase = 0;
				// compare target(sample board) and the part of board started with (i, f)
				for (int k = 0; k < 8; k++)
					for (int j = 0; j < 8; j++)
						if (board[i + k][f + j] != target[k][j]) countOfCase++;
				v_cnt.push_back(countOfCase);
			}
		}
	}
	int min = v_cnt[0];
	for (int& v : v_cnt)
		min = (min > v ? v : min);
	cout << min;
}
