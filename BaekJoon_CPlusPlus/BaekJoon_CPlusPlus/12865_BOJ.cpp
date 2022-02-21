// 백준 12865번 평범한 배낭

// input: 1 <= N = 물품 개수 <= 100
//		  1 <= K = 최대무게 <= 100,000
//		  각 물건의 1 <= W(무게) <= 100,000
//					0 <= V(가치) <= 1,000

// condition: 가치 합의 최대값

// dp[i][j] = i번째 물건까지 확인하며, 가방의 무게가 j인 경우의 가치합의 최대값
// 경우 1( j < obj[i] ): 물건을 애초에 넣을 수가 없다.
// 경우 2( j >= obj[i]): 물건을 넣을 수 있다.
//						경우2-1: 물건을 안 넣는다. dp[i - 1][j]
//						경우2-2: 물건을 넣는다.
//								 i-1번째 물건까지로 j - weight[i]만큼의 무게를 만들어주고, 현재(i번째)를 넣는다.
//								 dp[i - 1][j - weight[i]] + value[i]


#include<iostream>
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	int* objsWeight = new int[N + 1];
	int* objValue = new int[N + 1];

	for (int i = 1; i < N + 1; i++)
		cin >> objsWeight[i] >> objValue[i];

	int** dp = new int*[N + 1];
	for (int i = 0; i < N + 1; i++)
		dp[i] = new int[K + 1];

	for (int i = 0; i < K + 1; i++) dp[0][i] = 0;
	for (int i = 0; i < N + 1; i++) dp[i][0] = 0;

	for (int i = 1; i < N + 1; i++)
	{
		for (int f = 1; f < K + 1; f++)
		{
			if (f >= objsWeight[i])
			{
				dp[i][f] = dp[i - 1][f];
				if (dp[i][f] <= dp[i - 1][f - objsWeight[i]] + objValue[i])
					dp[i][f] = dp[i - 1][f - objsWeight[i]] + objValue[i];
			}
			else dp[i][f] = dp[i - 1][f];
		}
	}

	cout << dp[N ][K];

	for (int i = 0; i < N + 1; i++)
		delete[] dp[i];
	delete[] dp;
}