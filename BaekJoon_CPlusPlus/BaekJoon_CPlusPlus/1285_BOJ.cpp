// 백준 1258번 동전 뒤집기

// input: 행렬의 한 변의 길이 N (1 <= N <= 20, 자연수)
//		  각 행의 동전의 상태 (H = 앞면, T = 뒷면)

// condition: 가능한 행위: 1개의 행 또는 열에 있는 모든 동전들을 뒤집는다.

// output: 최소한의 뒷면만 보이도록 했을 때, 최소한의 뒷면 동전의 수

// 각 행의 뒤집기에 따라 열의 뒤집기가 결정된다.
// 다만, 문제는 어떤 행을 어떻게 뒤집느냐에 따라 열의 뒤집기가 전부 달라지므로,
// 행과 열의 뒤집기를 동시에 진행할 수 없다.
// 예를 들어 1행과 1열을 어떻게 뒤집든
// 2행과 2열을 어떻게 뒤집느냐에 따라서 1행과 1열의 뒤집는 방식이 다라질 수 있다.
// 대신 행을 뒤집는 모든 경우에 수에 대해서는
// 각각의 열에 대해 그리디 알고리즘으로 해결할 수 있다.
// 이 문제를 풀기 위해서 비트마스킹을 공부했다.

#include <iostream>
#include <math.h>
using namespace std;

int minT(int* _rowsBit, int _size, int _curRow)
{
	// 재귀는 _curRow가 _size일 때 끝난다. 즉 더이상 고려할 행의 경우의 수가 없다.
	// 각 열을 뒤집는 경우와 뒤집지 않는 경우를 계산한다.
	if (_curRow == _size)
	{
		int total = 0;
		for (int i = 0; i < _size; i++)
		{
			int not_flip_col_cnt = 0;
			for (int j = 0; j < _size; j++)
			{
				if (_rowsBit[j] & (1 << i))
				{
					not_flip_col_cnt++;
				}
			}

			total += min(not_flip_col_cnt, _size - not_flip_col_cnt);
		}

		return total;
	}

	int not_flip_row = minT(_rowsBit, _size, _curRow + 1);

	// call by pointer이기 때문에 아래처럼 뒤집어주면 앞으로도 계속 뒤집힌 상태로 연산하게 된다.
	// 하지만 결국 모든 경우의 수를 판단할 수 있게 되므로 상관 없다.
	_rowsBit[_curRow] = ~_rowsBit[_curRow];
	int flip_row = minT(_rowsBit, _size, _curRow + 1);

	return min(not_flip_row, flip_row);
}

int main()
{
	int N;
	cin >> N;
	
	// 각 row 별로 비트마스크를 만든다.	
	int* rowsBitMask = new int[N] {0};
	for (int i = 0; i < N; i++)
	{
		string row;
		cin >> row;
		for (int j = 0; j < N; j++)
		{
			if (row[j] == 'T')
			{
				// 1 << j는 j번째 비트만 1로 하는 경우로,
				// i번째 row의 비트마스크의 j번째 비트를 1로 바꾸주는 것을 의미한다.
				rowsBitMask[i] |= (1 << j);
			}
		}
	}

	cout << minT(rowsBitMask, N, 0);


	delete[] rowsBitMask;
	return 0;
}
