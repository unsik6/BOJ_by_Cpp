/* 백준 11569번 신호등
*
* Input: 테스트 케이스 개수 T (1 <= T <= 10)
*		 교차로(정점)의 수 N (1 <= N <= 100,000)
*		 도로의(간선)의 수 M (1 <= M <= 100,000)
*		 출발 교차로의 번호 S (1 <= S <= N)
*		 도착 교차로의 번호 D (1 <= D <= N)
* 
*		 M개의 줄 src: a, dst: b, wht: c (1<= a, b <= N, a != b, 1 <= c <= 100,000)
*		 각 교차로의 신호등 주기 P_i (1 <= i <= N, 1 <= P_i <= 100)
*		 두 교차로 사이에는 최대 한개의 도로만 존재한다.
*
* Output: 첫째 줄: 최소 시간 출력 (64 bit 변수로 할 것) - 경로가 없는 경우 -1
* 
* 
*		 1) 자동차는 1초에 1의 길이만큼 이동한다
*		 2) 모든 신호등은 자동차의 출발과 동시에 동작한다.
*		 3) 출발 교차로와 ㄱ도착 교차로에서는 신호를 기다릴 필요가 없다.
*		 4) 어떤 교차로에서 같은 교차로로 돌아오는 길(self-loop)는 없다.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// input
int T, N, M, src, dst;
long long ret;
long long distances[100001];
long long periods[100001];
vector<pair<int, int>> adjacencyLists[100001]; // pair.frst = dst, second = weight


struct vertexInfo
{
	int id;
	long long d;
	int par;

	// std::priority_queue를 사용하기 위해 반대로 반환하게 한다.
	bool operator < (const vertexInfo& _a)
	{
		return (this->d > _a.d);
	}
};

struct compVI
{
	bool operator ()(vertexInfo a, vertexInfo b)
	{
		return a.d > b.d;
	}
};

bool pairComp(pair<int, int> a, pair<int, int> b)
{
	if (a.first < b.first) return true;
	else return false;
}

int main()
{
	
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		// input
		cin >> N >> M >> src >> dst;
		for (int m = 0; m < M; m++)
		{
			int s;
			pair<int, int> dw;
			cin >> s >> dw.first >> dw.second;
			adjacencyLists[s].push_back(dw);
			adjacencyLists[dw.first].push_back(pair<int, int>{s, dw.second});
		}
		for (int i = 1; i <= N; i++)
		{
			cin >> periods[i];
		}
			

		for (int i = 1; i <= N; i++)
		{
			sort(adjacencyLists[i].begin(), adjacencyLists[i].end(), pairComp);
			distances[i] = -1;
		}

		// initialize return value
		ret = -1;

		priority_queue<vertexInfo, vector<vertexInfo>, compVI> fringes;	// frist is vertex id, second is distance.
		vertexInfo tmp{ src, 0, -1 };
		fringes.push(tmp);
		while (!fringes.empty())
		{
			vertexInfo newTree = fringes.top();
			fringes.pop();
			
			// break 상황 1) 목적지 도착, 2) 고립된 정점
			if (newTree.id == dst)
			{
				ret = newTree.d;
				break;
			}
			if (adjacencyLists[newTree.id].empty())
			{
				break;
			}

			long long delayTime = 0;
			if (newTree.par != -1)	// 시작점인 경우 안함
			{
				// 현재 newTree는 어디서부터 오는 자동차를 통과시키는가
				long long whatOn = (newTree.d / periods[newTree.id]) % (long long)adjacencyLists[newTree.id].size();
				// 해당 통행이 시작된지 얼마나 되었나
				long long onTime = (newTree.d % periods[newTree.id]);
				// newTree에 오기 전에 어디서 왔는지, 그리고 그 정점이 newTree입장에서 몇번째인지
				long long seq = 0;

				for (int k = 0; k < adjacencyLists[newTree.id].size(); k++)
				{
					if (adjacencyLists[newTree.id][k].first == newTree.par)
					{
						seq = k;
						break;
					}
				}

				// 기다려야 되면 delayTime 계산
				if (whatOn != seq)
				{
					if (whatOn > seq) seq += (long long)adjacencyLists[newTree.id].size();
					delayTime = (seq - whatOn - 1) * periods[newTree.id] + (periods[newTree.id] - onTime);
				}
			}

			for (int i = 0; i < adjacencyLists[newTree.id].size(); i++)
			{
				int destIdx = adjacencyLists[newTree.id][i].first;

				// 해당 인접 버텍스로 가는 시간은 지금까지 소모한 시간 + 기다린 시간 + 도로를 지나가는 시간
				long long newDistance = newTree.d + delayTime + (long long)adjacencyLists[newTree.id][i].second;

				if (distances[destIdx] == -1 || distances[destIdx] > newDistance)
				{
					distances[destIdx] = newDistance;
					vertexInfo newVI{ destIdx, newDistance, newTree.id };
					fringes.push(newVI);
				}
			}
		}

		cout << ret << '\n';

		for (int i = 1; i <= N; i++)
		{
			if (!adjacencyLists[i].empty()) adjacencyLists[i].clear();
		}
	}
}