/* 백준 2087 암호문
*
*Input: bit의 수 n (5<= n <= 40)
*		n개의 줄에 자연수 a_i (sum(a_1, a_2, ... a_n) <= 2'000'000'000)
*		K

* Output : K = a_1 * t_1 + a_2 * t_2 + ... + a_n * t_n을 만족하는 이진 암호문 t_1t_2t_3...t_n (t_i = 0 OR 1)
*/

#include <iostream>
#include <algorithm>

using namespace std;

#define POW2_20 1048576

// input
int N, K, halfSize;
int As1[20], As2[20];

// Sum table
// 2'000'000'000이 2^20보다 한참 크기 때문에 case 별로 저장한다.
// 정렬해서 이진탐색으로 검색해야 하기 때문에 case도 같이 저장한다.
pair<int, int> halfSum1[POW2_20];	// half[case] = {합, case}
pair<int, int> halfSum2[POW2_20];

int computeHalf(int* _arrAs, pair<int, int>* _sumArr, int _halfSize)
{
	// 모두가 0인 경우는 굳이 할 필요 없음.
	for (int bit = 1; bit < (1 << _halfSize); bit++)
	{
		// 한 가지의 경우만 찾으면 되므로 이미 같은 합을 만든 경우가 있으면 수행 안한다.
		if (_sumArr[bit].second != 0)
			continue;

		int curCase = bit;
		int arrIdx = 0;
		int sum = 0;
		while (curCase > 0)
		{
			if (curCase % 2 == 1)
				sum += _arrAs[arrIdx];
			curCase /= 2;
			arrIdx++;
		}

		// K를 이미 찾은 경우 bit 리턴
		if (sum == K)
			return bit;

		_sumArr[bit] = { sum, bit };
	}

	return -1;
}

void printDecimalToCode(int _decimal, int _size)
{
	int cnt = 0;
	while (_decimal > 0)
	{
		cout << _decimal % 2;
		_decimal /= 2;
		cnt++;
	}

	for (int i = 0; i < _size - cnt; i++)
		cout << 0;
}

bool Comp_lower_bound(const pair<int, int> _a, const pair<int, int> _b)
{
	return _a.first < _b.first;
}

int main()
{
	cin >> N;
	halfSize = N / 2;
	for (int n = 0; n < halfSize; n++)
		cin >> As1[n];
	for (int n = 0; n < N - halfSize; n++)
		cin >> As2[n];
	cin >> K;

	int checkEnd = computeHalf(As1, halfSum1, halfSize);
	// 만약 이미 K를 찾은 경우
	if (checkEnd != -1)
	{
		printDecimalToCode(checkEnd, halfSize);
		
		for (int i = 0; i < N - halfSize; i++)
			cout << 0;
		return 0;
	}
	checkEnd = computeHalf(As2, halfSum2, N - halfSize);
	if (checkEnd != -1)
	{
		// 뒷부분이니까 앞부분 먼저 출력
		for (int i = 0; i < N - halfSize; i++)
			cout << 0;

		printDecimalToCode(checkEnd, N - halfSize);
		
		return 0;
	}
	
	// 뒷부분 합 배열 정렬
	int  size2 = 1 << (N - halfSize);
	sort(halfSum2, halfSum2 + size2);

	// 답 찾기
	int firstBit = -1, secondBit = -1;
	for (int i = 1; i < (1 << halfSize); i++)
	{
		// 앞 부분의 합이 0인 경우는 위에서 별도 처리함.
		if (halfSum1[i].second == 0)
			continue;
		
		int targetSum = K - halfSum1[i].first;	// 남은 수를 찾아야 한다.

		// 단일 값이 아닐 때, lower_bound 사용하는 방법
		int targetIdx = lower_bound(halfSum2, halfSum2 + size2, pair<int,int>(targetSum, 0), Comp_lower_bound) - halfSum2;

		if (targetIdx < size2)
		{
			if (halfSum2[targetIdx].first == targetSum)
			{
				firstBit = i; secondBit = halfSum2[targetIdx].second;
				break;
			}
		}
	}

	// 답 출력
	printDecimalToCode(firstBit, halfSize);
	printDecimalToCode(secondBit, N - halfSize);	

	return 0;
}