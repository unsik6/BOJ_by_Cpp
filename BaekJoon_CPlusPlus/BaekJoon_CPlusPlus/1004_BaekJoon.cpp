// 백준 1004번 어린 왕자 푸는중

// Input: T = 테스트 케이스의 개수, n = 행성계의 개수
//		  (x1, y2) = 출발점 좌표, (x2, y2) = 도착점 좌표
//		  (Cx, Cy, r) = 행성계의 중심점 좌표와 반지름

// condition: 행성계 진입/이탈을 최소한으로 하는 경로
//			  1) 행성계는 교차하거나 접하지 않는다.
//			  2) 출발점/도착점이 행성계의 경계에 있는 경우, 진입/이탈로 간주하지 않는다.
//			  (정수) -1000 <= x1, y1, x2, y2, Cx, Cy <= 1000
//			  (정수) 1 <= r <= 1000, 1 <= n <= 50

// 조건 1)에 의하여 행성계 내의 이동 중에는 진입/이탈이 발생하지 않는다.
// 즉, 출발점과 도착점이 모두 포함된 계를 찾은 후,
// 출발점과 도착점에 대하여 각각 얼마나 깊숙히 있는지를 도출한다.
// 그리고 그 값을 더해준다.

// 좌표들과 반지름의 조건에 의하여, 원의 방정식의 값들의 결과의 최대가 2*10^6이다. int 가능

#include <iostream>
using namespace std;

int main()
{
	int T;
	cin >> T;
	int arrPoslen = T * 4;
	int* arrPos = new int[arrPoslen];					// 모든 출발점과 도착점 좌표
	int* arrSystemCnt = new int[T];						// 모든 행성계 개수
	int** arrSystems = new int*[T];						// 모든 행성계 정보

	for (int i = 0; i < T; i++)
	{
		cin >> arrPos[4 * i] >> arrPos[1 + 4 * i]
			>> arrPos[2 + 4 * i] >> arrPos[3 + 4 * i];
		cin >> arrSystemCnt[i];
		int SystemInfoCnt = 3 * arrSystemCnt[i];
		arrSystems[i] = new int[SystemInfoCnt];
		for (int f = 0; f < arrSystemCnt[i]; f++)
		{
			int SystemNInfo = 3 * f;
			cin >> arrSystems[i][SystemNInfo] >> arrSystems[i][1 + SystemNInfo]
				>> arrSystems[i][2 + SystemNInfo];
			cout << f << "번째 정보: " << arrSystems[i][SystemNInfo]
				<< " " << arrSystems[i][1 + SystemNInfo]
				<< " " << arrSystems[i][2 + SystemNInfo];
		}
	}

	for (int i = 0; i < T; i++)
	{
		int startPosLevel{ 0 }, endPosLevel{ 0 };
		for (int f = 0; f < arrSystemCnt[i]; f++)
		{
			bool IsStartIn{ false }, IsEndIn{ false };
			int tmpStartXfunct = arrSystems[i][3 * f] - arrPos[4 * i];
			int tmpStartYfunct = arrSystems[i][1 + 3 * f] - arrPos[1 + 4 * i];
			int tmpEndXfunct = arrSystems[i][3 * f] - arrPos[2 + 4 * i];
			int tmpEndYfunct = arrSystems[i][1 + 3 * f] - arrPos[3 + 4 * i];

			if (tmpStartXfunct * tmpStartXfunct + tmpStartYfunct * tmpStartYfunct < arrSystems[i][2 + 3 * f])
			{
				startPosLevel++;
				IsStartIn = true;
			}
			if (tmpEndXfunct * tmpEndXfunct + tmpEndYfunct * tmpEndYfunct < arrSystems[i][2 + 3 * f])
			{
				endPosLevel++;
				IsEndIn = true;
			}
			if (IsStartIn * IsEndIn != 0) break;
		}

		cout << startPosLevel + endPosLevel << "\n";
	}

	delete[] arrPos, arrSystemCnt;
	for (int i = 0; i < T; i++)
		delete[] arrSystems[i];
	delete[] arrSystems;
}