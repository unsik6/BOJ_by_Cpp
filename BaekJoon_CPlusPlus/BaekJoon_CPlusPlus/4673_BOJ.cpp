// 백준 4673번 셀프넘버

// condition: d(n) = n + (n의 각 자리 수)
//			  n을 d(n)의 생성자라고 할 때, 생성자가 없는 수를 셀프 넘버라고 한다.
//			  10000보다 작은 양의 정수 중 셀프 넘버들을 나열하여 출력하는 함수를 작성하시오.

#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

int d(int _n)
{
	int result = _n;
	while (true)
	{
		result += _n % 10;
		_n = int(_n / 10);
		if (_n == 0) break;
	}
	return result;
}

int main()
{
	bool arr[10001]{ true };
	for (int i = 1; i < 10000; i++)
	{
		int index = d(i);
		if (index <= 10000) arr[index] = true;
	}

	for (int i = 1; i < 10000; i++)
		if (!arr[i]) cout << i << endl;
	return 0;
}