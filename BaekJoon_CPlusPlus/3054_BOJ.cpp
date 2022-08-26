/* 백준 3054번 피터팬 프라임
*
* Input: 단어 (알파벳 대문자로 구성, 최대 15글자)

* Output: 3의 배수 위치의 문자는 웬디 프레임으로, 나머지는 피터팬 프레임으로 장식
*		  겹치는 경우 웬디 프라임으로
*/

#include <iostream>
using namespace std;

string str;
int len;
int cnt = 0;

void printFirstFifth()
{
	for (int i = 1; i <= (len * 5) - len + 1; i++)
	{
		if (i % 4 == 3)
		{
			if ((i % 3) % 3 == 2)
				cout << '*';
			else cout << '#';
		}
		else cout << '.';
	}
	cout << '\n';
}

void printSecondFourth()
{
	for (int i = 1; i <= (len * 5) - len + 1; i++)
	{
		if (i % 2 == 0)
		{
			if ((i / 2) % 2 == 0)
			{
				if ((i / 2) / 2 % 3 == 0)
					cout << '*';
				else cout << '#';
			}
			else
			{
				if (((i / 2) / 2 + 1) % 3 == 0)
					cout << '*';
				else cout << '#';
			}
		}
		else cout << '.';
	}
	cout << '\n';
}

void printCenter()
{
	for (int i = 1; i <= (len * 5) - len + 1; i++)
	{
		if (i % 2 == 1)
		{
			if (i % 4 == 3)
			{
				cout << str[cnt++];
			}
			else
			{
				if (cnt % 3 == 2 || (cnt - 1) % 3 == 2)
				{
					if (cnt == len && cnt % 3 != 0) cout << '#';
					else cout << '*';
				}
				else cout << '#';
			}
		}
		else cout << '.';
		
	}
	cout << '\n';
}

int main()
{
	cin >> str; len = (int)str.length();
	printFirstFifth();
	printSecondFourth();
	printCenter();
	printSecondFourth();
	printFirstFifth();
	return 0;
}