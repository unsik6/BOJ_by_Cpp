/* 백준 1708번 볼록 껍질
*
* Input: 점의 개수 N (3 <= N <= 100,000)
*		 N개의 줄에 x좌표, y좌표 (|x|,|y| <= 40,000)
*

* Output: 볼록 껍질을 이루는 점의 개수를 출력
*
* Convex hull
* 대표적인 알고리즘: Graham's Scan
* 1) Preprocessing (nlogn)
*	(1) 기준점 pivot을 잡는다 - 보통 y값이 가장 작은 점
*	(2) x축에 대한 각도의 오름차순 정렬을 한다.	- pivot 기준으로 반시계 방향 정렬
* 2) Processing (n)
*	(1) first = pivot, second = 정렬의 첫번째로 한다.
*	(2) 정렬의 두번째를 next로 한다.
*	(3) first와 second를 스택에 넣는다.
*	(4-1) 한 개(second)를 팝한 다음, 팝한 것(second), top(first), next에 대하여 ccw를 수행한다.
		  반시계방향(>0)이면 second와 next를 스택에 넣는다.
*	(4-2) 만약 ccw가 시계방향(<0)이면 second를 스택에 넣지 않고, pop을 한번 더 한다.
*		  그리고 이번에 팝한 것, top(이전의 first 전의 것), next에 대하여 ccw를 수행한다.
* 
* - 전처리 과정에서 좌표들을 ccw를 기준으로 정렬했기 때문에, 4번 과정에서 ccw가 시계방향이라면
*	second가 껍질 안쪽에 있음을 의미한다.
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include <math.h>
using namespace std;

#define POSITION pair<long long, long long>

// input
int N;

// 정점들의 배열 - 가장 앞에 pivot 저장
POSITION positions[100000];

// Processing에서 사용 - positions 배열의 인덱스를 추적
stack<int> stk;

POSITION operator- (POSITION _p1, POSITION _p2)
{
	return { _p1.first - _p2.first, _p1.second - _p2.second };
}
long long ccw(POSITION _pivot, POSITION _p1, POSITION _p2)
{
	POSITION v1 = _p1 - _pivot;
	POSITION v2 = _p2 - _pivot;
	return v1.first * v2.second - v1.second * v2.first;
}

long long distance(POSITION _a, POSITION _b)
{
	return pow(_a.first - _b.first, 2) + pow(_a.second - _b.second, 2);
}

// Y좌표 기준 정렬
bool compareY(POSITION _a, POSITION _b)
{
	if (_a.second < _b.second) return true;
	else if (_a.second > _b.second) return false;
	else
	{
		return _a.first < _b.first;
	}
}

// ccw의 오름차순 정렬
// 이 과정에 대해서는 스칼라 곱을 이용한 cos값의 내림차순 또는,
// pivot과 해당 정점 간을 지나는 직선의 기울기를 사용할 수 있다.
bool compareCCW(POSITION _a, POSITION _b)
{
	long long ccwResult = ccw(positions[0], _a, _b);
	
	// 세 점이 일직선 위에 있으면 가까운 것을 먼저 출력 (이 예외처리 중요)
	if (ccwResult == 0)
		return distance(positions[0], _a) < distance(positions[0], _b);
	else  // 그렇지 않을 경우 더 반시계 방향이 아닌 쪽으로 앞으로 배치
	{
		return ccwResult > 0;
	}
}



int main()
{
	cin >> N;
	for (int n = 0; n < N; n++)
		cin >> positions[n].first >> positions[n].second;
	sort(positions, positions + N, compareY);	// p[0]에 pivot(Y좌표가 가장 낮은 점)이 존재
	sort(positions + 1, positions + N, compareCCW);	// p[0]는 미포함.

	/*for (int n = 0; n < N; n++)
		cout << positions[n].first << ' ' << positions[n].second << endl;*/

	stk.push(0);
	stk.push(1);
	int next = 2;	// positions 배열 추적할 인덱스

	// 모든 정점을 다 넣을 때까지
	while (next < N)
	{
		while (stk.size() > 1)
		{
			int second = stk.top();
			stk.pop();
			int first = stk.top();

			// 만약 ccw가 <0이라면 second를 유지한 채로 다음 단계로 진행한다.
			// 그렇지 않다면 second는 제외한 상태로 반복한다.
			if (ccw(positions[first], positions[second], positions[next]) > 0)
			{
				stk.push(second);
				break;
			}
		}

		// 다음 정점으로 진행한다.
		stk.push(next++);
	}
	
	cout << stk.size();


	return 0;
}