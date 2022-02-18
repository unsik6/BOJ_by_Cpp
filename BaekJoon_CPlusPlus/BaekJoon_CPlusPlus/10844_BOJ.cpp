// 백준 10844번 쉬운 계단수

// input: 1 <= N = 숫자의 길이 <= 100

// condition: 각 자리에 대하여 옆자리에 대해 1차이가 나는 경우, 계단수라고 함.
//			  N이 주어졌을 때, 가능한 계단수의 수

// N번의 자리에 대하여 이전 자리에서 어떤 숫자가 나오냐에 따라 이번 자리에 나오는 숫자의 케이스가 다르다.

#include<iostream>
using namespace std;

int main()
{
	int arr[10] = { 0 };
	int preArr[10] = { 0 };
	long long N;
	cin >> N;
	if (N == 1) cout << 9;
	else
	{
		for (int i = 1; i < 10; i++) preArr[i] = 1;
		while (N > 1)
		{
			arr[0] = preArr[1];
			for (int i = 1; i < 9; i++)
			{
				arr[i] = (preArr[i - 1] + preArr[i + 1]) % 1000000000;
			}
			arr[9] = preArr[8];

			for (int i = 0; i < 10; i++) preArr[i] = arr[i];
			N--;
		}

		for (int i = 1; i < 10; i++)
		{
			arr[0] += arr[i];
			arr[0] %= 1000000000;
		}
		cout << arr[0] % 1000000000;
	}
}