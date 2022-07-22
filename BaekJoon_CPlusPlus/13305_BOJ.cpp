// 백준 13305번 주유소

// input: 2 <= N = 도시의 개수 <= 100,000
//		  City[i]와 City[i+1]을 연결하는 N-1개의 도로의 길이 D[i]
//		  1 <= sum(D[i] | 0 <= i < N-1) <= 1,000,000,000
//		  1 <= City[i]의 리터당 가격 <= 1,000,000,000

// condition: 가장 돈을 적게 쓰면서 끝까지 가는 경우

// 중요한 것은 City[i]에서 주유를 할지 말지이다.
// City[i].pricePerL > City[i].pricePerL 이라면 다음 도시까지만 갈 만큼 주유하는 것이 싸다.
// else 위 조건이 나올 때까지는 City[i]에서 주유하는 것이 싸다.


#include <iostream>
using namespace std;

int main()
{
	long long N;
	cin >> N;

	// 마지막 도시의 리터당 가격은 필요없지만 입력을 받아야 하므로 N개의 unsigned long long를 준비한다.
	long long* prices = new long long[N];
	long long* distances = new long long[N - 1];

	for (int i = 0; i < N - 1; i++) cin >> distances[i];
	for (int i = 0; i < N; i++) cin >> prices[i];

	long long totalPrice = 0;
	long long curCity = 0;
	
	for (int i = 1; i < N; i++)
	{
		if (prices[i] < prices[curCity])
		{
			totalPrice += (prices[curCity] * distances[i - 1]);
			curCity = i;
		}
		else totalPrice += (prices[curCity] * distances[i - 1]);
	}

	cout << totalPrice;
}