// 백준 9020번 골드바흐의 추측

// input: 4 <= n = 짝수 <= 10000

// condition: 2보다 큰 모든 짝수는 두 소수의 합으로 나타낼 수 있다는 것이다.
//			  이러한 수를 골드바흐 수라고 한다.
//			  또, 짝수를 두 소수의 합으로 나타내는 표현을 그 수의 골드바흐 파티션이라고 한다.
//			  예를 들면, 4 = 2 + 2, 6 = 3 + 3, 8 = 3 + 5, 10 = 5 + 5, 12 = 5 + 7,
//			  14 = 3 + 11, 14 = 7 + 7이다.
//			  10000보다 작거나 같은 모든 짝수 n에 대한 골드바흐 파티션은 존재한다.

// n은 10000이다. n까지의 소수를 검사할 예정이므로 int 범위를 넘지 않는다.
// 원래는 가장 작은 소수부터 구했으나 두 수의 차이가 가장 작은 파티션을 출력해야 하므로
// 큰 소수부터 구한다.

#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	int* arr = new int[T];
	for (int i = 0; i < T; i++) cin >> arr[i];

	for (int t = 0; t < T; t++)
	{
		// n이 4인 경우를 제외하면 파티션의 요소들을 반드시 홀수여야 한다.
		// 2 이상의 짝수는 소수일 수 없기 때문이다.
		// 그러므로 향후 반복문의 수를 줄이기 위해 4는 예외처리한다.
		// 파티션에 2가 필요한 짝수는 (2+2)인 4밖에 없다.
		// 2이상의 소수는 모두 홀수이므로 (2+홀수)는 홀수가 되기 때문이다.
		if (arr[t] == 4)
		{
			cout << 2 << ' ' << 2 << '\n';
			continue;
		}
		
		// 에라토스테네스의 채로 n까지의 소수 리스트를 구비해두고 구한다.
		int ertos_size = arr[t] + 1;
		bool* ertos = new bool[ertos_size] {false};
		for (int i = 2; i < ertos_size; i++) ertos[i] = true;
		for (int i = 2; i < ertos_size; i++)
		{
			if (ertos[i])
			{
				if (i * i > ertos_size) break;
				for (int f = i * i; f < ertos_size; f++)
					if (!(f % i)) ertos[f] = false;
			}
		}

		int a = 0, b = 0;	// 파티션
		// 2개의 소수로 분할되는 경우, 두 파티션은 n/2 이하 범위에 1개 이상 범위에 1개 존재한다.
		// n이 2 이상의 짝수는 소수일 수 없기 때문에 2씩 증가하여 반복울 줄인다.
		for (int i = 3; i <= (ertos_size - 1) / 2; i += 2)
		{
			if (ertos[i])
			{
				// b가 짝수일리 없다.
				// if (!(b % 2)) continue;
				if (ertos[arr[t] - i])
				{
					a = i;
					b = arr[t] - i;
				}
				// 별도의 크기 비교는 필요 없다.
				// 애초에 a가 더 클수록 두 값의 차이는 줄어든다.
			}
		}
		cout << a << ' ' << b << '\n';
	}
}