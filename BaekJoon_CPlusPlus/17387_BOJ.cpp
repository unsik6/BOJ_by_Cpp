/* 백준 17387번 선분 교차2
*
* Input: 선분 L1과 L2의 양 끝점의 좌표를 줄로 구분하여 입력 받음.
*		 -1,000,000 <= x1, y1, x2, y2, x3, y3, x4, y4 <= 1,000,000
*		 좌표의 값들은 모두 정수

* Output: L1과 L2가 교차하면 1, 아니면 0
*		  단, 선분의 길이는 반드시 0보다 크다.
*		  단, 한 선분의 끝점이 선분 위에 있거나 서로 다른 선분의 끝점이 같은 위치에 있다면 교차이다.
*
* CCW 응용이다.
* Pi = (xi, yi)라고 했을 때,
* P1과 P3, P4의 CCW의 결과, P2와 P3, P4의 CCW의 결과가 다를 경우에는 P1과 P2가 L2를 기준으로 서로 다른 쪽에 존재한다는 것을 의미한다.
* 또한, 위 과정을 P3과 P4 기준으로도 해줘야 한다.
* 
* 
*/
#include <iostream>
#include <utility>

using namespace std;

#define position pair<long long, long long>

position operator- (const position _left, const position _right)
{
	return { _left.first - _right.first, _left.second - _right.second };
}

// 선분의 끝점이 같아도 교차이므로 = 관계도 포함한다.
bool operator<= (position _p1, position _p2)
{
	if (_p1.first == _p2.first)
		return _p1.second <= _p2.second;
	else return _p1.first <= _p2.first;
}

// positions
position pos[4];

 // CCW
int ccw(position _p1, position _p2, position _p3)
{
	position vec1 = _p2 - _p1;
	position vec2 = _p3 - _p1;

	long long cross = vec1.first * vec2.second - vec2.first * vec1.second;

	if (cross > 0) return 1;
	else if (cross < 0) return -1;
	else return 0;
}

int main()
{
	for (int i = 0; i < 4; i++)
		cin >> pos[i].first >> pos[i].second;

	// L1 to positions of L2
	int l1Tol2 = ccw(pos[0], pos[1], pos[2]) * ccw(pos[0], pos[1], pos[3]);
	// reverse
	int l2Tol1 = ccw(pos[2], pos[3], pos[0]) * ccw(pos[2], pos[3], pos[1]);

	if (l1Tol2 <= 0 && l2Tol1 <= 0)
	{
		if (l1Tol2 == 0 && l2Tol1 == 0)
		{
			// sort the positions
			if (pos[1] <= pos[0])
				swap(pos[1], pos[0]);
			if (pos[3] <= pos[2])
				swap(pos[3], pos[2]);

			if (pos[0] <= pos[3] && pos[2] <= pos[1])
				cout << 1;	// a position of a line is on the another line.
			else cout << 0;	// two line do not intersect.
		}
		else cout << 1;
	}
	else cout << 0;	// not intersection
	
		

	return 0;
}