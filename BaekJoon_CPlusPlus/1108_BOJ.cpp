/* 백준 1108 검색 엔진
*
* Input: 링크 정보의 수 N (1 <= N <= 50)
*		 N개의 줄에 링크 정보
*		 L i l1 l3 ... li ( li ... li로부터 L로 가는 링크가 존재, 모든 링크의 이름은 문자열 S(|S| <= 50)이다. )
*						  (0 <= i <= 24)
*		 점수를 알고자 하는 링크 이름 (만드시 링크 정보에 포함됨)
* 
*		 1) 모든 링크의 초기 점수는 1이다.
*		 2) V -> W 링크가 있는 경우 V의 점수를 W에 더한다.
*		 3) 만약 V ~> W가 존재한다면 W->V로 인한 점수 이동은 하지 않는다.

* Output: 점수를 알고자 하는 링크 이름의 점수
*/

// 2)의 조건을 위해 위상정렬을 이용한다.
// 3)의 조건을 위해 SCC를 이용한다.
// 링크 이름을 해싱하여 인덱스를 구성한다.

// 프로세스
// 1. 그래프 생성
// 2. SCC 계산
// 3. 같은 SCC에 있는 노드 간의 간선 제거
// 3. 위상정렬 후 점수 부여

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define UM_SI unordered_map<string, int>
#define INT_VEC vector<int>

// input
int iLinkNum;

// output
long long arrLinkScores[1250];	// 정점 개수가 25*50 = 1250임.

// DataStructure
UM_SI mapLinks;				// 정점 해시
INT_VEC vecGraph[1250];		// 그래프
INT_VEC vecGraphT[1250];	// 간선 뒤집은 그래프
INT_VEC vecGraphN[1250];	// SCC 내 간선 제거한 그래프
INT_VEC vecGraphNT[1250];	// SCC 내 간선을 제거하고, 간선을 뒤집은 그래프

// For SCC
bool arrVisited[1250]{ false };		// DFS 내에서 방문여부 판단
bool arrFinished[1250]{ false };	// DFS 내에서 종료여부 판단
void resetDFSArr()
{
	for (int i = 0; i < iLinkNum; i++)
		arrVisited[i] = arrFinished[i] = false;
}
stack<int> stkAncestors;	// DFS용 스택
stack<int> stkFinished;		// DFS 종료 순으로 저장되는 스택
int arrSCCL[1250];

// For Topological Sorting
int arrIndegSort[1250];
bool compVt(int _iVt1, int _iVt2)
{
	return vecGraphNT[_iVt1].size() < vecGraphNT[_iVt2].size();
}
int arrTPSort[1250];

int main()
{
	// input
	int iVtNum, iIndegNum;
	string strDst, strSrc;

	cin >> iVtNum;
	int iVtIdx = 0;	// 지정할 정점 인덱스
	for (int i = 0; i < iVtNum; i++)
	{
		cin >> strDst >> iIndegNum;

		// strDst가 해시에 저장된 적이 없다면 저장한다.
		if (mapLinks.find(strDst) == mapLinks.end())
			mapLinks[strDst] = iVtIdx++;

		for (int j = 0; j < iIndegNum; j++)
		{
			cin >> strSrc;
			if (mapLinks.find(strSrc) == mapLinks.end())
				mapLinks[strSrc] = iVtIdx++;

			// 그래프에 넣기
			vecGraph[mapLinks[strSrc]].push_back(mapLinks[strDst]);
			vecGraphT[mapLinks[strDst]].push_back(mapLinks[strSrc]);
		}
	}

	// 링크 개수
	iLinkNum = mapLinks.size();

	// initiate Scores
	for (int i = 0; i < iLinkNum; i++)
		arrLinkScores[i] = 1;

	// Construct SCC
	// first DFS
	for (int i = 0; i < iLinkNum; i++)
	{
		if (!arrVisited[i])
		{
			stkAncestors.push(i);
			while (!stkAncestors.empty())
			{
				int iCurVt = stkAncestors.top();

				if (arrVisited[iCurVt])
				{
					stkAncestors.pop();
					if (!arrFinished[iCurVt])
					{
						stkFinished.push(iCurVt);
						arrFinished[iCurVt] = true;
					}
					continue;
				}
				else
					arrVisited[iCurVt] = true;

				for (int iAdjIdx = 0; iAdjIdx < vecGraph[iCurVt].size(); iAdjIdx++)
				{
					int iAdjVt = vecGraph[iCurVt][iAdjIdx];
					if (!arrVisited[iAdjVt])
						stkAncestors.push(iAdjVt);
				}
			}
		}
	}

	resetDFSArr();
	// second DFS
	while (!stkFinished.empty())
	{
		int iStartVt = stkFinished.top();
		stkFinished.pop();
		
		if (arrVisited[iStartVt])
			continue;

		stkAncestors.push(iStartVt);
		while (!stkAncestors.empty())
		{
			int iCurVt = stkAncestors.top();
			stkAncestors.pop();

			arrVisited[iCurVt] = true;
			arrSCCL[iCurVt] = iStartVt;

			for (int iAdjIdx = 0; iAdjIdx < vecGraphT[iCurVt].size(); iAdjIdx++)
			{
				int iAdjVt = vecGraphT[iCurVt][iAdjIdx];
				if (!arrVisited[iAdjVt])
					stkAncestors.push(iAdjVt);
			}
		}
	}

	// construct new Graph
	for (int i = 0; i < iLinkNum; i++)
	{
		for (int j = 0; j < vecGraph[i].size(); j++)
		{
			int iAdjVt = vecGraph[i][j];
			if (arrSCCL[i] != arrSCCL[iAdjVt])
			{
				vecGraphN[i].push_back(iAdjVt);
				vecGraphNT[iAdjVt].push_back(i);
			}
		}
	}
	
	// Topological Sorting
	// Indeg Sort
	// initialize
	for (int i = 0; i < iLinkNum; i++)
		arrIndegSort[i] = i;

	std::sort(arrIndegSort, arrIndegSort + iLinkNum, compVt);

	resetDFSArr();
	// DFS
	for (int i = 0; i < iLinkNum; i++)
	{
		int iStartVt = arrIndegSort[i];

		if (arrVisited[iStartVt])
			continue;

		stkAncestors.push(iStartVt);
		while (!stkAncestors.empty())
		{
			int iCurVt = stkAncestors.top();

			if (arrVisited[iCurVt])
			{
				stkAncestors.pop();
				if (!arrFinished[iCurVt])
				{
					stkFinished.push(iCurVt);
					arrFinished[iCurVt] = true;
				}
				continue;
			}
			else
				arrVisited[iCurVt] = true;
			

			for (int iAdjIdx = 0; iAdjIdx < vecGraphN[iCurVt].size(); iAdjIdx++)
			{
				int iAdjVt = vecGraphN[iCurVt][iAdjIdx];
				if (!arrVisited[iAdjVt])
				{
					stkAncestors.push(iAdjVt);
				}
				
			}
		}
	}

	// Score
	for (int i = 0; i < iLinkNum; i++)
	{
		int iCurVt = stkFinished.top();
		stkFinished.pop();
		for (int iAdjIdx = 0; iAdjIdx < vecGraphN[iCurVt].size(); iAdjIdx++)
		{
			int iAdjVt = vecGraphN[iCurVt][iAdjIdx];
			arrLinkScores[iAdjVt] += arrLinkScores[iCurVt];
		}
	}

	string strTarget;
	cin >> strTarget;
	cout << arrLinkScores[mapLinks[strTarget]];

	return 0;
}