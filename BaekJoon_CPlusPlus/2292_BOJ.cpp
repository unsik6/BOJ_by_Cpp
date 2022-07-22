// 백준 2292번 벌집

// Input: 1 <= N = 목표지점 <= 1,000,000,000
// condition: 회전하는 벌집 형태로 형성되며 1에서 시작한다.

// 껍질의 두께에 따라 진행하는 수가 늘어난다.
// 첫번째 껍질: 2 ~ 7 = 6개
// 두번째 껍질: 8 ~ 19 = 12개
// 세번째 껍질: 20 ~ 37 = 18개
// 네번째 껍질: 38 ~ 61 = 24개
// 6의 배수로 늘어난다.

#include<iostream>
using namespace std;

int main()
{
	int N, cnt{ 1 };
	cin >> N;
	while (N > 1)
	{
		N -= cnt * 6;
		cnt++;
	}
	cout << cnt;
}