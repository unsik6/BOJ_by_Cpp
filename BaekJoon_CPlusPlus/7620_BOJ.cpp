/* 백준 7620번 편집 거리
*
* Input: 	두 개의 문자열: 영문 알파벳과 숫자로 이루어져 있음 ( 1 <= length <= 17,000)
*
* Output: 다음과 같은 4가지 연산이 있다.
*			(1) 추가 ('a'): 한글자 출력
*			(2) 삭제 ('b'): 입력 문자열 맨 앞 글자 삭제 - 출력 x
*			(3) 수정 ('m'): 입력 문자열 맨 앞 글자를 삭제 -> 바꾼 글자 출력
*			(4) 복사 ('c'): 한 글자 복사 + 입력에서 맨 앞 글자 삭제 -> 삭제 글자 출력
* 
*		  첫번째 문자열을 두번째 문자열로 바꾸는 가장 짧은 편집 스크립트를 작성하는 프로그램 작성
*
* Point: length^2 공간 사용 불가능 (거의 275 mb - 제한은 128MB)
*/

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

#define MATCHING 0
#define CHANGE 1
#define UP 2
#define LEFT 3


struct PATH
{
	unsigned char leftTop : 2;
	unsigned char rightTop : 2;
	unsigned char leftBottom : 2;
	unsigned char rightBottom : 2;
};

string x, y;
int arr[2][17001];
PATH pathArr[17002 / 2 + 10][17002 / 2 + 10];


void setPath(int _r, int _c, int _p)
{
	if (_r % 2 == 0 && _c % 2 == 0)
		pathArr[_r / 2][_c / 2].leftTop = _p;
	else if (_r % 2 == 1 && _c % 2 == 1)
		pathArr[_r / 2][_c / 2].rightBottom = _p;
	else
	{
		if (_r % 2 == 0)
			pathArr[_r / 2][_c / 2].leftBottom = _p;
		else
			pathArr[_r / 2][_c / 2].rightTop = _p;
	}
}

int getPath(int _r, int _c)
{
	if (_r % 2 == 0 && _c % 2 == 0)
		return pathArr[_r / 2][_c / 2].leftTop;
	else if (_r % 2 == 1 && _c % 2 == 1)
		return pathArr[_r / 2][_c / 2].rightBottom;
	else
	{
		if (_r % 2 == 0)
			return pathArr[_r / 2][_c / 2].leftBottom;
		else
			return pathArr[_r / 2][_c / 2].rightTop;
	}
}

int main()
{
	cin >> x >> y;
	int rownumBase = 0, rownumMaking = 1;

	arr[0][0] = 0;
	for (int i = 1; i <= x.length(); i++)
	{
		arr[0][i] = i;
		setPath(0, i, LEFT);
	}
	for (int i = 1; i <= y.length(); i++)
	{
		arr[rownumMaking][0] = i;
		setPath(i, 0, UP);

		for (int j = 1; j <= x.length(); j++)
		{
			if (x[j - 1] == y[i - 1])
			{
				arr[rownumMaking][j] = arr[rownumBase][j - 1];
				setPath(i, j, MATCHING);
			}
			else
			{
				int LDEL, UPADD, LUC, min;
				int tmpPath;

				LDEL = arr[rownumMaking][j - 1] + 1;
				UPADD = arr[rownumBase][j] + 1;
				LUC = arr[rownumBase][j - 1] + 1;

				min = LDEL;
				tmpPath = LEFT;
				if (min > UPADD)
				{
					min = UPADD;
					tmpPath = UP;
				}
				if (min > LUC)
				{
					min = LUC;
					tmpPath = CHANGE;
				}

				arr[rownumMaking][j] = min;
				setPath(i, j, (int)tmpPath);
			}
		}
		rownumMaking ^= rownumBase ^= rownumMaking ^= rownumBase;
	}

	stack<pair<char, char>> order;	// command, char
	int curR = y.length(), curC = x.length();
	while (curR > 0 || curC > 0)
	{
		int tmpPath = getPath(curR, curC);
		switch (tmpPath)
		{
		case MATCHING:
			order.push(make_pair('c', y[curR - 1]));
			curR--; curC--;
			break;
		case CHANGE:
			order.push(make_pair('m', y[curR - 1]));
			curR--; curC--;
			break;
		case LEFT:
			order.push(make_pair('d', x[curC -1]));
			curC--;
			break;
		case UP:
			order.push(make_pair('a', y[curR - 1]));
			curR--;
			break;
		}
	}

	while (!order.empty())
	{
		cout << order.top().first << ' ' << order.top().second << '\n';
		order.pop();
	}

}