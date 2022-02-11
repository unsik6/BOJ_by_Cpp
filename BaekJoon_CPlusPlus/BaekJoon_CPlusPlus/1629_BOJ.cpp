// 백준 1629번 곱셈

// input: A, B, C = 자연수 <= 2,147,483,647

// condition: A를 B번 곱한 수를 C로 나누었을 때의 나머지


#include <iostream>
using namespace std;

unsigned long long modExponential(int _a, int _b, int _c)
{
	unsigned long long mod = _a % _c;
	if (_b == 1)
		return _a % _c;
	else
	{
		if ((_b % 2))
			return modExponential(_a, _b - 1, _c) * mod % _c;
		else
			return modExponential(_a, _b / 2, _c) * modExponential(_a, _b / 2, _c) % _c;
	}
}

int main()
{
	int A, B, C;
	cin >> A >> B >> C;
	cout << modExponential(A, B, C);
}