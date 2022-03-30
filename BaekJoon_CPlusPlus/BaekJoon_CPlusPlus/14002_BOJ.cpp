/* 백준 14002번 가장 긴 증가하는 부분 수열4

input : 수열 A의 크기 N (1 <= N <= 1,000)
		수열 A를 이루는 Ai (1 <= Ai <= 1,000)

output: 가장 긴 증가하는 부분 수열의 길이와 그 증가하는 부분 수열을 출력하라.
		만약 solution이 여러개라면 그중 아무거나 출력해도 된다.


가장 긴 증가하는 부분 수열의 길이를 구하는 알고리즘은 11053번 문제를 통해 구현했다.

<11053 풀이>
DP로 구현한다.
N 크기의 DP 배열을 만드는데 이 배열은 i번째 요소까지의 가장 긴 부분 수열이다.
i = [0..N-1], f = [0..i-1]이라고 하자.
각 i에 대해서 검사를 하는데 만약 dp[f]가 dp[i]보다 크고, A[i]가 A[f]보다 작다면
증가하는 부분 수열이므로 dp[f]에 dp[i]를 넣고 최종적으로 +1을 해준다.
dp[f]를 0으로 초기화한다면, A[f]로만 증가하는 부분 수열인 경우에도 위 반복이 성립한다.

<14002의 추가사항>
11053은 단순히 길이만을 출력했다.
하지만 14002는 부분 수열을 구성해야 하므로, 이를 위한 저장을 해야 한다.
N*N 크기의 행렬을 만들고, 각 dp[i]에 대하여 어떤 구성 요소들이 필요한지 저장한다.
*/

#include <iostream>
using namespace std;

int A[1000];
int dp[1000]{ 0 };
bool mat[1000][1000]{ 0 };

int main()
{
	// input
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	// initialize
	dp[0] = 1;
	mat[0][0] = true;

	// iteration
	int maxIdx = 0; // 0~maxIdx까지에서의 증가하는 부분 수열이 최대인 경우, 전체에서 최대이다.
	for (int i = 1; i < N; i++)
	{
		int preIdx = -1;	// 어떤 부분수열에 A[i]를 붙여서 만들어지는 지를 저장
		for (int f = i - 1; f >= 0; f--)
		{
			if (A[i] > A[f] && dp[i] < dp[f])
			{
				preIdx = f;
				dp[i] = dp[f];
			}
		}
		dp[i]++;
		if (dp[maxIdx] < dp[i]) maxIdx = i;

		// 부분 수열 요소 구현
		for (int k = 0; k <= preIdx; k++)
		{
			mat[i][k] = mat[preIdx][k];
		}
		mat[i][i] = true;
	}

	// output
	cout << dp[maxIdx] << '\n';
	for (int i = 0; i <= maxIdx; i++)
	{
		if (mat[maxIdx][i]) cout << A[i] << ' ';
	}

	return 0;
}