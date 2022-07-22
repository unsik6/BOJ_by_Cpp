// 백준 3009번 네 번째 점

// input: 직교좌표계의 세 개의 점, 각 좌표 수치는 1 <= (x, y) <= 1000

// 원래라면 방정식을 통해 4번째 점을 도출하겠지만 축에 평행한 직사각형을 출력하므로 필요 없다.
// 각 좌표에 대해 쌍을 이루지 못하는 x와 y를 찾으면 된다.

#include<iostream>

int main()
{
	int x1, y1, x2, y2, x3, y3, x4{ 0 }, y4{ 0 };
	std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	if (x1 == x2) x4 = x3;
	else if (x1 == x3) x4 = x2;
	else x4 = x1;
	if (y1 == y2) y4 = y3;
	else if (y1 == y3) y4 = y2;
	else y4 = y1;
	std::cout << x4 << ' ' << y4;
}