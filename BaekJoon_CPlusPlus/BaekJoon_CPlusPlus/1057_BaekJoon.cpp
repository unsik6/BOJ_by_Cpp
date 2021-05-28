// 백준 1057번 토너먼트

#include <iostream>
using namespace std;


int main()
{
	int n, kim, im, round{ 0 };
	cin >> n >> kim >> im;
	while (kim != im)
	{
		kim = (kim + 1) / 2;
		im = (im + 1) / 2;
		round++;
	}
	cout << round;
	return 0;
}

// 긴 초기답
/*
int Round(int, int, int);

int N, Kim, Im;

int main()
{
	cin >> N >> Kim >> Im;

	bool IsKimPre = (Kim < Im ? true : false);

	if (IsKimPre)
		cout << Round(Kim, Im, N);
	else
		cout << Round(Im, Kim, N);

	return 0;
}

int Round(int Pre, int Aft, int N)
{
	int Round = 1;
	while (Aft%2 || Aft - Pre > 1)
	{
		Pre = ((Pre - 1) / 2) + 1;
		Aft = ((Aft - 1) / 2) + 1;

		N = (N % 2 ? N / 2 : (N + 1) / 2);

		Round++;
	}
	return Round;
}
*/