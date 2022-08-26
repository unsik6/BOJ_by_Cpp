/* 백준 3056번 007
*
* Input: 미션과 지미의 수 N (1 <= N <= 20)
*		 i번째 줄에 j번째 정수 = 지미본드 i가 미션 j를 성공할 확률

* Output: 모든 미션을 지미 본드에게 1개씩 나눠줬을 때 전체 미션 성공 확률이 최대가 되는 경우
*		  (오차 범위 +-0.000001)
*
* Point:
*	N이 작으므로 BF로 푼다. 이때 비트마스킹을 이용한다.
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int N, cnt, tmp;
double percent[20][20];				// 요원 별 성공 확률
double bitmask[1 << 20] = { 1, };	// 비트 마스크

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> percent[i][j];

	// 출력 설정
	cout.precision(6);
	cout << fixed;

	// 총 검사 회수는 비트 마스크의 경우의 수만큼 진행
	for (int i = 0; i < (1 << N); i++)
	{
		cnt = 0;
		tmp = i;

		// 현재 비트 수 세기 (비트 수 = 몇명의 요원이 진행했는지)
		while (tmp > 0)
		{
			// 비트가 1인 경우
			if (tmp % 2 == 1) cnt++;
			tmp /= 2;
		}

		// 어떤 미션을 진행할 것인가
		for (int j = 0; j < N; j++)
		{
			if ((i & (1 << j)) == 0)
			{
				// 그 미션을 하는 경우,
				// 새롭게 진행하는 미션을 누가 진행하는게 최대인지 계산
				bitmask[i | (1 << j)] = max(bitmask[i | (1 << j)], bitmask[i] * percent[j][cnt] / 100.0);
			}
		}
	}

	// 비트마스크가 꽉 찼을 때 = 모든 미션이 수행되었을 때의 확률
	cout << bitmask[(1 << N) - 1] * 100 << endl;
}
