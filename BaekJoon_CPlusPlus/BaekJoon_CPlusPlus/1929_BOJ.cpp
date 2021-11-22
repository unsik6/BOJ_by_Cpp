// 백준 1929번 소수 구하기

// input: 1 <= M <= N <= 1,000,000 (M과 N은 양의 정수)

// condition: N부터 M까지의 소수들을 작은 순으로 출력한다.

// 에라토스테네스의 채로 풀어보자
// 에라토스테네스의 채의 규칙은 다음과 같다.
// 2 <= i <= sqrt(n) + 1
// 위 범위내의 모든 소수 i에 대하여
// i의 배수인 수들을 모두 지우면 소수만 남는다.

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int M, N;
	cin >> M >> N;
	vector<int> prime = { 2 };		// 소수를 저장할 동적 배열
	bool divided = false;

	for (int i = 1; i <= N; i++)
	{
		if (i == 1)continue; // 1은 별도로 예외처리
		if (i == 2)	// 2는 별도로 예외처리
		{
			if(M <= 2) cout << i << '\n';
			continue;
		}
		for (int& it : prime)
		{
			if (!(i % it))
			{
				divided = true;
				break;
			}
		}
		if (!divided)
		{
			prime.push_back(i);	// 소수로 안 나눠지면 소수에 추가
			if(i >= M)	cout << i << '\n';
		}
		divided = false;	// 판단 변수 초기화
	}
}