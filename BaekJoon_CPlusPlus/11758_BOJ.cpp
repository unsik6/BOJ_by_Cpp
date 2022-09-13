/* 백준 11758번 CCW
*
* Input: 점 P1~P3의 좌표를 줄로 구분하여 입력 받음.
*		 -10,000 <= x1,y1,x2,y2,x3,y3 <= 10,000

* Output: P1 - P2 - P3를 순서대로 이은 선분이 반시계 방향이면 1, 시계 방향이면 -1, 일직선이면 0을 출력
*
* 만약 P1을 기준으로 P2가 P3의 우측에 있으면 반시계 방향, 좌측에 있으면 시계 방향이다. (진행하는 순서에 따라 결정)
* 이는 [P1->P2] 벡터(v1)와 [P1->P3] 벡터(v2)의 외적으로 판단할 수 있다.
* 두 벡터의 외적의 결과의 방향에 따라 결정된다.
*/

#include<iostream>
#include<utility>
using namespace std;

#define position pair<int, int>

position operator- (const position _left, const position _right)
{
	return { _left.first - _right.first, _left.second - _right.second };
}

int ccw(position _p1, position _p2, position _p3)
{
	position v1 = _p2 - _p1;
	position v2 = _p3 - _p1;

	int cross = v1.first * v2.second - v1.second * v2.first;

	if (cross > 0) return 1;
	else if (cross < 0) return -1;
	else return 0;
}

int main()
{
	position positions[3];
	for (int i = 0; i < 3; i++)
		cin >> positions[i].first >> positions[i].second;
	cout << ccw(positions[0], positions[1], positions[2]);
}