// 백준 1904번 타일01

// input: 1 <= N = 비트 스트링 개수 <= 1,000,000

// condition: '00'과 '1'으로 만들 수 있는 비트 스트링

// 1 = {1}, 2 = {00, 11}이다.
// 길이가 1 늘어나면 N-1에 1을 붙인 형태 또는 N-2에 00을 붙인 형태가 나온다.
// 즉, 피보나치 수열과 같다.
// 피보나치 수열에 따른 값이 굉장히 크므로 페르마의 소정리를 이용한다.

#include <iostream>
using namespace std;

int main()
{
	long long N;
	cin >> N;

	long long* arr = new long long[1000001];
	arr[1] = 1;
	arr[2] = 2;
	for (int i = 3; i <= N; i++)
	{
		arr[i] = (arr[i - 2] + arr[i - 1]) % 15746;
	}
	cout << arr[N];
}