// 백준 2750번 수 정렬하기

// input: 1 <= N = 정수 개수 <= 1,000
//		  |x| <= 1,000 (중복 안됨)

#include<iostream>

int main()
{
	int N;
	std::cin >> N;
	int* arr = new int[N];
	for (int i = 0; i < N; i++) std::cin >> arr[i];
	int* result = new int[N];
	for (int i = 1; i < N; i++) result[i] = 1000;
	result[0] = arr[0];
	for (int i = 1; i < N; i++)
	{
		for (int f = 0; f < N; f++)
		{
			if (arr[i] < result[f])
			{
				for (int k = N -1; k > f; k--)
					result[k] = result[k - 1];
				result[f] = arr[i];
				break;
			}
		}
	}
	for (int i = 0; i < N; i++) std::cout << result[i] << '\n';
}