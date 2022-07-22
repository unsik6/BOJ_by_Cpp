// 백준 1024번 수열의 합

// Input: N = 합, L = 길이
// condition: 음이 아닌 정수 리스트
//			  (자연수) N <= 1,000,000,000 && 100 >= (자연수)L >= 2


// 등차 수열의 합
// An = A1 + (n-1)d
// Sn = n(2A1+(n-1)d)/2

#include <iostream>

int main()
{
	double N, L;
	std::cin >> N >> L;
	int first{ 0 };
	while (true)
	{
		// L이 100을 넘기면 -1 출력
		if (L > 100)
		{
			std::cout << -1;
			return 0;
		}
		// Sn 공식을 전개
		// Sn = N, n = L, d = 1
		// A1 = N / L - L / 2 + 1/2
		
		double dtmpResult = (N / L) - (L / 2) + 0.5;
		if (dtmpResult < 0 || dtmpResult > 1000000000) // 첫째 항 조건
		{
			std::cout << -1;
			return 0;
		}

		int itmpResult = static_cast<int>(dtmpResult);
		if (dtmpResult - itmpResult != 0)
		{
			L++;
			continue;
		}
		
		first = itmpResult;
		break;
	}

	for (int i = 0; i < L; i++) std::cout << first + i << " ";

	return 0;
}