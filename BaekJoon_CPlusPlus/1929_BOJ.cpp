// 백준 1929번 소수 구하기

// input: 1 <= M <= N <= 1,000,000 (M과 N은 양의 정수)

// condition: N부터 M까지의 소수들을 작은 순으로 출력한다.

// 에라토스테네스의 채로 풀어보자
// 에라토스테네스의 채의 규칙은 다음과 같다.
// 2 <= i <= sqrt(n) + 1
// 위 범위내의 모든 소수 i에 대하여
// i의 배수인 수들을 모두 지우면 소수만 남는다.

// 두번째 풀이
// 일반적인 예제입니다.
// 첫번째 풀이에서는 출력까지 한번에 하고자
// 주어진 수의 범위에 집중하여 for문을 돌렸으나 시간초과가 발생합니다.
// 소수 여부를 기준으로 하면 소수의 i*i 이후로 숫자를 제거하면 되므로
// 반복 횟수를 줄일 수 있습니다.

#include <iostream>
using namespace std;

int main()
{
	int M, N;
	cin >> M >> N;
	int end = N + 1;
	bool* arr = new bool[end]{ false };	// 중요한 것은 소수인가 아닌가이므로 bool
	for (int i = 0; i < end; i++)
	{
		arr[i] = true;
		if (i == 0 || i == 1) arr[i] = false;
	}
	// 아래의 for문의 인덱스는 일부러 long long을 사용합니다.
	// i * i 계산에서 int 범위를 초월할 수 있기 때문입니다.
	for (long long i = 2; i < end; i++)
	{
		if (arr[i] == true)
		{
			// 어차피 i*i 이상부터 돌리므로 범위를 넘으면 필요 없습니다.
			if (i * i > N) break;

			// i*i 이전까지는 이미 i보다 작은 소수로 인해 제거됨.
			// f를 굳이 1개씩 증가시킬 필요는 없습니다. 어차피 i의 배수를 없애는 것이므로
			// i만큼 증가시키면 됩니다.
			for (long long f = i * i; f <= N; f += i)	
				if (!(f % i)) arr[f] = false;	// 확인차원의 if문
		}
	}

	for (int i = M; i < end; i++) if(arr[i]) cout << i << '\n';
}

// 첫번째 풀이: 시간초과
// 반복문의 기준을 주어지는 숫자들로 할 경우,
// 반복문의 횟수를 줄일 수 있는 부분이 없다.
// 만약 소수를 기준으로 반복문을 진행한다면
// 반복문의 시작점을 더 크게 잡을 수 있으므로 시간을 줄일 수 있다.
/*
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
*/