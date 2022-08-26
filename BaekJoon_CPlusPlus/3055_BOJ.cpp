/* 백준 3055번 탈출
*
* Input: R, C (1 <= R, C <= 50)
*		 R개의 줄에 지도 (단, S, D는 한 개씩)

* Output: (1) S에서 출발하여 D에 도착하는 가장 빠른 시간 출력 (못 갈경우 KAKTUS 출력)
*		  (2) 이동에는 1의 시간이 소요된다.
*		  (3) 고슴도치는 변이 인접한 칸으로 이동할 수 있다.
*		  (4) 물은 변이 인접한 모든 칸으로 범람한다.
*		  (5) 물이 범람할 예정이거나 물인 칸으로 고슴도치는 이동할 수 없다.
*		  (6) 물은 비버의 소굴로 이동할 수 없다.
*		  (7) 물과 고슴도치는 돌을 통과할 수 없다.
* 
* (1) 최단 경로
* (2) 물 먼저 처리해줘야 Output.(5)를 처리할 수 있다.
*/

#include <iostream>
#include <queue>
#include <utility>
using namespace std;

char map[50][50];		// 지도
int waterMap[50][50];	// 각 위치 마다 물이 차오르는 최소 시간 저장
int hogMap[50][50];		// 고슴도치 최단 경로

struct compWater
{
	bool operator()(pair<int, int> _a, pair<int, int> _b)
	{
		return (waterMap[_a.first, _a.second] < waterMap[_b.first, _b.second]);
	}
};
struct compHog
{
	bool operator()(pair<int, int> _a, pair<int, int> _b)
	{
		return (hogMap[_a.first, _a.second] < hogMap[_b.first, _b.second]);
	}
};

int main()
{
	int R, C;
	cin >> R >> C;

	priority_queue < pair<int, int>, vector<pair<int, int>>, compWater> waters;
	priority_queue < pair<int, int>, vector<pair<int, int>>, compHog> hogs;
	pair<int, int> S, D;

	for (int r = 0; r < R; r++)
	{
		string str;
		cin >> str;
		for (int c = 0; c < C; c++)
		{
			map[r][c] = str[c];
			waterMap[r][c] = 100000;
			hogMap[r][c] = 100000;
			if (str[c] == '*')
			{
				waters.push(make_pair(r, c));
				waterMap[r][c] = 0;
			}
			else if (str[c] == 'S') S = make_pair(r, c);
			else if (str[c] == 'D') D = make_pair(r, c);
		}
	}

	// 먼저 물 전용 최소 범람 시간 계산
	while (!waters.empty())
	{
		pair<int, int> cur = waters.top();
		waters.pop();

		// 상
		if (cur.first - 1 >= 0)
		{
			if (waterMap[cur.first - 1][cur.second] > waterMap[cur.first][cur.second] + 1
				&& map[cur.first - 1][cur.second] != 'X' && map[cur.first - 1][cur.second] != 'D')
			{
				waterMap[cur.first - 1][cur.second] = waterMap[cur.first][cur.second] + 1;
				waters.push(make_pair(cur.first - 1, cur.second));
			}
		}
		// 하
		if (cur.first + 1 < R)
		{
			if (waterMap[cur.first + 1][cur.second] > waterMap[cur.first][cur.second] + 1
				&& map[cur.first + 1][cur.second] != 'X' && map[cur.first + 1][cur.second] != 'D')
			{
				waterMap[cur.first + 1][cur.second] = waterMap[cur.first][cur.second] + 1;
				waters.push(make_pair(cur.first + 1, cur.second));
			}
		}
		// 좌
		if (cur.second - 1 >=  0)
		{
			if (waterMap[cur.first][cur.second - 1] > waterMap[cur.first][cur.second] + 1
				&& map[cur.first][cur.second - 1] != 'X' && map[cur.first][cur.second - 1] != 'D')
			{
				waterMap[cur.first][cur.second - 1] = waterMap[cur.first][cur.second] + 1;
				waters.push(make_pair(cur.first, cur.second - 1 ));
			}
		}
		// 우
		if (cur.second + 1 < C)
		{
			if (waterMap[cur.first][cur.second + 1] > waterMap[cur.first][cur.second] + 1
				&& map[cur.first][cur.second + 1] != 'X' && map[cur.first][cur.second + 1] != 'D')
			{
				waterMap[cur.first][cur.second + 1] = waterMap[cur.first][cur.second] + 1;
				waters.push(make_pair(cur.first, cur.second + 1));
			}
		}
	}

	// 고슴도치 최단 경로 구하기
	hogMap[S.first][S.second] = 0;
	hogs.push(S);
	while (!hogs.empty())
	{
		pair<int, int> cur = hogs.top();
		hogs.pop();

		// 상
		if (cur.first - 1 >= 0)
		{
			if (hogMap[cur.first - 1][cur.second] > hogMap[cur.first][cur.second] + 1
				&& map[cur.first - 1][cur.second] != 'X'
				&& waterMap[cur.first - 1][cur.second] > hogMap[cur.first][cur.second] + 1)
			{
				hogMap[cur.first - 1][cur.second] = hogMap[cur.first][cur.second] + 1;
				hogs.push(make_pair(cur.first - 1, cur.second));
			}
		}
		// 하
		if (cur.first + 1 < R)
		{
			if (hogMap[cur.first + 1][cur.second] > hogMap[cur.first][cur.second] + 1
				&& map[cur.first + 1][cur.second] != 'X'
				&& waterMap[cur.first + 1][cur.second] > hogMap[cur.first][cur.second] + 1)
			{
				hogMap[cur.first + 1][cur.second] = hogMap[cur.first][cur.second] + 1;
				hogs.push(make_pair(cur.first + 1, cur.second));
			}
		}
		// 좌
		if (cur.second - 1 >= 0)
		{
			if (hogMap[cur.first][cur.second - 1] > hogMap[cur.first][cur.second] + 1
				&& map[cur.first][cur.second - 1] != 'X'
				&& waterMap[cur.first][cur.second - 1] > hogMap[cur.first][cur.second] + 1)
			{
				hogMap[cur.first][cur.second - 1] = hogMap[cur.first][cur.second] + 1;
				hogs.push(make_pair(cur.first, cur.second - 1));
			}
		}
		// 우
		if (cur.second + 1 < C)
		{
			if (hogMap[cur.first][cur.second + 1] > hogMap[cur.first][cur.second] + 1
				&& map[cur.first][cur.second + 1] != 'X'
				&& waterMap[cur.first][cur.second + 1] > hogMap[cur.first][cur.second] + 1)
			{
				hogMap[cur.first][cur.second + 1] = hogMap[cur.first][cur.second] + 1;
				hogs.push(make_pair(cur.first, cur.second + 1));
			}
		}
	}
	

	if (hogMap[D.first][D.second] < 100000)
		cout << hogMap[D.first][D.second];
	else cout << "KAKTUS";
}