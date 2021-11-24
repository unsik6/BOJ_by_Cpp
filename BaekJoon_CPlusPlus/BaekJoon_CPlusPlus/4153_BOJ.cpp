// 백준 4153번 직각삼각형

// input: T = 테스트 케이스, 1 <= 각 변의 길이 3개 <= 30,000 (양의 정수)

// 피타고라스의 법칙인지 확인
// 소수점도 파악해야 하므로 실수형 사용

#include<iostream>
using namespace std;

int main()
{
	while (true)
	{
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 0 && b == 0 && c == 0) return 0;
		int temp = 0;
		if (a > c)
		{
			temp = c;
			c = a;
			a = temp;
		}
		if (b > c)
		{
			temp = c;
			c = b;
			b = temp;
		}
		if (c * c == a * a + b * b) cout << "right\n";
		else cout << "wrong\n";
	}
	return 0;
}


// 이거 왜 틀린건지를 모르겠다.
/*
#include<iostream>
#include<vector>
using namespace std;

int main()
{
	while (true)
	{
		vector<int> v;
		for (int i = 0; i < 3; i++)
		{
			int e;
			cin >> e;
			v.push_back(e);
		}
		if (v[0] == 0 && v[1] == 0 && v[2] == 0) return 0;

		int maxIndex = 0;
		if (v[0] < v[1]) maxIndex = 1;
		if (v[1] < v[2]) maxIndex = 2;
		int maxPow = 0, notMaxPowSum = 0;
		for (int i = 0; i < 3; i++)
		{
			if (i == maxIndex) maxPow += v[i] * v[i];
			else notMaxPowSum += v[i] * v[i];
		}
		if (maxPow == notMaxPowSum) cout << "right\n";
		else cout << "wrong\n";
	}
	return 0;
}
*/