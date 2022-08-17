/* 백준 17831번 대기업 승범이네
*
* Input: 판매원의 수 (2 <= N <= 200,000) - 판매원들은 1~N으로 번호가 매겨지고, 승범이는 항상 1번
*		 2번 판매원부터 N번 판매원의 사수
*		 i번 판매원의 실력을 나타내는 정수 A_i(0 <= A_i <= 100)
*
* Output: 모든 멘토링 관계에서 발생하는 시너지의 합의 최대값이 가장 큰 경우의 시너지의 합
*		  사수-부사수 관계에서 멘토링 관계가 성립할 수 있다.
*		  멘토링 관계가 맺어진 판매원은 다른 판매원가 멘토링 관계가 될 수 없다.
*		  시너지 값은 멘토링 관계가 맺어진 판매원끼리의 실력을 곱한 값이다.
* 
* DP문제로, Subtree의 루트가 자신의 자식과 멘토링 관계인지 (즉, 자신의 부모와 멘토링 관계가 될 수 없는지) 그 반대인지를 고려하면 된다.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define MAX 200000

int skill[MAX + 1]{ 0 };
int par[MAX + 1];
vector<int> children[MAX + 1];
vector<bool> flag[MAX + 1];
int TF[MAX + 1][2]{ 0 };	// [i][0]는 자신이 자신의 자식과 멘토링일 때, [i][1]은 자신의 자식과 멘토링이 아닐 때

int main()
{
	// 판매원 수 입력
	int n;
	cin >> n;

	// 사수(부모 노드) 입력
	for (int i = 2; i <= n; i++)
	{
		cin >> par[i];
		children[par[i]].push_back(i);
		flag[par[i]].push_back(false);
	}

	// 능력 입력
	for (int i = 1; i <= n; i++)
		cin >> skill[i];

	queue<int> BFS;
	stack<int> rev;

	BFS.push(1);
	rev.push(1);
	while (rev.size() < n)
	{
		int cur = BFS.front();
		BFS.pop();
		for (int i = 0; i < children[cur].size(); i++)
		{
			BFS.push(children[cur][i]);
			rev.push(children[cur][i]);
		}
	}

	while (!rev.empty())
	{
		int cur = rev.top();
		rev.pop();

		if (children[cur].empty())
		{
			TF[cur][0] = 0;
			TF[cur][1] = 0;
		}
		else
		{
			// 먼저 내가 자식들이랑 멘토링 안 할 때 - 즉, 자식들이 자신들의 서브트리의 최대 값을 저장
			int maxOfChildren = 0;
			for (int i = 0; i < children[cur].size(); i++)
			{
				// 자식놈이 자기 자식이랑 연결된 경우가 더 클 때
				if (TF[children[cur][i]][0] > TF[children[cur][i]][1])
				{
					maxOfChildren += TF[children[cur][i]][0];
					flag[cur][i] = false;
				}
				// 자식놈이 자기 자식이랑 연결 안 된 경우가 더 클 때
				else
				{
					maxOfChildren += TF[children[cur][i]][1];
					flag[cur][i] = true;
				}
			}
			TF[cur][1] = maxOfChildren;

			// 자식 중 하나와 연결되는 경우
			for (int i = 0; i < children[cur].size(); i++)
			{
				int curValue = 0;
				// cur랑 i번째 자식이 멘토링될 수 있음.
				if (flag[cur][i])
				{
					curValue = maxOfChildren + skill[cur] * skill[children[cur][i]];
				}
				// cur랑 i번째 자식이 멘토링 될 수 없음 => 자식이 자기 자식이랑 멘토링인 걸 끊어내고 cur랑 멘토링
				else
				{
					curValue = maxOfChildren - TF[children[cur][i]][0] + TF[children[cur][i]][1] + skill[cur] * skill[children[cur][i]];
				}

				if (TF[cur][0] < curValue)
					TF[cur][0] = curValue;
			}	
		}
	}

	cout << (TF[1][0] > TF[1][1] ? TF[1][0] : TF[1][1]);

	return 0;
}