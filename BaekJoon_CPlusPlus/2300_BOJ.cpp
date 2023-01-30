/* 백준 2300 기지국
*
*Input: 건물의 개수 N ( 1 <= N <= 10,000)
*		각 줄마다 건물의 좌표 x, y (|x|,|y| <= 1,000,000)

		모든 건물의 y좌표는 0이 될 수 없다.
		기지국은 x축 위에 건설되며, y좌표는 0으로 고정이다.
		기지국을 중심으로 정사각형 범위가 통신범위이다.
		기지국의 최소 개수가 아닌 통신범위의 한 변의 총합이 최소가 되는 것을 구해야 한다.

* Output: 통신범위의 한 변의 총합의 최소값
*/

// DP 문제로
// pos_a는 a번째 건물이라고 했을 때
// T(pos_a,pos_b)는 a번째 건물부터 b번째 건물까지에 대한 최적해라고 하자.
// T(pos_1,pos_N)=min(T(pos_1, pos_k)+T(pos_{k+1},pos_N))
// 이는 곧 모든 경우의 수를 탐색하는 것과 같다.

#include<iostream>
#include<algorithm>
using namespace std;

#define INF 9e9	// 사실 아무리 커봐야 2백만 언저리이다.

// input
int N;
pair<int, int> buildings[10001];

// DP
int dp[10001]{ 0 };	// dp[0]은 base case로 건물 0개이므로 0이다.

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> buildings[i].first >> buildings[i].second;
	
	// 정렬할 때는 맨 앞에 빈칸이 말려들어가지 않게 조심
	sort(buildings + 1, buildings + N + 1);

	// DP
	// 앞에서부터 순회한다.
	for (int i = 1; i <= N; i++)
	{
		// 일단 최소값을 찾아야하니까 디폴트는 INF이다.
		dp[i] = INF;
		int maxHeight = 0;
		for (int j = i; j >= 1; j--)
		{
			// j~i번째 건물들을 묶는다고 하자.
			
			// 일단 건물 높이 최신화
			maxHeight = max(maxHeight, abs(buildings[j].second));

			// 기존에 저장한 값(여태까지 비교한 케이스 중 최적)과
			// 현재의 경우인 T(1, j-1)+T(j, i)를 비교한다.
			dp[i] = min(dp[i], dp[j - 1] + max(2 * maxHeight, buildings[i].first - buildings[j].first));
		}
	}
	
	// 출력
	cout << dp[N];

	return 0;
}
