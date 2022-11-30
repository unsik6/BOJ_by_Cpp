/* 백준 22348 헬기 착륙장
*
* Input: 테스트 케이스 수 T (1 <= T <= 10,000)
*		 빨간페인트 a통, 파란페인트 b통 (1 <= a, b <= 50,000)

* Output: 만들 수 있는 헬기 착륙장 개수
*/

#include <iostream>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL); std::cout.tie(NULL);

const int M = 1'000'000'007;

// input & output
int T, redPaint, bluePaint, caseNum;

// DP: maxRadiusByRedUse[maximum_radius][red paint usage]
#define MAX_R 502
#define MAX_PAINT 50000
int maxRadiusByRedUse[MAX_R + 1][MAX_PAINT + 1]{ 0 };
int sumOfCase[MAX_R + 1][MAX_PAINT + 1]{ 0 };

// preprocessing
void createDP()
{
	// base case [0][0]
	maxRadiusByRedUse[0][0] = 1;

	// 현재 케이스를 기준으로 만들 수 있는 [다음 원 추가 케이스]에 경우의 수를 추가
	// 원이 하나 늘어날 때 경우는 빨강을 사용하는가 안 하는가에 따라 다르다.
	// 1) 다음 원을 그릴 수 있는 경우
	//		이전 케이스에서 원의 크기만큼 더 쓸 수 있다면 현재의 경우의 수를 추가해준다.
	// 2) 다음 원을 그릴 수 없는 경우
	//		현재 사용량 만큼만 추가해준다.
	// 두 케이스는 독립이다. (빨간 페인트에만 의존)
	for (int r = 0; r < MAX_R; r++)
	{
		for (int useRed = 0; useRed <= MAX_PAINT; useRed++)
		{
			// case 1: 다음 원을 빨강으로 그릴 수 있음.
			if (useRed + r + 1 <= MAX_PAINT)
			{
				maxRadiusByRedUse[r + 1][useRed + r + 1] += maxRadiusByRedUse[r][useRed];
				maxRadiusByRedUse[r + 1][useRed + r + 1] %= M;
			}

			// case 2: 다음 원에 빨간 페인트 안 쓸거임
			maxRadiusByRedUse[r + 1][useRed] += maxRadiusByRedUse[r][useRed];
			maxRadiusByRedUse[r + 1][useRed] %= M;
		}
	}

	// 누적합 쿼리 전처리
	for (int r = 0; r <= MAX_R; r++)
	{
		sumOfCase[r][0] = maxRadiusByRedUse[r][0];
		for (int useRed = 1; useRed <= MAX_PAINT; useRed++)
			sumOfCase[r][useRed] = (sumOfCase[r][useRed - 1] + maxRadiusByRedUse[r][useRed]) % M;
	}
}

int main()
{
	FAST_IO
		createDP();
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		caseNum = 0;					// output initialization
		cin >> redPaint >> bluePaint;	// input

		for (int r = 1; r <= MAX_R; r++)
		{
			// 사용한 총 페인트 수
			int totalUsage = r * (r + 1) / 2;

			// 빨간 페인트 최소 사용량 ~ 최대 사용량까지의 합 구하기
			// 빨간 페인트 최소 사용량 = 총 사용량 - 파란 페인트 전체 사용
			// 빨간 페인트 최대 사용량 = 빨간 페인트 전체 사용
			int minRed = totalUsage - bluePaint;

			// 만들 수 없는 케이스이다.
			// 예: 3개의 원 = 6통 사용, 파란 페인트 2통, 빨간 페인트 3통
			//	   최소 사용이 4통이므로 만들 수 없다.
			if (minRed > redPaint)
				continue;

			int sumRed;
			if (minRed > 0)
				sumRed = (sumOfCase[r][redPaint] - sumOfCase[r][minRed - 1] + M) % M;
			else
				sumRed = sumOfCase[r][redPaint];

			caseNum += sumRed;
			caseNum %= M;
		}

		cout << caseNum << '\n';
	}
	return 0;
}