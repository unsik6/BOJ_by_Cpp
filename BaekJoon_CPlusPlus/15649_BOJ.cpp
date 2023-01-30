/* 백준 15649 N과 M(1)
*
*Input: 자연수 범위 N, 고를 자연수 개수 M (1 <= M <= N <= 8)

* Output: 1~N의 수들을 중복 없이 M개 고르는 모든 수열 출력
*/
// 시간제한이 1초이지만 N과 M이 작아서 백트래킹으로 푸는 문제
// 경우의 수는 최대 8!=40320이며 각 단계마다 사용하지 않은 숫자를 확인해야 하므로 8*8!이 된다.

#include <iostream>
using namespace std;

int N, M;
bool inputs[9]{ false };
int outputs[9];

void solution(int _seq)
{
	// M개 전부다 확인했으면 출력
	if (_seq > M)
	{
		for (int i = 1; i <= M; i++)
			cout << outputs[i] << ' ';
		cout << '\n';
		return;
	}

	// 사용 안한 것 중에 가장 작은 거부터 진행
	for (int i = 1; i <= N; i++)
	{
		// false면 사용
		if (!inputs[i])
		{
			inputs[i] = true;	// 사용한다 지정
			outputs[_seq] = i;	// 수열의 _seq번째 숫자에 넣기
			solution(_seq + 1);	// 다음 순번 번호로
			
			// 이번 단계까지 다 사용했으면, 다음 경우를 위해 사용해제
			inputs[i] = false;
		}
	}
}

int main()
{
	cin >> N >> M;
	solution(1);
	return 0;
}