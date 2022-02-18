// 백준 2156번 포도주 시식

// input: 1 <= n = 포도주 잔 수 <= 10,000 (자연수)
//		   포도주의 양 0 <= x <= 1,000 (정수)

// condition: 1) 포도주를 선택하면 그 잔에 들어있는 모든 양을 마셔야 하고 마신 후에는 원래 위치에 놓아야 한다.
//			  2) 연속으로 놓여있는 3잔은 마실 수 없다.

// 2579와 유사
// case 1) 이번 포도주를 먹는 경우
//			OXO : DP[i-2] + A[i]
//			XXO : DP[i-3] + A[i]
//			XOO : DP[i-3] + A[i-1] + A[i]
//			이므로 두번째는 세번째보다 무조건 작으니 계산에서 제외한다.
// case 2) 이번 포도주를 안 먹는 경우
//			조건에 위배될 일이 없으므로 DP[i - 1] 번째와 같다.
// 이 중 최대의 경우를 구한다.

#include <iostream>
using namespace std;

int maxInt(int _a, int _b)
{
	return (_a > _b ? _a : _b);
}

int main()
{
	int n;
	cin >> n;
	if (n == 1)
	{
		int one;
		cin >> one;
		cout << one;
	}
	else if (n == 2)
	{
		int one, two;
		cin >> one >> two;
		cout << one + two;
	}
	else if (n > 2)
	{
		int* arr = new int[n + 1];
		int* memoziation = new int[n + 1];
		memoziation[0] = arr[0] = 0;
		
		cin >> arr[1];
		cin >> arr[2];
		memoziation[1] = arr[1];
		memoziation[2] = arr[1] + arr[2];
		for (int i = 3; i < n + 1; i++)
		{
			cin >> arr[i];
			int max = 0;
			// drink arr[i]
			max = maxInt(memoziation[i - 2] + arr[i], memoziation[i - 3] + arr[i - 1] + arr[i]);
			// don't drink
			max = maxInt(max, memoziation[i - 1]);

			memoziation[i] = max;
		}
		cout << memoziation[n];

		delete[] arr;
	}
}