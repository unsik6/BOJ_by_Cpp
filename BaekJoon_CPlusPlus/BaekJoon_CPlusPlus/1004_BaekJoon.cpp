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
// 즉, 출발점과 도착점이 어떤 계의 경계로 인하여 안과 밖으로 나뉘는 경우에만 진입/이탈이 발생한다.

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
	int*** arrSystems = new int**[T];					// 모든 행성계 정보: 1차원 = test, 2차원 = 행성계, 3차원 = 행성계 정보

	for (int t = 0; t < T; t++)
	{
		cin >> arrPos[4 * t] >> arrPos[1 + 4 * t]
			>> arrPos[2 + 4 * t] >> arrPos[3 + 4 * t];
		cin >> arrSystemCnt[t];
		arrSystems[t] = new int* [arrSystemCnt[t]];
		for (int s = 0; s < arrSystemCnt[t]; s++)
		{
			arrSystems[t][s] = new int[3];
			cin >> arrSystems[t][s][0] >> arrSystems[t][s][1]
				>> arrSystems[t][s][2];
		}

		int otherCnt{ 0 };
		for (int s = 0; s < arrSystemCnt[t]; s++)
		{
			bool IsStartIn{ false }, IsEndIn{ false };
			int tmpStartXfunct = arrSystems[t][s][0] - arrPos[4 * t];
			int tmpStartYfunct = arrSystems[t][s][1] - arrPos[1 + 4 * t];
			int tmpEndXfunct = arrSystems[t][s][0] - arrPos[2 + 4 * t];
			int tmpEndYfunct = arrSystems[t][s][1] - arrPos[3 + 4 * t];

			if (tmpStartXfunct * tmpStartXfunct +
				tmpStartYfunct * tmpStartYfunct < arrSystems[t][s][2] * arrSystems[t][s][2])
				IsStartIn = true;
			if (tmpEndXfunct * tmpEndXfunct +
				tmpEndYfunct * tmpEndYfunct < arrSystems[t][s][2] * arrSystems[t][s][2])
				IsEndIn = true;
			if (IsStartIn != IsEndIn) otherCnt++;
		}

		cout << otherCnt << "\n";
	}

	delete[] arrPos, arrSystemCnt;
	for (int i = 0; i < T; i++)
		delete[] arrSystems[i];
	delete[] arrSystems;

	return 0;
}