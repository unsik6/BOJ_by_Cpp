/* 백준 7453 합이 0인 네 정수
*
*Input: n (1<= n <= 4000)
*		n개의 줄에 배열 A, B, C, D의 요소인 정수 x가 공백으로 구분되어 주어진다. (|x| <= 2^28)

* Output : A[a], B[b], C[c], D[d]의 합이 0이 되는 (a, b, c, d) 쌍의 개수
*/

#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[4][4000];
int sums[2][4000 * 4000];
long long cnt = 0;

void makeSum()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sums[0][i * n + j] = arr[0][i] + arr[1][j];
			sums[1][i * n + j] = arr[2][i] + arr[3][j];
		}
	}

	sort(sums[0], sums[0] + (n * n));
	sort(sums[1], sums[1] + (n * n));
}

void counting()
{
	for (int i = 0; i < n * n; i++)
	{
		cnt += upper_bound(sums[1], sums[1] + n * n, sums[0][i] * -1) - sums[1]
			- (lower_bound(sums[1], sums[1] + n * n, sums[0][i] * -1) - sums[1]);
	}
}

int main()
{
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		for (int arrIdx = 0; arrIdx < 4; arrIdx++)
			cin >> arr[arrIdx][i];
	}
	
	makeSum();
	counting();

	cout << cnt;
}