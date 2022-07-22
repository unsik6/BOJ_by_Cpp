// 백준 1712번 손익분기점

// Input: 1 <= A = 고정비용, B = 가변비용, C = 가격 <= 21억
// condition: 손익분기점이 나타나지 않으면 -1

#include<iostream>
using namespace std;

int main()
{
	int A, B, C;
	cin >> A >> B >> C;
	if (B >= C) cout << -1;
	else cout << A / (C - B) + 1;
	return 0;	
}