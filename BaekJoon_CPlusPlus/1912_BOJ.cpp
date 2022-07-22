// 백준 1912번 연속합

// input: 1 <= n = 정수의 개수<= 100,000
//		  -1,000 <= x <= 1,000

// condition: 연속하는 합의 최대 값

// dp[i]는 a[i]를 맨끝으로 하는 연속된 부분수열의 합이다.
// dp[i-1] + a[i]이지만,
// dp[i-1] + a[i] < a[i]라면 굳이 가져올 필요가 없으므로, a[i]가 된다.
// 이 경우, dp[i-1]은 a[i]를 만나기 전까지의 최대이므로
// a[i]를 포함하는 a[i]보다 낮은 수열의 합의 최대를 포함한다.
// a[i]를 중간에 포함하거나, 첫번째로 포함하는 부분수열의 합은 dp[j] (i <= j)이다.

#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;

	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	int* dp = new int[n];
	dp[0] = arr[0];
	int totalMax = dp[0];
	for (int i = 1; i < n; i++)
	{
		int max = dp[i - 1] + arr[i];
		if (max < arr[i]) max = arr[i];

		dp[i] = max;
		if (totalMax < dp[i]) totalMax = dp[i];
	}

	cout << totalMax;
}
