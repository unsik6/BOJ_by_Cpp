/* 백준 2305 자리 배치
*
*Input: 자리의 개수 N (2 <= N <= 40)
*		자유석 번호 K (1 <= K <= N)

		(1) 자유석이 아닌 경우 지정석이다.
		(2) 지정석 번호가 i인 경우, 해당 자리를 예약한 고객은 i - 1, i + 1, i 또는 자유석에 앉을 수 있다.

* Output: 위 규칙 2개를 만족하면서 인원 전체가 앉는 모든 경우의 개수를 구하시오.
*/

/* 비트마스킹&DP 문제로의 접근
* 각 자리는 결국 '누군가 앉는다/아무도 안 앉는다'라는 선택지가 있을 뿐이므로
* 이 경우, 비트 마스킹을 통해서 풀 수 있으나 모든 케이스가 P^N_{N-1}이므로 작살난다.
* 이를 방지하기 위해 중복되는 케이스들을 지워나가야 한다. => 하지만 중복되는 케이스도 없다.
* 그런데 비트가 1 << 40이니까 메모리가 터지게 된다.
*/
/*
* 좌석 배치의 규칙을 이용한다.
* https://kimcodingvv.github.io/BOJ-2305/
* 
* - fibo 배열은 자유석이 없는 경우에 대하여 n길이의 좌석 배치를 이루는 경우이다.
*	이러한 풀이 방법은 LCS 문제의 증명과 유사하다. (CLRS p392)
* - dp 테이블은 한쪽 끝에 자유석이 있다고 가정한 경우의 수를 의미한다.
*	아래 경우들을 보면 한쪽 끝이 링크의 예제와 반대로 오른쪽에 있는 경우가 있는데(1의 경우)
*	이는 단순 역순이며, 각 자리들은 좌 또는 우까지 앉을 수 있기 때문에 상관이 없다.
* 
* - 그러므로 최종적인 값은 k를 기준으로 배열을 나누어 계산한다.
* 
* - (1) [1.. k][k+1 .. N]로 나눈 경우
*		[1..k-1] 범위의 사람들이 자유석에 앉는 경우이다.
*		왼쪽 배열: dp[k]
*		오른쪽 배열: 자유석이 없는 경우의 수이므로 fibo[n-k]에 해당한다.
*	(2) [1..k-1][k..N]로 나눈 경우
*		[k+1..N] 범위의 사람들이 자유석에 앉는 경우이다.
*		왼쪽 배열: 자유석이 없는 경우의 수이므로 fibo[k-1]에 해당한다.
*		오른쪽 배열: dp[n-k+1]이다.
*	(*) 위 두 경우에 대하여 자유석에 아무도 앉지 않는 경우가 중복된다.
*		=> fibo[k-1]*fibo[n-k]인 경우를 한번 빼준다.
*/

#include <iostream>

using namespace std;

int N, K, cnt{ 0 };

int noFree[41];		// 피보나치와 같다.
int noFreeSum[41];
int withFree[41];	// dp

int main()
{
	cin >> N >> K;
	
	noFree[0] = noFree[1] = noFreeSum[0] = 1;
	noFreeSum[1] = 2;

	for (int i = 2; i <= N; i++)
	{
		noFree[i] = noFree[i - 1] + noFree[i - 2];
		noFreeSum[i] = noFreeSum[i - 1] + noFree[i];
	}

	// base case
	withFree[0] = withFree[1] = 1;
	withFree[2] = 2;

	for (int i = 3; i <= N; i++)
	{
		withFree[i] = withFree[i - 1] + withFree[i - 2]
			+ noFreeSum[i - 1] - noFree[0];
	}
	
	cout << withFree[K] * noFree[N - K] + noFree[K - 1] * withFree[N - K + 1] - noFree[K - 1] * noFree[N - K];
	return 0;
}