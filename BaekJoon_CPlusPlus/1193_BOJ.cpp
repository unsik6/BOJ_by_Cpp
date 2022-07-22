// 백준 1193번 분수찾기

// Input: 1 <= X = 목표분수 <= 10,000,000
// condition: 유리수 분수법에 의한 행렬을 지그재그로 진행

// 홀수 분수는 분자가 감소, 분모가 증가 <= 해당 수
// 짝수 분수는 분자가 증가, 분모가 감소 <= 해당 수


#include<iostream>
using namespace std;

int main()
{
	int X, n{ 1 }, mom{ 0 }, son{ 0 };
	cin >> X;
	while (X - n > 0)
	{
		X -= n;
		n++;
	}
	mom = (n % 2 == 0 ? n - X + 1 : X);
	son = (n % 2 != 0 ? n - X + 1 : X);
	cout << son << '/' << mom;
	return 0;
}