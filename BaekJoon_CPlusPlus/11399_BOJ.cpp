// 백준 11399번 ATM

// input: 1 <= N = 사람의 수 <= 1,000
//		  1 <= 각 사람이 돈 뽑는데 걸리는 시간 Pi <= 1,000

// condition: i번째 줄을 서있는 사람이 돈 뽑는데 걸리는 시간 Sk = sum(Pk | 1 <= k <= Pk)
//			  사람들의 줄을 세울 때 sum(Sk | 1 <= k <= n)의 최소값을 구하여라

// i가 작을 수록 더 많이 더해지므로 앞에 설 수록 작은 숫자여야 한다.

#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int* arr = new int[N];
	for (int i = 0; i < N; i++)
		cin >> arr[i];

	sort(arr, arr + N);

	int sum = 0;
	int minTotal = 0;
	for (int i = 0; i < N; i++)
	{
		sum += arr[i];
		minTotal += sum;
	}

	cout << minTotal;
}