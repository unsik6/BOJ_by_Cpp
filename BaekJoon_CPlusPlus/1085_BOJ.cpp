// 백준 1085번 직사각형에서 탈출

// input: 탈출해야 할 직사각형 (w, h) 1 <= w, h <= 1,000
//		  한수의 위치 (x, y) 1<= x <= w-1, 1<= y <= h-1
//		  w, h, x, y 는 정수

// 탈출하는 가장 빠른 방법은 그냥 수직 또는 수평으로 가장 가까운 경계면으로 가는 것이다.

#include<iostream>
int main()
{
	int x, y, w, h;
	std::cin >> x >> y >> w >> h;
	int min = x;
	if (w - x < min) min = w - x;
	if (y < min) min = y;
	if (h - y < min) min = h - y;
	if (min < 0) min *= -1;
	std::cout << min;
}