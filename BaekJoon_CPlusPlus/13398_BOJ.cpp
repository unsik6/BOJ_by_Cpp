// 백준 13398번 트리의 부모 찾기

// input: 수열의 크기 (1 <= n <= 100,000)
//		  수열의 요소 (-1,000 <= x <= 1,000)
// 
// condition: 수열에서 1개를 제거할 수 있다.

// 일반적인 연속합 문제와 동일하다.
// 다만 벽뚫고 지나가기 문제처럼 해당 요소를 제거할지 안 할지가 중요하다.

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int* sequence = new int[n];
	for (int i = 0; i < n; i++) cin >> sequence[i];

	// no destroy element
	int* dp1 = new int[n] {0};
	// destroy element
	int* dp2 = new int[n] {0};
	dp1[0] = sequence[0];
	dp2[0] = 0;

	int max = dp1[0];

	for (int i = 1; i < n; i++)
	{
		// dp1
		if (dp1[i - 1] + sequence[i] < sequence[i])
		{
			dp1[i] = sequence[i];
		}
		else
		{
			dp1[i] = dp1[i - 1] + sequence[i];
		}


		// dp2
		if (dp1[i - 1] > dp2[i - 1] + sequence[i])
		{
			dp2[i] = dp1[i - 1];
		}
		else
		{
			dp2[i] = dp2[i - 1] + sequence[i];
		}

		if (max < dp1[i]) max = dp1[i];
		if (max < dp2[i]) max = dp2[i];
	}

	cout << max;


	delete[] sequence;
	delete[] dp1;
	delete[] dp2;
}