// 백준 11054번 가장 긴 바이토닉 부분 수열

// input: 1 <= N = 수열의 길이 <= 1,000 (자연수)
//		  1 <= Ai <= 1,000

// condition:  바이토닉수열: 1) 증가하는 수열, 2) 감소하는 수열, 3) 증가하다가 감소하는 수열

// dp[i]는 Ai를 포함하는 부분수열 중 바이토닉 수열의 최대 길이라고 생각하자.
// Ai를 포함하는 바이토닉 수열은 Ai보다 앞에서는 증가수열, Ai보다 뒤에서는 감소수열인 경우를 더하는 것이다.
// 여기서 -1을 해줘야 하는데 Ai가 겹치기 때문이다.
// 만약 단순한 증가 또는 감소 수열이라고 하더라도, 반대편이 0이 되므로 성립한다.


#include<iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int* arr = new int[N + 1];
	int** dp = new int*[N + 1];
	for (int i = 0; i < N + 1; i++)
		dp[i] = new int[3];
	arr[0] = dp[0][0] = dp[0][1] = dp[0][2] = 0;
	// dp[i][0]: 증가수열, dp[i][1]: 감소수열, dp]i][2]: 바이토닉 수열

	// 먼저 증가부분수열들을 구해보자.
	for (int i = 1; i < N + 1; i++)
	{
		cin >> arr[i];
		dp[i][0] = 0;
		for (int f = i - 1; f > 0; f--)
		{
			if (arr[i] > arr[f] && dp[i][0] < dp[f][0])
			{
				dp[i][0] = dp[f][0];
			}
		}
		dp[i][0]++;
	}

	// 이제 반대로 감소부분수열들을 찾아보자. 모든 과정을 반대로 해준다.
	for (int i = N; i > 0; i--)
	{
		dp[i][1] = 0;
		for (int f = i + 1; f < N + 1; f++)
		{
			if (arr[i] > arr[f] && dp[i][1] < dp[f][1])
				dp[i][1] = dp[f][1];
		}
		dp[i][1]++;
	}

	// 마지막으로 각각 더해서 바이토닉 수열의 최장 길이를 찾는다.
	int max = 0;
	for (int i = 1; i < N + 1; i++)
	{
		dp[i][2] = dp[i][0] + dp[i][1] - 1;
		if (max < dp[i][2])
			max = dp[i][2];
	}

	cout << max;
}
