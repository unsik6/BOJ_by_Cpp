// 백준 1158번 요세푸스 문제

#include <iostream>
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	int* arr = new int[N];
	for (int i = 0; i < N; i++) arr[i] = i + 1;
	int st{ 0 }, curIndex{ 0 };
	while (true)
	{
		if (curIndex == N) break;
		int et{ 0 }, add{ 0 };
		while (et < K)
		{
			int cur = (st + et + add >= N ? st + et + add - N :st + et + add);
			if (arr[cur] == 0)
			{
				add++;
				continue;
			}
			else
			{
				if (et == K - 1)
				{
					cout << arr[cur];
					arr[cur] = 0;
					st = cur + 1;
				}
				add = 0;
				et++;
			}
		}
		curIndex++;
	}

	delete[] arr;
	

	return 0;
}