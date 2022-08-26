/* 백준 3052번 나머지
*
* Input: 10개의 수 (1 <= i <= 1,000)

* Output: 10개의 수를 42로 나눈 나머지들을 구성하는 중복되지 않는 수의 개수
*/

#include <iostream>
int main()
{
	bool arr[42]{false}; int cnt = 0;
	for (int i = 0; i < 10; i++)
	{
		int x;
		std::cin >> x;
		if (arr[x % 42]) continue;
		arr[x % 42] = true;
		cnt++;
	}
	std::cout << cnt;
}