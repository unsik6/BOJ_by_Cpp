// 백준 2740번 행렬 곱셈

// input: 1<= N, M, K = 행렬의 한 변의 크기 <= 100
//        |각 원소| <= 100 인 정수

// condition: A[N x M]과 B[M x k] 곱

#include<iostream>
using namespace std;

void multipleMatrix(int** _a, int _aRow, int _aCol, int** _b, int _bRow, int _bCol, int** _c)
{
	for (int i = 0; i < _aRow; i++)
	{
		for (int f = 0; f < _bCol; f++)
		{
			int tmp = 0;
			for (int k = 0; k < _aCol; k++)
			{
				tmp += (_a[i][k] * _b[k][f]);
			}

			_c[i][f] = tmp;
		}
	}
}

int main()
{
	int N, M, K;
	cin >> N >> M;
	int** A = new int* [N];
	for (int i = 0; i < N; i++)
	{
		A[i] = new int[M];
		for (int f = 0; f < M; f++)
			cin >> A[i][f];
	}

	cin >> M >> K;
	int** B = new int* [M];
	for (int i = 0; i < M; i++)
	{
		B[i] = new int[K];
		for (int f = 0; f < K; f++)
			cin >> B[i][f];
	}

	int** C = new int* [N];
	for (int i = 0; i < N; i++)
	{
		C[i] = new int[K];
		for (int f = 0; f < K; f++)
			C[i][f] = 0;
	}
	
	multipleMatrix(A, N, M, B, M, K, C);

	for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < K; f++)
			cout << C[i][f] << ' ';
		cout << '\n';
	}


	for (int i = 0; i < N; i++)
	{
		delete[] A[i];
		delete[] C[i];
	}
	delete[] A;
	delete[] C;

	for (int i = 0; i < M; i++)
	{
		delete[] B[i];
	}
	delete[] B;
}