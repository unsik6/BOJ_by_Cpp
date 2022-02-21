// 백준 1912번 연속합

// input: 1 <= n = 정수의 개수<= 100,000
//		  -1,000 <= x <= 1,000

// condition: 연속하는 합의 최대 값


// [n, n] 매트릭스를 이용한다. [i, j]는 i부터 j까지의 부분 수열의 합이다. (0 <= i <= j <= n-1)

#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;

	int** mat = new int* [n];
	for (int i = 0; i < n; i++)
	{
		mat[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		//  [i, i]이므로 a[i]가 최대합이다.
		cin >> mat[i][i];
	}

	for (int i = 1; i < n; i++)
	{
		for (int f = i - 1; f >= 0; f--)
		{
			int max = mat[i - 1][f];
			if (max < mat[i][f + 1]) max = mat[i][f + 1];
			int sum = 0;
			for (int k = f; k <= f; k++)
				sum += mat[k][k];
			if (max < sum) max = sum;

			mat[i][f] = max;
		}
	}
	cout << mat[n - 1][n - 1];
}
