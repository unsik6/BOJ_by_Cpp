// 백준 2869번 달팽이는 올라가고 싶다.

// Input: 1 <= B = 미끄러짐 <= A = 올라감 <= V = 목표 <=1,000,000,000
// condition: 낮에는 A만큼 올라가고 밤에는 B 만큼 미끄러진다.

#include<iostream>
using namespace std;

int main()
{
	int A, B, V;
	cin >> A >> B >> V;
	cout << ((V - B) % (A - B) == 0 ? (V - B) / (A - B) : ((V - B) / (A - B) + 1));
}