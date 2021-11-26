// 백준 11729번 하노이 탑 이동순서

// input: 1 <= N <= 20 : 탑 높이

// 하노이 탑을 1번칸에서 3번칸으로 옮긴다고 생각해보자
// 1) 먼저 1번 칸에서 3번 칸으로 N-2만큼 옮긴다.
// 그 다음, 1개를 2번칸으로 옮긴다.
// 그 다음, 3번 칸으로 옮겨두었던 원판들(N-2)을 모두 2번칸으로 옮긴다.
// 그 다음, 1번칸의 마지막 층이었던 크기 N인 원판을 3번칸으로 옮긴다.

// 이걸 반복하게 된다.
// 즉, 위 단계를 모두 완료하면 (N, start, bypass, to)의 관계에서
// (N, bypass, start, to) 관계를 진행하게 된다.
// 자 그러면 맨 처음 단계는 뭘까? N-1개 만큼의 탑을 bypass로 옮기는 작업이다.
// (N, start, to, bypass)로 변하게 된다!
// 만약 N이 1이라면 당연히 바로 start에서 to로 옮겨주면 된다.

// 다만, 이번 문제에서는 이동 과정도 표시해야 하므로
// 매개변수로 현재 하노이탑이 1번칸에 있는지 2번칸에 있는지 확인한다.

// 문제 특성상 횟수를 먼저 출력해야 한다.
// 만든 하노이 탑으로 테스트를 해보면
// 1, 3, 8, 16, 31 ... 의 규칙이 나타난다.
// 2^N - 1의 규칙이 나타난다.


#include <iostream>
using namespace std;

void Hanoi(int N, int start, int bypass, int to)
{
	if (N == 1)
		cout << start << ' ' << to << '\n';
	else
	{
		Hanoi(N - 1, start, to, bypass);
		cout << start << ' ' << to << '\n';	// 3으로 먼저 옮긴다.
		Hanoi(N - 1, bypass, start, to);
	}
}

int main()
{
	int N, cnt{ 1 };
	cin >> N;
	for (int i = 1; i <= N; i++) cnt *= 2;
	cout << --cnt << '\n';
	Hanoi(N, 1, 2, 3);
}
