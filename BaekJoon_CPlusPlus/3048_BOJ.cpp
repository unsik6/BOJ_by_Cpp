/* 백준 3048번 개미
*
* Input: 개미집단 N1과 N2의 개미 수
*		 N1의 순서
*		 N2의 순서
*		 (각 개미는 알파벳 대문자로 표현, 개미 그룹 간 중복 없음)
*		 (0 <= T <= 50)

* Output: T초 후 개미들의 순서
*		  N1은 왼쪽->오른쪽, N2는 그의 반대로 이동한다.
*		  개미는 자신 앞에 마주 보는 개미가 있을 때 점프한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
	int n1, n2, t;
	cin >> n1 >> n2;
	vector<pair<char, int>> vec;
	string str;
	cin >> str;
	for (int i = n1 - 1; i >= 0; i--) vec.push_back(make_pair(str[i], 0));
	cin >> str;
	for (int i = 0; i < n2; i++) vec.push_back(make_pair(str[i], 1));

	cin >> t;
	int time = 0;
	while (time != t)
	{
		for (int i = 0; i < n1 + n2 - 1; i++)
		{
			if (vec[i].second == 0 && vec[i + 1].second == 1)
			{
				swap(vec[i], vec[i + 1]);
				i++;
			}
		}
		time++;
	}

	for (int i = 0; i < n1 + n2; i++)
		cout << vec[i].first;
}