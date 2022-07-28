/* 백준 2216번 문자열과 점수
*
* Input: 	A, B, C ( 0 <= A <= 10,000, -10,000 <= B, C < 0)
*			문자열 X
*			문자열 Y
*			( 1 <= |X|, |Y| <= 3,000)
*
* Output: 줄 세우기
*
* Point: 가중 편집 거리
*/

#include <iostream>
using namespace std;

string x, y;
int A, B, C;

int arr[3001][3001]{ 0 };

int main()
{
	cin >> A >> B >> C >> x >> y;

	int xlen = x.length(); int ylen = y.length();

	for (int i = 1; i <= xlen; i++)
		arr[i][0] = arr[i-1][0] + B;
	for (int j = 1; j <= ylen; j++)
		arr[0][j] = arr[0][j-1] + B;

	for (int i = 1; i <= xlen; i++)
	{
		for (int j = 1; j <= ylen; j++)
		{
			if (x[i - 1] == y[j - 1])
				arr[i][j] = arr[i - 1][j - 1] + A;
			else
			{
				int down = arr[i - 1][j] + B;
				int right = arr[i][j - 1] + B;
				int rd = arr[i - 1][j - 1] + C;

				int max = down;
				if (max < right) max = right;
				if (max < rd) max = rd;

				arr[i][j] = max;
			}		
		}
	}

	cout << arr[xlen][ylen];
}