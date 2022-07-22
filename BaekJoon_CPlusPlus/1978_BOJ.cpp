// 백준 1978번 소수 찾기

// Input: 1<= N = 입력받을 숫자의 개수 <= 100, N개의 1000 이하의 양의 정수

// 소수는 1과 자기 자신만으로 
// (N/2 +1)까지 나눠본다.

#include<iostream>
using namespace std;

int main()
{
	int T, cnt{ 0 };
	bool IsPrime = true;
	cin >> T;
	int* nums = new int[T];
	for (int i = 0; i < T; i++) cin >> nums[i];
	for (int t = 0; t < T; t++)
	{
		if (nums[t] == 1) IsPrime = false;
		for (int i = 2; i < (nums[t] / 2) + 1; i++)
		{
			if (!(nums[t] % i))
			{
				IsPrime = false;
				break;
			}
		}
		if (IsPrime) cnt++;
		else IsPrime = true;
	}
	cout << cnt << endl;
}