// 백준 1026번 보물

// input: 행렬의 크기 N, M (1 <= N, M <= 50)
//		  행렬 A, 행렬 B

// condition: 행렬의 변환-3x3부분행렬을 요소를 모두 뒤집는다. (0->1, 1->0)
//			  최소한의 행렬의 변환으로 A를 B로 만들어라. 단, 바꿀 수 없는 경우 -1 출력

// 원소 하나를 기준으로 변환을 계속한다. 만약 대상 원소가 B와 같다면 더이상 변환하지 않는다.
// 원소 하나를 해결한 후에는 그 원소는 변환 대상이 아니므로 이전의 변환에 영향을 미치지 않는다.
// 그리디 알고리즘 사용
// 
// 1. A[i, j]에 대하여 0 <= i <= N-1, 0 <= j <= M-1까지 B[i, j]와 같은 지 검사한다.
// 2. 만약 A[i, j]가 B[i, j]와 다르다면 변환한다.

#include <iostream>
using namespace std;

int main()
{
	int N, M;
	cin >> N >> M;
	bool** matA = new bool* [N];
	bool** matB = new bool* [N];
	for (int i = 0; i < N; i++)
	{
		matA[i] = new bool[M];
		string inputRow;
		cin >> inputRow;
		for (int f = 0; f < M; f++)
			matA[i][f] = inputRow[f] - '0';
	}

	for (int i = 0; i < N; i++)
	{
		matB[i] = new bool[M];
		string inputRow;
		cin >> inputRow;
		for (int f = 0; f < M; f++)
		{
			matB[i][f] = inputRow[f] - '0';
		}
	}

	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < M; f++)
		{
			if (matA[i][f] != matB[i][f] && i + 2 < N && f + 2 < M)
			{
				cnt++;
				for (int k = 0; k < 3; k++)
				{
					for (int j = 0; j < 3; j++)
					{
						matA[i + k][f + j] = !matA[i + k][f + j];
					}
				}
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < M; f++)
		{
			if(matA[i][f] != matB[i][f])
			{
				cout << -1;
				return 0;
			}
		}
	}

	cout << cnt;


	for (int i = 0; i < N; i++)
	{
		delete[] matA[i];
		delete[] matB[i];
	}
	delete[] matA;
	delete[] matB;
}
