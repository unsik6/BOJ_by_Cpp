// 백준 2565번 전깃줄

// input: 1 <= N = 전깃줄의 개수 <= 100 (자연수)
//		  각 전깃줄의 A 기둥 번호, B 기둥 번호

// condition: 서로 평행이고 높이가 같은 전봇대A와 B가 있다.
//			  각 전봇대는 위에서부터 높이마다 1부터 번호가 매겨져 있다.
//			  해당 위치 번호는 500 이하의 자연수이다.
//			  같은 위치에 2개의 전깃줄을 설치할 수 없다.
//			  전깃줄이 꼬이지 않기 위해 최소 몇개의 전깃줄을 제거해야 하는가?

// 1개의 기둥을 기준으로 보면 수열이 된다.
// A를 기준으로 해보자. 수열 A의 인덱스는 전봇대 A의 위치, 값은 연결된 전봇대 B의 위치이다.
// i번째 전깃줄이 꼬이지 않으려면, 1<= i2 < i인 위치의 A[i2]는 A[i]보다 작아야 한다.
// 마찬가지로 i < i3 <= 500인 위치의 A[i3]은 A[i]보다 커야 한다.
// 즉 증가하는 부분 순열의 길이를 전체 전깃줄 길이 만큼 뺀 값이 줄이는 전깃줄의 개수이다.

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int* arr = new int[n];
	int* dp = new int[n];

	// A에서의 위치는 상대적 크기가 중요하지, 진짜 인덱스가 중요한 것은 아니다.
	// A의 위치에 맞춰 B에 연결된 위치를 정렬해준다.
	int* pos = new int[501];
	for (int i = 0; i < 501; i++) pos[i] = -1;
	for (int i = 0; i < n; i++)
	{
		int A, B;
		cin >> A >> B;
		pos[A] = B;
	}
	int Bidx = 0;
	for (int i = 0; i < 501; i++)
	{
		if (pos[i] > 0)
		{
			arr[Bidx] = pos[i];
			Bidx++;
		}
	}
	delete[] pos;

	// 증가하는 부분수열의 최장 길이 구하기
	int max = 0;
	dp[0] = 1;
	for (int i = 1; i < n; i++)
	{
		dp[i] = 0;
		for (int f = i; f >= 0; f--)
		{
			if (arr[i] > arr[f] && dp[i] < dp[f])
			{
				dp[i] = dp[f];
			}
		}
		dp[i]++;
		if (max < dp[i]) max = dp[i];
	}

	cout << n - max;

	delete[] arr;
	delete[] dp;
}