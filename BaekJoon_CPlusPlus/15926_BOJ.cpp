/* 백준 15926번 현욱은 괄호왕이야!!
*
* Input: 문자열의 길이 n (1 <= n <= 200,000)
*		 문자열

* Output: 올바른 괄호 문자열의 최대 길이
*		  1) ()는 올바른 괄호문자열이다.
*		  2) 어떤 문자열 x가 올바른 괄호 문자열이라면, (x)도 올바른 괄호 문자열이다.
*		  3) 어떤 문자열 x와 y가 올바른 괄호 문자열이라면, xy도 올바른 괄호 문자열이다.
*
* (의 인덱스를 스택에 넣고 )가 나올 때 pop한다.
* 올바른 문자열 안쪽에서 발생한 올바른 문자열은 바깥쪽을 넘을 수 없다.
*/

#include <iostream>
#include <stack>
using namespace std;

int n;
string str;
stack<int> stk;

int main() {
	cin >> n >> str;
	stk.push(-1);
	int maximum = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == '(')
		{
			stk.push(i);
		}
		else {
			stk.pop();
			if (!stk.empty())
			{
				maximum = max(maximum, i - stk.top());
			}
			else stk.push(i);
		}
	}
	cout << maximum;
}