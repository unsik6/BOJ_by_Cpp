// 백준 1463번 1로 만들기

// input: 1 <= X <= 10^6 (정수)

// condition: 1) X가 3으로 나누어 떨어지면 3으로 나눈다.
//			  2) X가 2로 나누어 떨어지면 2로 나눈다.
//			  3) 1을 뺀다.


#include<iostream>
using namespace std;

int main()
{
	int X;
	cin >> X;
	int* arr = new int[X + 1];
	if (X == 1) cout << 0;
	else if (X == 2) cout << 1;
	else if (X == 3) cout << 1;
	else if (X >= 4)
	{
		arr[2] = 1;
		arr[3] = 1;
		int cnt = 4;
		while (cnt <= X)
		{
			arr[cnt] = arr[cnt - 1] + 1;
			if (cnt % 2 == 0)
				arr[cnt] =(arr[cnt] < arr[cnt / 2] + 1 ? arr[cnt] : arr[cnt / 2] + 1);
			if (cnt % 3 == 0)
				arr[cnt] = (arr[cnt] < arr[cnt / 3] + 1 ? arr[cnt] : arr[cnt / 3] + 1);
			cnt++;
		}
		
		cout << arr[X] << '\n';

		delete[] arr;
	}
}