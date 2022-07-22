// 백준 2231번 분해합

// input: 1 <= N <= 1,000,000

// condition: 분해합 = [N + N의 각 자리수의 합] 이때, 생성자 = N

// 브루트포스 알고리즘: 가능한 또는, 유의미한 케이스들을 모두 검사하는 것이다.

#include<iostream>
using namespace std;

int sum(int n)
{
	int sum = n;
	while (n != 0)
	{
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int main()
{
	int N, result{ 0 };
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		if (N == sum(i))
		{
			result = i;
			break;
		}
	}
	cout << result << endl;
}