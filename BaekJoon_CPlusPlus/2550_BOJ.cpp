/* 백준 2550번 전구
*
* Input: 스위치와 전구 쌍의 수 (1 <= N <= 10,000)
*		 N개 스위치의 순서대로의 번호 x_i (1 <= x_i <= 10,000, x_i != x_j)
*		 N개 전구의 순서대로의 번호 x_i (1 <= x_i <= 10,000, x_i != x_j)

* Output: 스위치 번호와 전구 번호가 같다면 전선이 연결되어 있음을 의미한다.
*		  전선이 교차하는 두 스위치는 동시에 작동시킬 수 없다.
*		  
*		  전구가 가장 많이 켜지는 경우에 대하여,
*		  켜진 전구의 수와,
*		  켜진 전구들에 대응하는 스위치의 번호를 오름차순으로 출력하시오.
*
* LIS 문제이다.
* 스위치들을 작동시켰을 때, 모든 전선이 교차하지 않는 경우는 스위치의 위치 순서(오름차순)에 따라 전구의 위치도 오름차순인 경우이다.
* 그러므로 전구의 위치 순으로 스위치의 위치를 저장하고, 그에 대한 LIS를 구한다.
* 전봇대 문제와 동일하나, LIS를 재구성해야 한다는 점이 다르다.
*/

#include <iostream>
#include <algorithm>

using namespace std;


int switch_pos[10001];
int bulb_no[10000];
int bulb_idx[10000];
int lis_len[10000];
int pre[10000];
bool turn_on[10001]{ false };

int main()
{
	// input
	int N;
	cin >> N;
	int num;
	for (int i = 0; i < N; i++)
	{
		cin >> num;
		switch_pos[num] = i;
	}
	for (int i = 0; i < N; i++)
	{
		cin >> num;
		bulb_idx[i] = switch_pos[num];
		bulb_no[i] = num;
	}

	int max_idx = 0;
	int max_len = 0;
	for (int i = 0; i < N; i++)
	{
		lis_len[i] = 1;
		pre[i] = i;
		for (int j = 0; j < i; j++)
		{
			if (bulb_idx[j] < bulb_idx[i])
			{
				// 더 긴 경우
				if (lis_len[i] < lis_len[j] + 1)
				{
					lis_len[i] = lis_len[j] + 1;
					pre[i] = j;
				}
			}
		}
		if (max_len < lis_len[i])
		{
			max_len = lis_len[i];
			max_idx = i;
		}
	}

	// backtrack the LIS
	int cur = max_idx;
	turn_on[bulb_no[max_idx]] = true;
	while (cur != pre[cur])
	{
		cur = pre[cur];
		turn_on[bulb_no[cur]] = true;
	}

	// output
	cout << max_len << '\n';
	for (int i = 1; i <= N; i++)
	{
		if (turn_on[i])
			cout << i << ' ';
	}
}