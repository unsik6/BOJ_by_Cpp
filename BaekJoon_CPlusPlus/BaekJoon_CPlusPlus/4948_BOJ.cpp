// 백준 1948번 베르트랑 공준

// input: 1 <= N <= 123,456

// condition: 베르트랑 공준은 임의의 자연수 n에 대하여,
//			  n보다 크고, 2n보다 작거나 같은 소수는 적어도 하나 존재한다는 내용을 담고 있다.


// 에라토스테네스의 채 문제인(1929)의 풀이를 통해 풀어본다.

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int input;
	vector<int> v_n;
	cin >> input;
	while (input != 0)
	{
		v_n.push_back(input);
		cin >> input;
	}

	for (int& n : v_n)
	{
		int size = 2 * n + 1;
		bool* numbers = new bool[size]{ false };
		int cnt = 0;
		// 에라토스테네스 채의 배열을 초기화
		for (int i = 2; i < size; i++)
			numbers[i] = true;
		// n의 제한인 123456의 제곱은 int의 범위를 넘어간다.
		for (long long i = 2; i < size; i++)
		{
			if (i * i > size)
				break;
			if (numbers[i])
				for (long long f = i * i; f < size; f += i)
					if (!(f % i)) numbers[f] = false;
		}
		for (int i = n + 1; i < size; i++)
			if (numbers[i]) cnt++;
		cout << cnt << '\n';
	}
}