// 백준 1436번 영화감독슘

// input: 1 <= N = 순서(자연수) <= 10,000

// condition: 6이 3개 이상 연속으로 들어가는 수

// 브루트포스 알고리즘: 가능한 또는, 유의미한 케이스들을 모두 검사하는 것이다.

#include<iostream>
using namespace std;

int main()
{
	int N, cnt{ 0 }, number{ 665 };
	cin >> N;
	
	while (cnt < N)
	{
		number++;
		int tmp = number;
		bool isSequence = false;
		int sequenceCnt = 0;
		while (tmp != 0)
		{
			int digit = tmp % 10;

			// is digit 6?
			if (digit == 6) isSequence = true;
			else isSequence = false;
			if (isSequence) sequenceCnt++;
			else sequenceCnt = 0;

			if (sequenceCnt == 3)
			{
				cnt++;
				break;
			}

			tmp /= 10;
		}
	}

	cout << number;
}