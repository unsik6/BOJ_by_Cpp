// 백준 11053번 가장 긴 증가하는 부분 수열

// input: 1 <= N = 수열의 크기 <= 1,000 (자연수)
//		  수열의 1 <= Ai <= 1,000 (정수)

// condition:  가장 긴 증가하는 부분수열

// 길이가 짧은 것부터 시작하여, 생성된 부분수열들의 길이와 마지막 값이 가장 작은 값을 유지한다.

#include<iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int* arr = new int[N + 1];
	int* memo = new int[N + 1];
	arr[0] = memo[0] = 0;
	int max = 0;
	for (int i = 1; i < N + 1; i++)
	{
		cin >> arr[i];
		memo[i] = 0;
		for (int f = i - 1; f > 0; f--)
		{
			if (arr[i] > arr[f] && memo[i] < memo[f])
			{
				memo[i] = memo[f];
			}
		}
		memo[i]++;
		if (max < memo[i]) max = memo[i];
	}
	cout << max;
}