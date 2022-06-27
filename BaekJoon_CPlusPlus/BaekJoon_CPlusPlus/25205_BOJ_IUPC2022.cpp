/* 백준 25205번 경로당펑크 2077
*
* Input: 첫 번째 줄에 문자열 s의 길이를 나타내는 정수 N (2 <= N <= 30)
*		 두 번째 줄에 문자열 s
*
* Output: 사용자 이름 마지막 글자에 받침이 있다면 1, 없다면 0
*
*/

#include <iostream>
using namespace std;

int main()
{
	int N; string str;
	cin >> N >> str;
	if (str[N - 1] == 'r' || str[N - 1] == 'R' || str[N - 1] == 't' || str[N - 1] == 's'
		|| str[N - 1] == 'w' || str[N - 1] == 'g' || str[N - 1] == 'e' || str[N - 1] == 'f'
		|| str[N - 1] == 'a' || str[N - 1] == 'q' || str[N - 1] == 'x' || str[N - 1] == 'v'
		|| str[N - 1] == 'T' || str[N - 1] == 'd' || str[N - 1] == 'c' || str[N - 1] == 'z')
	{
		cout << 1;
	}
	else cout << 0;
	return 0;
}