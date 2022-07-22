// 백준 7568번 덩치

// input: 1 <= N = 사람 수 <= 50
//		  10 <= x, y = 몸무게, 키 <= 200

// condition: 키와 몸무게가 모두 크다면 그것은 상대적으로 '덩치가 크다' (초과만 해당)
//			  만약 둘다 초과하지 않는다면 덩치를 구분할 수 없으므로 같은 등수이다.
//			  자신보다 덩치가 큰 사람 수 +1이 등수이다.

// 브루트포스 알고리즘: 가능한 또는, 유의미한 케이스들을 모두 검사하는 것이다.

#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		arr[i] = new int[3];
		cin >> arr[i][0] >> arr[i][1];
		arr[i][2] = 1;
	}
	for (int i = 0; i < N; i++)
	{
		for (int f = 0; f < N; f++)
		{
			if (arr[i][0] < arr[f][0] && arr[i][1] < arr[f][1])
				arr[i][2] += 1;
		}
		cout << arr[i][2] << '\n';
	}

	for (int i = 0; i < N; i++) delete[] arr[i];
	delete[] arr;
}