/* 백준 3047번 ABC
*
* Input: 1 <= x, y, z <= 100
*		  A, B, C로 이루어진 문자열
*

* Output: A < B < C라는 조건의 ABC를 x,y,z에 지정하고 입력된 문자열에 따라 숫자 출력
*/

#include <iostream>
#include <algorithm>
int main()
{
	int arr[3]; char str[4];
	for (int i = 0; i < 3; i++) std::cin >> arr[i];
	std::sort(arr, arr + 3);
	std::cin >> str;
	for (int i = 0; i < 3; i++)
	{
		if (str[i] == 'A') std::cout << arr[0];
		else if (str[i] == 'B') std::cout << arr[1];
		else std::cout << arr[2];
		std::cout << ' ';
	}
}