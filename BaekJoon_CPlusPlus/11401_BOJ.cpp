// 백준 11401번 이항계수3

// input: 1 <= N = 자연수 <= 4,000,000 , 0 <= K = 정수 <= N

// condition: 이항계수 Combination(N, K)를 1,000,000,007로 나눈 수

// ref: https://st-lab.tistory.com/241, https://m.blog.naver.com/hongjg3229/221650178981

#include <iostream>
using namespace std;

#define PRIME 1000000007
typedef unsigned long long ULL;

ULL pow(ULL _a, ULL _b, ULL _c)
{
	if (_b == 0) return 1;
	else
	{
		if (_b % 2 > 0) return (pow(_a, _b - 1, _c) * (_a % _c)) % _c;
		else
		{
			ULL result = pow(_a, _b / 2, _c) % _c;
			return (result * result) % _c;
		}
	}
}

ULL solute(ULL _N, ULL _K, ULL _P)
{
	ULL top = 1;
	ULL bottom = 1;
	for (int i = 1; i <= _N; i++)
	{
		top *= i;
		top %= _P;
	}
	for (int i = 1; i <= _K; i++)
	{
		bottom *= i;
		bottom %= _P;
	}
	for (int i = 1; i <= _N - _K; i++)
	{
		bottom *= i;
		bottom %= _P;
	}

	ULL bottom2 = pow(bottom, _P - 2, _P);
	ULL result = top * bottom2;
	result %= _P;
	return result;
}

int main()
{
	ULL N, K;
	cin >> N >> K;
	cout << solute(N, K, PRIME);
}