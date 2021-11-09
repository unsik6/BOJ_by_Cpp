// 백준 1010번 다리 놓기

// Input: T = 테스트 케이스의 개수, N = 왼쪽 사이트 개수, M = 오른쪽 사이트 개수
// condition: N개 만큼의 다리
//			  다리끼리는 겹쳐질 수 없음.
//			  (정수) 0 < N <= M < 30 

// 조합(combination)
// 다리를 어떻게 연결하든 다리를 연결하는 순서는 정해져 있으므로
// M개의 박스에 N개의 사탕을 최대 1개 넣을 수 있는 겨우의 수와 같다.
// C(m, n) = m! / n! (m-n)!

#include <iostream>

int main()
{
	int t;
	std::cin >> t;
	double *N = new double[t];
	double* M = new double[t];
	for(int i= 0; i < t; i++) std::cin >> N[i] >> M[i];

	for (int i = 0; i < t; i++)					// test count
	{
		// 30 정도까지 가면 수가 엄청 많아짐. => 자료형 선택
		double limit = (N[i] > M[i] - N[i] ? M[i] - N[i] : N[i]);	// 더 작은수로 반복문을 돌리기 위함.
		unsigned long long MFactorial = 1;
		unsigned long long limFactoial = 1;

		for (double f = 0; f < limit; f++)
		{
			MFactorial *= (M[i] - f);
			limFactoial *= (limit - f);
		}

		std::cout << MFactorial/limFactoial << "\n";
	}

	return 0;
}