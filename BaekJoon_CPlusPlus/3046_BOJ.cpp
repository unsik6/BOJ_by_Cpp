/* 백준 3046번 R2
*
* Input: -1,000 <= R1, S <= 1,000
*		

* Output: S는 R1과 R2의 평균 => R2 구하기
*/

#include <iostream>
int main()
{
	int r1, s;
	std::cin >> r1 >> s;
	std::cout << 2 * s - r1;
}