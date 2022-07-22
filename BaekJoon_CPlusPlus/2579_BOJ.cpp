// 백준 2579번 계단 오르기

// input: 1 <= n = 주어지는 계단의 수 <= 300 (자연수)
//		  각 계단의 점수. (1 <= x <= 10000) (자연수)

// condition: 1) 한번에 1개 또는 2개의 계단 오르기 가능
//			  2) 연속된 3개의 계단을 모두 밟을 수 없음.
//			  3) 첫번째는 계단으로 취급하지 않음. 마지막 계단은 무조건 밟아야 함.

// 총 점수의 최댓값을 출력하라.

// 하나의 problem의 문제는 2칸 전이냐 1칸 전이냐이다.
// 1칸 전인 경우에는 이전 칸에서 1칸만 건넌 경우는 할 수 없다.
// 2칸 전인 경우에는 2칸 이전의 칸에서 최대값을 가져오면 된다.

// 3열짜리 배열을 생성한다.
// arr[n][0]은 그 칸의 점수이다.
// arr[n][1]은 1칸 전인 경우
// arr[n][2]은 2칸 전인 경우이다.

#include <iostream>
using namespace std;


int main()
{
	int n;
	cin >> n;
	int** stairsNScores = new int*[n + 1];

	for (int i = 0; i < n + 1; i++)
	{
		stairsNScores[i] = new int[3];
	}
	for (int i = 0; i < 3; i++)
	{
		stairsNScores[0][i] = 0;
	}
	for (int i = 1; i < n + 1; i++)
	{
		cin >> stairsNScores[i][0];
		if (i == 1)
		{
			for (int f = 1; f < 3; f++) stairsNScores[i][f] = stairsNScores[i][0];
		}
		else
		{
			stairsNScores[i][1] = stairsNScores[i][0] + stairsNScores[i - 1][2];
			stairsNScores[i][2] = stairsNScores[i][0] +
				(stairsNScores[i - 2][1] > stairsNScores[i - 2][2] ? stairsNScores[i - 2][1] : stairsNScores[i - 2][2]);
		}
	}

	cout << (stairsNScores[n][1] > stairsNScores[n][2] ? stairsNScores[n][1] : stairsNScores[n][2]);
}