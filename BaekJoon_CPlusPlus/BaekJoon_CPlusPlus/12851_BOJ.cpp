/* 백준 12851번 숨바꼭질2
*
* Input: 수빈의 위치 (0 <= N <= 100,000)
*		 동생의 위치 (0 <= K <= 100,000)
*
* Output: 수빈이는 X-1또는 X+1, X*2로 이동
*		  첫째 줄: 수빈이가 동생을 찾는 가장 빠른 시간 출력
*		  둘째 줄: 가장 빠른 시간으로 수빈이가 동생을 찾는 방법의 수
*/

#include <iostream>
#include <queue>
using namespace std;

int arr[100001]{ 0 };

int main()
{
	for (int i = 0; i < 100001; i++)
	{
		arr[i] = 1000002;
	}
	int src, dst;
	cin >> src >> dst;

	if (src == dst)
	{
		cout << 0 << '\n' << 1;
	}
	else
	{
		queue<int> visitedNodes;
		visitedNodes.push(src);
		arr[src] = 0;
		int shortestPath = 100002;
		int cnt = 0;
		while (!visitedNodes.empty())
		{
			int curNode = visitedNodes.front();
			visitedNodes.pop();

			if (curNode > 0)
			{
				if (arr[curNode - 1] >= arr[curNode] + 1)
				{
					visitedNodes.push(curNode - 1);
					arr[curNode - 1] = arr[curNode] + 1;
				}
				if (curNode - 1 == dst)
				{
					if (shortestPath == arr[curNode] + 1)
					{
						cnt++;
					}
					else if (shortestPath > arr[curNode] + 1)
					{
						shortestPath = arr[curNode] + 1;
						cnt = 1;
					}
				}
			}
			if (curNode < 100000)
			{
				if (arr[curNode + 1] >= arr[curNode] + 1)
				{
					visitedNodes.push(curNode + 1);
					arr[curNode + 1] = arr[curNode] + 1;
				}
				if (curNode + 1 == dst)
				{
					if (shortestPath == arr[curNode] + 1)
					{
						cnt++;
					}
					else if (shortestPath > arr[curNode] + 1)
					{
						shortestPath = arr[curNode] + 1;
						cnt = 1;
					}
				}
			}
			if (curNode <= 50000)
			{
				if (arr[curNode * 2] >= arr[curNode] + 1)
				{
					visitedNodes.push(curNode * 2);
					arr[curNode * 2] = arr[curNode] + 1;
				}
				if (curNode * 2 == dst)
				{
					if (shortestPath == arr[curNode] + 1)
					{
						cnt++;
					}
					else if (shortestPath > arr[curNode] + 1)
					{
						shortestPath = arr[curNode] + 1;
						cnt = 1;
					}
				}
			}
		}

		cout << shortestPath << '\n' << cnt;
	}
	
	return 0;
}