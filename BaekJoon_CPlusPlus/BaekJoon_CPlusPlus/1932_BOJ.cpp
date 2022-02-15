// 백준 1932번 정수삼각형

// input: 1 <= n = 삼각형의 크기(높이) <= 500 (자연수)
//		  각 줄마다 위에서부터 아래로 삼각형인 정수들이 주어진다. (0 <= x <= 9999)

// condition: 위에서부터 내려오되, 현재 선택한 정수의 대각선 왼쪽 또는 오른쪽 아래만 선택하며 내려올 수 있다.

// matrix로 memoziation
// row가 각 층이다.

#include <iostream>
using namespace std;


int main()
{
	int n;
	cin >> n;

	int max = 0;
	int** mat = new int* [n];
	for (int i = 0; i < n; i++)
	{
		mat[i] = new int[n];
		for (int f = 0; f <= i; f++)
		{
			cin >> mat[i][f];

			// first level don't have previous level
			if (i > 0)
			{
				// the first number of each level only from the first number of previous level
				if (f == 0)
					mat[i][f] += mat[i - 1][f];
				// the last number of each level only from the last number of previous level
				else if (f == i)
					mat[i][f] += mat[i - 1][f - 1];
				// else, the number of each level can be computed from 2 numbers of previous level
				else
				{
					int first = mat[i][f] + mat[i - 1][f - 1];
					int second = mat[i][f] + mat[i - 1][f];
					mat[i][f] = (first > second ? first : second);
				}
			}
			max = (mat[i][f] > max ? mat[i][f] : max);
		}
	}

	cout << max;
}