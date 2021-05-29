// 백준 2581번 소수

#include <iostream>
using namespace std;

int M, N, sum{ 0 }, minPrime{ -1 };
bool IsPrime = true;

int main()
{
	cin >> M;
	cin >> N;

	for (int i = M; i <= N; i++)
	{
		for (int f = 2; f < i; f++)
		{
			int tmp = i % f;
			if (!(i % f))
			{
				IsPrime = false;
				break;
			}
		}
		if (IsPrime && i != 1)
		{
			sum += i;
			if (minPrime == -1) minPrime = i;
		}
		else IsPrime = true;
	}
	if (sum == 0) cout << -1;
	else cout << sum << endl << minPrime;


	return 0;
}