/* 백준 8986번 전봇대
*
* Input: 전봇대의 수 N (1 <= N <= 100,000)
*		 전봇대의 위치가 오름차순으로 주어진다. (xi | i=0이면 x_i=0, 그외는 1 <= x_i <= 1,000,000,000)

* Output: 모든 이웃한 전봇대들의 거리가 같도록 전봇대들의 이동거리 합의 최솟값을 출력
*
* 삼분탐색을 활용하되 최적값을 찾으려고 하면 무한루프가 발생한다.
*/

#include <iostream>
using namespace std;

// input
int N;
long long poles[100000];

long long function(long long _distance)
{
	long long ret = 0;
	for (int n = 1; n < N; n++)
	{
		ret += abs(poles[n] - _distance * n);
	}
	return ret;
}

int main()
{
	cin >> N;
	for (int n = 0; n < N; n++)
		cin >> poles[n];

	long long low = 0, high = 1e9;
	while (high - low + 1 > 3)
	{
		long long p1 = (low * 2 + high) / 3;
		long long p2 = (low + high * 2) / 3;

		long long funcP1 = function(p1);
		long long funcP2 = function(p2);

		if (funcP1 < funcP2)
			high = p2;
		else
			low = p1;
	}

	long long minimum = 1e18;
	for (int i = low; i <= high; i++)
	{
		minimum = min(minimum, function(i));
	}

	cout << minimum;
}