// 백준 2138번 전구와 스위치

// input: 배열의 길이 N (2 <= N <= 100,000)
//		  arr[i]의 상태 (0, 1)
//		  원하는 arr[i]의 상태 (0, 1)

// condition: i번째 스위치를 누를 경우, i-1, i, i+1이 바뀐다. 양 끝은 안쪽 1개와 본인만 바뀐다.
//			  전구 배열의 상태를 원하는 형태로 바꿀 수 있는 최소한의 스위치 조작 횟수를 출력하라. 
//			  불가능한 경우 -1 출력

// i번째 전구를 고려하여 i+1번째 스위치를 작동한다.
// 이전의 전구가 다르면 스위치를 켠다.
// 이렇게 하면 앞으로의 결정에서 이전에 맞춰둔 전구가 영향을 받지 않는다.
// 단, 2가지 케이스를 비교해야 한다. 1번 전구를 키는 경우와 키지 않는 경우

#include<iostream>
using namespace std;

int main()
{
	int N;
	string curStr, tarStr;
	cin >> N >> curStr >> tarStr;;
	
	// case 1
	string temp = curStr;
	int cnt1 = 1;
	temp[0] = (temp[0] == '0' ? '1' : '0');
	temp[1] = (temp[1] == '0' ? '1' : '0');

	for (int i = 1; i < N; i++)
	{
		if (temp[i - 1] != tarStr[i - 1])
		{
			temp[i - 1] = (temp[i - 1] == '0' ? '1' : '0');
			temp[i] = (temp[i] == '0' ? '1' : '0');
			if(i < N - 1) temp[i + 1] = (temp[i + 1] == '0' ? '1' : '0');
			cnt1++;
		}
	}
	if (temp[N - 1] != tarStr[N - 1]) cnt1 = -1;

	// case 2
	int cnt2 = 0;
	for (int i = 1; i < N; i++)
	{
		if (curStr[i - 1] != tarStr[i - 1])
		{
			curStr[i - 1] = (curStr[i - 1] == '0' ? '1' : '0');
			curStr[i] = (curStr[i] == '0' ? '1' : '0');
			if (i < N - 1) curStr[i + 1] = (curStr[i + 1] == '0' ? '1' : '0');
			cnt2++;
		}
	}
	if (curStr[N - 1] != tarStr[N - 1]) cnt2 = -1;

	if (cnt1 == -1) cout << cnt2;
	else if (cnt2 == -1) cout << cnt1;
	else cout << (cnt1 < cnt2 ? cnt1 : cnt2);
}