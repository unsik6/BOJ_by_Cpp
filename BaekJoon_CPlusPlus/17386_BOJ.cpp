/* 백준 17386번 선분 교차1
*
* Input: 선분 L1과 L2의 양 끝점의 좌표를 줄로 구분하여 입력 받음.
*		 -1,000,000 <= x1, y1, x2, y2, x3, y3, x4, y4 <= 1,000,000
*		 좌표의 값들은 모두 정수

* Output: L1과 L2가 교차하면 1, 아니면 0
*		  단, 선분의 길이는 반드시 0보다 크다.
*		  단, 세 점이 일직선 상에 있는 일은 없다.
*
* CCW 응용이다.
* Pi = (xi, yi)라고 했을 때,
* P1과 P3, P4의 CCW의 결과, P2와 P3, P4의 CCW의 결과가 다를 경우에는 P1과 P2가 L2를 기준으로 서로 다른 쪽에 존재한다는 것을 의미한다.
* 또한, 위 과정을 P3과 P4 기준으로도 해줘야 한다.
*/

#include<iostream>
#include<utility>
using namespace std;

// (10^6)^2가 int 범위 초과하여 수정
#define position pair<long long, long long>

position operator- (const position _left, const position _right)
{
	return { _left.first - _right.first, _left.second - _right.second };
}

int ccw(position _p1, position _p2, position _p3)
{
	position v1 = _p2 - _p1;
	position v2 = _p3 - _p1;

	long long cross = v1.first * v2.second - v1.second * v2.first;

	if (cross > 0) return 1;
	else if (cross < 0) return -1;
	else return 0;
}

// 매개변수로 ccw 결과를 입력, 이때 두 결과의 곱이 -1이라면 서로 방향이 다르다.
bool isCross(int _a, int _b)
{
	return _a * _b == -1;
}

int main()
{
	position positions[4];
	for (int i = 0; i < 4; i++)
		cin >> positions[i].first >> positions[i].second;
	cout << (isCross(ccw(positions[0], positions[2], positions[3]), ccw(positions[1], positions[2], positions[3])) &&
		isCross(ccw(positions[2], positions[0], positions[1]), ccw(positions[3], positions[0], positions[1])));
}