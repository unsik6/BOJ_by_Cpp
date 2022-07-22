// 백준 11047번 동전0

// input: 1 <= N = 동전 종류의 수 <= 10
//		  1 <= K = 가치의 합 <= 100,000,000
//		  각 동전 Ai의 가치 (Ai = 1, i >= 2인 경우에 Ai = A(i-1)의 배수)

// condition: 최소한의 동전으로 K를 만드는 경우를 원한다.

// K >= Ai인 가치가 가장 큰 동전을 계속 선택한다.

// 그리디 선택 특성
// Ai는 항상 A(i-1)의 배수이므로, A(i-1)의 최대 개수는 Ai/A(i-1)보다 작다.
// 만약 (K >= Ai고 가치가 가장 큰 동전)을 Am이라고 한다면, 최적해에 Am이 포함되지 않으면,
// 그 것보다 작은 동전들로 채웠을 때, Ai/Ak (k < i)만큼의 개수가 추가되므로
// 매번 Am을 선택했을 때 가장 최적인 해를 구할 수 있다.

// 최적 부분 구조
// K에 대해 Am을 최대한 넣고 남은 값을 K'라고 할 때 Am인 동전을 최대한 많이 넣으므로 K'은 반드시 Am보다 작다.
// K' < Am이므로 Am은 더이상 사용할 수 없으며 Am > Ak (k < m)을 통해서 K'에 대한 최적해를 구한다.
// 이 때, K'에 대한 문제 즉 subProblem은 K일 때와 마찬가지의 방식으로 구할 수 있으며 각각에 대한 최적해를 갖는다.
// 최적부분해 + Am의 개수가 최적해이므로 최적 부분 구조가 성립힌다.

#include <iostream>
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	int* coins = new int[N];
	for (int i = 0; i < N; i++)
		cin >> coins[i];
	
	int curSum = 0;
	int cnt = 0;
	for (int i = N - 1; i >= 0; i--)
	{
		if (K >= coins[i] + curSum)
		{
			curSum += coins[i];
			cnt++;
			i++;
		}
	}

	cout << cnt;
}