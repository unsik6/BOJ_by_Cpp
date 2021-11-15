// 백준 1072번 게임

// Input: 1<= X = 지금까지 게임한 횟수 <= 1000,000,000, 0<= Y = 지금까지 이긴 게임 <=X
// condition: 현택이는 이제부터 지지 않음.
//			  기존 승률은 소수점 버림.


// 이진 탐색 알고리즘

#include<iostream>
using namespace std;

int main()
{
	long long X, Y;
	cin >> X >> Y;
	int Z = (Y * 100) / X;
	
	if (Z >= 99)
	{
		cout << - 1;
		return 0;
	}

	int low = 0;
	int high = 1000000000;
	int target = -1;
	while (low <= high)
	{

		int mid = (high + low) / 2;
		int tmp = ((Y + mid) * 100) / (X + mid);
		if (Z >= tmp)
		{
			target = mid + 1;
			low = mid + 1;
		}
		else
			high = mid - 1;
	}
	cout << target;
	return 0;
}