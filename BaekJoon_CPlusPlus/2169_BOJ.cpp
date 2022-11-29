/* 백준 2169 로봇 조종하기
*
* Input: 2차원 배열의 크기 N, M ( 1<= N, M <= 1,000)
*		 N 줄에 M개의 가치 k (|k| <= 100)
* 
*		 왼쪽, 오른쪽, 아래쪽으로 이동할 수 있다. (위쪽은 불가능)
*		 한번 탐사한 지역은 탐사하지 않는다.

* Output: [1,1]에서 출발하고 [N, M]에 도착했을 때 탐사한 지역들의 가치 합의 최대
*/

#include <iostream>

using namespace std;

#define MAX_SIZE 1000
#define MAX 0
#define RIGHT 1

int N, M;
int arr2_ori[MAX_SIZE][MAX_SIZE];
int arr3_max[MAX_SIZE][MAX_SIZE][2]{0};

int main()
{
	// 입력
	cin >> N >> M;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			cin >> arr2_ori[r][c];
		}
	}

	// 첫 행: 왼쪽에서 오는 것만 가능
	arr3_max[0][0][MAX] = arr2_ori[0][0];
	for (int c = 1; c < M; c++)
	{
		arr3_max[0][c][MAX] = arr3_max[0][c - 1][MAX] + arr2_ori[0][c];
	}
	// 중간 행
	for (int r = 1; r < N - 1; r++)
	{
		// 왼쪽부터 진행하는 경우
		// 먼저 가장 왼쪽에 있는 것은 위에서만 올 수 있으므로 초기화 개념
		arr3_max[r][0][MAX] = arr3_max[r - 1][0][MAX] + arr2_ori[r][0];

		// 그 다음부터는 위에서 온 경우와 왼쪽에서 온 경우의 MAX를 DP로 계산
		for (int c = 1; c < M; c++)
		{
			// 왼쪽에서 온 경우가 더 큰 경우
			if (arr3_max[r][c - 1][MAX] > arr3_max[r - 1][c][MAX])
				arr3_max[r][c][MAX] = arr3_max[r][c - 1][MAX];
			// 위에서 온 경우가 더 큰 경우
			else
				arr3_max[r][c][MAX] = arr3_max[r - 1][c][MAX];

			arr3_max[r][c][MAX] += arr2_ori[r][c];
		}

		// 오른쪽부터 진행하는 경우
		// 왼쪽과 마찬가지로 가장 오른쪽에 있는 것 먼저 초기화
		// 왼쪽에서 오는 거랑 계산한 것이 겹치면 안 되므로 별도 저장
		arr3_max[r][M - 1][RIGHT] = arr3_max[r - 1][M - 1][MAX] + arr2_ori[r][M - 1];

		// 왼쪽에서 오는 것과 동일
		for (int c = M - 2; c >= 0; c--)
		{
			// 오른쪽에서 온 경우가 더 큰 경우
			if (arr3_max[r][c + 1][RIGHT] > arr3_max[r - 1][c][MAX])
				arr3_max[r][c][RIGHT] = arr3_max[r][c + 1][RIGHT];
			// 위에서 온 경우가 더 큰 경우
			else
				arr3_max[r][c][RIGHT] = arr3_max[r - 1][c][MAX];

			arr3_max[r][c][RIGHT] += arr2_ori[r][c];;
		}

		// 최대값 비교
		for (int c = 0; c < M; c++)
		{
			if (arr3_max[r][c][RIGHT] > arr3_max[r][c][MAX])
				arr3_max[r][c][MAX] = arr3_max[r][c][RIGHT];
		}
	}
	
	// 마지막 행 처리
	// 행이 1개면 그냥 출력하면 된다.
	if (N < 2)
	{
		cout << arr3_max[N - 1][M - 1][MAX];
	}
	else
	{
		// 먼저 가장 왼쪽에 있는 것은 위에서만 올 수 있으므로 초기화 개념
		arr3_max[N - 1][0][MAX] = arr3_max[N - 2][0][MAX] + arr2_ori[N - 1][0];

		for (int c = 1; c < M; c++)
		{
			// 왼쪽에서만 올 수 있다.
			// 왼쪽에서 온 경우가 더 큰 경우
			if (arr3_max[N - 1][c - 1][MAX] > arr3_max[N - 2][c][MAX])
				arr3_max[N - 1][c][MAX] = arr3_max[N - 1][c - 1][MAX];
			// 위에서 온 경우가 더 큰 경우
			else
				arr3_max[N - 1][c][MAX] = arr3_max[N - 2][c][MAX];

			arr3_max[N - 1][c][MAX] += arr2_ori[N - 1][c];
		}

		cout << arr3_max[N - 1][M - 1][MAX];
	}

	
	return 0;
}