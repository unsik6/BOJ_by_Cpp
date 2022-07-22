// 백준 10757번 큰 수 A+B

// Input: 0 < A, B < 10^10000 (A, B는 정수)

// 숫자형 자료형은 10^10000단위의 숫자를 표현할 수 없다.
// 문자열로 표현해야 한다.

// ASCII
// 0: 48 ~ 9: 57

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
	string A, B, result;
	cin >> A >> B;
	int longerLength = static_cast<int>(A.length() > B.length() ? A.length() : B.length());
	int resultLength = longerLength + 2;
	result.resize(resultLength);
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	bool upper = false;
	int pos = 0;
	for (pos = 0; pos < static_cast<int>(result.length()) - 1; pos++)
	{
		int ofA{ 48 }, ofB{ 48 };
		if (pos < static_cast<int>(A.length())) ofA = A[pos];
		if (pos < static_cast<int>(B.length())) ofB = B[pos];
		int add = (upper ? (ofA - 48) + (ofB - 48) + 1 : (ofA - 48) + (ofB - 48));
		if (add > 9)
		{
			result[pos] = add + 38;
			upper = true;
		}
		else
		{
			result[pos] = add + 48;
			upper = false;
		}
	}
	int back = pos - 1;
	if (result[back] == 48)
	{
		result.resize(back);
	}
	else result.resize(pos);
	// 위 if-else문은 만약 result가 C문자열이라면 아래의 if문을 사용한다.
	/*if (result[back] == 48)
	{
		result.resize(pos);
		result[back] = '\0';
	}
	else result[result.length() - 1] = '\0';*/


	reverse(result.begin(), result.end());

	cout << result << endl;
}
