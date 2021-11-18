// 백준 2775번 부녀회장이 될테야

// Input: T = 테스트 케이스, 1 <= k, n <= 14 (k층 n호)
// condition: a층 b호에 입주하려면 (a-1)층의 1호부터 b호까지의 사람의 합 만큼 사람이 살아야한다.
//			  비어있는 집은 없다.
//			  아파트는 0층부터 있으며 1호부터 있다. 0층 i호에는 i만큼 산다.

// 단순합, n호 이상은 신경쓰지 않아도 된다.

#include<iostream>
using namespace std;

int main()
{
	int T;
	cin >> T;
	int* ks = new int[T];
	int* ns = new int[T];
	for (int i = 0; i < T; i++)
		cin >> ks[i] >> ns[i];
	for (int i = 0; i < T; i++)
	{
		int* prefloor = new int[ns[i]]{ 0 };
		int* targetfloor = new int[ns[i]]{ 0 };
		for (int k = 0; k < ns[i]; k++) prefloor[k] = k + 1;
		for (int f = 1; f <= ks[i]; f++)
		{
			for (int j = 0; j < ns[i]; j++)
				for (int p = ns[i] - 1; p >= j; p--)
					targetfloor[p] += prefloor[j];
			for (int j = 0; j < ns[i]; j++)
			{
				prefloor[j] = targetfloor[j];
				targetfloor[j] = 0;
			}
		}
		cout << prefloor[ns[i] - 1] << endl;
	}
}
