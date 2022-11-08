/* 백준 1933 스카이라인
*
* Input: 건물의 수 N (1 <= N <= 100,000)
*		 건물의 왼쪽 X좌표 L, 높이 H, 오른쪽 X 좌표 R (1 <= L < R <= 1,000,000,000, 1 <= H <= 1,000,000,000)

* Output: 높이가 변하는 지점에 대해서 그 지점의 X 좌표와 그 지점에서의 높이
*/

#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;


// input
int N;
int building_L, building_R, building_H;

// 건물
map<int, int> field;	// key: x좌표; value: union_find set의 root
pair<int, pair<int, int>> buildings[100000];	// {par, {H, R}}

void insertBuilding(int _idx, int _l, int _h, int _r)
{
	if (field.find(_l) == field.end())
	{
		field[_l] = _idx;
		buildings[_idx] = { _idx, {_h, _r} };
	}
	else
	{
		buildings[_idx] = { field[_l], {_h, _r} };
		field[_l] = _idx;
	}
}

// solution용
struct comp
{
	bool operator()(int _a, int _b)
	{
		return buildings[_a].second.first < buildings[_b].second.first;
	}
};
priority_queue<int, vector<int>, comp> pq;


int main()
{
	// 입력 받기
	cin >> N;

	for (int n = 0; n < N; n++)
	{
		cin >> building_L >> building_H >> building_R;
		insertBuilding(n, building_L, building_H, building_R);
	}


	for (map<int, int>::iterator iter = field.begin(); iter != field.end(); iter++)
	{
		// down
		bool down = false;
		int preRight = (pq.empty() ? -1 : buildings[pq.top()].second.second);
		int preH = (pq.empty() ? 0 : buildings[pq.top()].second.first);
		while (!pq.empty())
		{
			if (buildings[pq.top()].second.second >= iter->first)
				break;
			
			pq.pop();
			
			// 큐가 비어있다면 바닥으로 내려 앉은 것
			if (pq.empty())
				cout << preRight << ' ' << 0 << ' ';
			else if (buildings[pq.top()].second.second > preRight)	// 현재 탑이 {이전 최대 높이 건물}의 오른쪽 끝보다 오른쪽에서 끝나면 계단식
			{
				if (buildings[pq.top()].second.first < preH)		// 계단식이 아니라 건물 높이가 유지될 수도 있음에 대한 예외처리
				{
					cout << preRight << ' ' << buildings[pq.top()].second.first << ' ';
					if (!down) down = true;
				}
				preRight = buildings[pq.top()].second.second;
				preH = buildings[pq.top()].second.first;
			}
		}

		bool up = false;
		int preTopH = (pq.empty() ? 0 : buildings[pq.top()].second.first);
		int idx = iter->second;
		while (true)
		{
			pq.push(idx);
			if (buildings[idx].second.first > preTopH)
				up = true;

			if (idx == buildings[idx].first)
				break;
			else
				idx = buildings[idx].first;
		}

		if (up)
		{
			cout << iter->first << ' ' << buildings[pq.top()].second.first << ' ';
		}
	}

	// 마지막 내려앉기를 위한 down
	// down
	int preRight = (pq.empty() ? -1 : buildings[pq.top()].second.second);
	int preH = (pq.empty() ? 0 : buildings[pq.top()].second.first);
	while (!pq.empty())
	{
		pq.pop();

		if (pq.empty())
			cout << preRight << ' ' << 0 << ' ';
		else if (buildings[pq.top()].second.second > preRight)
		{
			if(buildings[pq.top()].second.first < preH)
				cout << preRight << ' ' << buildings[pq.top()].second.first << ' ';
			preRight = buildings[pq.top()].second.second;
			preH = buildings[pq.top()].second.first;
		}
	}

	return 0;
}