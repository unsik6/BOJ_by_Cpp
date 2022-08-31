/* 백준 3036번 링
*
* Input: 링의 개수 N (3 <= M <= 100)
*		 연결된 순으로 링의 반지름 r_i (1 <= r_i <= 1,000)

* Output: 연결된 순서대로 (i번째 링의 바퀴 수)/(첫번째 링의 바퀴 수)를 기약분수 형태로 출력
*
* 회전하는 바퀴수는 원의 둘레에 비례하기 때문에 큰 문제가 되지 않는다.
* 그러나 기약분수의 형태로 출력해야 하므로 이 문제는 최대공약수를 구하는 문제라고 할 수 있다.
* 링의 개수가 최대 100이고 반지름의 크기가 최대 1,000이므로
* 무식한 방법으로 최대 공약수를 찾아도 primitive operation의 수가 100,000이다.
* 그러므로 시간제한을 넘지 않는다.
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int firstR;
	cin >> firstR;
	for (int i = 1; i < n; i++)
	{
		int iR;
		cin >> iR;
		int minR = min(firstR, iR);
		int gcf = 1;
		// 자신을 제외한 최대 공약수는 k/2를 넘을 수 없다.
		for (int i = 1; i <= minR / 2; i++)
		{
			if (firstR % i == 0 && iR % i == 0)
				gcf = i;
		}
		// 더 작은 반지름이 최대공약수인 경우
		if (iR % firstR == 0)
			gcf = firstR;
		if (firstR % iR == 0)
			gcf = iR;

		cout << firstR / gcf << '/' << iR / gcf << '\n';
	}
}