// 백준 2798번 블랙잭

// input: 3 <= N <= 100 : 카드의 수, 10 <= M <= 300,000 : 목표 숫자
//						  카드들

// condition: 3장의 카드를 뽑아 만들 수 있는 (<= M) 중에 가장 큰 수를 호출한다.
//			  이 경우가 가능한 조합의 카드들만 주어진다.

// 브루트포스 알고리즘: 가능한 또는, 유의미한 케이스들을 모두 검사하는 것이다.

#include<iostream>
using namespace std;

int main()
{
	int N, M, result{ 0 }, max{ 0 };
	cin >> N >> M;
	int* deck = new int[N];
	for (int i = 0; i < N; i++) cin >> deck[i];
	for (int i = 0; i < N; i++)
	{
		for (int f = i + 1; f < N; f++)
		{
			for (int k = f + 1	; k < N; k++)
			{
				if (deck[i] + deck[f] + deck[k] <= M)
				{
					result = deck[i] + deck[f] + deck[k];
					max = (result > max ? result : max);
				}
			}
				
		}


	}
	cout << max;
}