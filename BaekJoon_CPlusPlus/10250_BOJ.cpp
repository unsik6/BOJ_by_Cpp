// 백준 10250번 ACM 호텔

// Input: 1<= H = 층수, W = 각 층의 호수 <= 99, 1 <= N <= H*W
// condition: 각 손님들은 더 적게 걸을수록 좋고, 같은 걸음이라면 낮은 층을 선호

// 어차피 왼쪽부터 차례대로 쌓아올라간다.

#include<iostream>
using namespace std;

int main()
{
	int T;
	cin >> T;
	int* Hs = new int[T];
	int* Ws = new int[T];
	int* Ns = new int[T];

	for (int i = 0; i < T; i++)
		cin >> Hs[i] >> Ws[i] >> Ns[i];

	for (int i = 0; i < T; i++)
	{
		int row = (Ns[i] % Hs[i] == 0 ? Ns[i] / Hs[i] : Ns[i] / Hs[i] + 1);
		int floor = (Ns[i] % Hs[i] == 0 ? Hs[i] : Ns[i] % Hs[i]);
		cout << floor * 100 + row << endl;
	}
	delete[] Hs;
	delete[] Ws;
	delete[] Ns;
}