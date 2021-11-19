// 백준 2839번 설탕배달

// Input: 3 <= N = 배달해야할 설탕 kg <= 5000
// condition: 3kg, 5kg 주머니가 있다.
//			  최대한 적은 주머니 수로 배달한다.
//			  만약 정확하게 N을 만들 수 없다면 -1를 출력한다.

// 최대한 5로 나누고 나머지를 3으로 나누는게 가장 좋다. (Greedy)
// 하지만 만약 최대한 5로 나눈 나머지가 3으로 나눠떨어지지 않는다면
// 5kg 주머니를 줄여가며 3으로 나눌 수 있도록 맞춘다.
// 만약 5kg 주머니가 0개인데도 3으로 나눌 수 없다면
// 그건 만들 수 없는 것이다.

#include<iostream>

int main()
{
	int N;
	std::cin >> N;
	int cnt = N / 5;
	while (true)
	{
		if ((N - (5 * cnt)) % 3 == 0)
		{
			cnt += (N - (5 * cnt)) / 3;
			std::cout << cnt;
			break;
		}
		else
		{
			if (cnt == 0)
			{
				std::cout << -1;
				break;
			}
			else cnt--;
		}
	}
	return 0;
}