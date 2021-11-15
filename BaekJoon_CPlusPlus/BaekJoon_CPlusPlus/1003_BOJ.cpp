// 백준 1003번 피보나치

// 재귀함수인 피보나치 수열을 호출할 때, fibonacci(0)과 fibonacci(1)이
// 호출되는 횟수를 구하라.

/*
int fibonacci(int n) {
	if (n == 0) {
		printf("0");
		return 0;
	} else if (n == 1) {
		printf("1");
		return 1;
	} else {
		return fibonacci(n‐1) + fibonacci(n‐2);
	}
}
*/

// 각각을 c0, c1이라고 할 때, c0와 c1은 각각 피보나치 수열이다.

// 결과 및 의의: 코드를 짜기 전에 생각을 먼저 하자.

#include<iostream>
using namespace std;

int main()
{
	// 테스트 수를 받는다.
	int T;
	cin >> T;
	// fibonacci(0)이 호출되는 수인 피보나치 수열을 저장할 배열
	int c0[41] = { 1, 0 };
	// fibonacci(1)이 호출되는 수인 피보나치 수열을 저장할 배열
	int c1[41] = { 0, 1 };
	// 둘다 미리 피보나치 수열을 넣어준다.
	for (int i = 2; i <= 40; i++)
	{
		c0[i] = c0[i - 2] + c0[i - 1];
		c1[i] = c1[i - 2] + c1[i - 1];
	}
	// 각각의 테스트 케이스에서의 n을 받아서 넣을 배열
	int* arrN = new int[T];
	// 테스트 케이스 마다 n 받기
	for (int i = 0; i < T; i++)
		cin >> arrN[i];
	// 미리 만들어둔 c0, c1 수열에서 n에 해당하는 것을 찾아온다.
	for (int i = 0; i < T; i++)
		cout << c0[arrN[i]] << " " << c1[arrN[i]] << endl;
	return 0;
}