// 백준 1149번 RGB거리

// input: 1 <= N = 집의 개수 <= 1,000 (자연수)
//		  각 줄에 집마다 R, G, B를 칠하는 가격 (1 <= x <= 1,000) (자연수)

// condition: 모든 집을 칠하는 비용의 최소값
//			  서로 붙어있는 집은 서로 다른 색이어야 한다.

// DP로 풀되 N번째 집까지의 최소 총 가격은
// N번째 집에 x라는 색을 칠할 때, N-1번째 집에 x가 아닌 다른 색을 칠한 최소값에 N번째 집에 x라는 색을 칠하는 가격을
// 더한 것 중 최소 값을 고른다.

#include <iostream>
using namespace std;

int min(int _a, int _b)
{
	return (_a < _b ? _a : _b);
}

int main()
{
	int N;
	cin >> N;

	// the prices of painting each color for each house
	int**rgbArr = new int*[N];
	for (int i = 0; i < N; i++)
	{
		rgbArr[i] = new int[3];
	}
	for (int i = 0; i < N; i++)
	{
		cin >> rgbArr[i][0] >> rgbArr[i][1] >> rgbArr[i][2];
	}
		
	// optimal solution memoziation array
	int** solution = new int*[N];
	for (int i = 0; i < N; i++)
		solution[i] = new int[3];

	// save the prices for the first house
	for(int i = 0; i < 3; i++)
		solution[0][i] = rgbArr[0][i];

	// solute subproblems
	for (int i = 1; i < N; i++)
	{
		for (int f = 0; f < 3; f++)
		{
			solution[i][f] = min(solution[i - 1][(f+1) % 3] + rgbArr[i][f],
				solution[i - 1][(f + 2) % 3] + rgbArr[i][f]);
		}
	}

	// optimal solution
	int optimalSolution = min(solution[N - 1][0], solution[N - 1][1]);
	optimalSolution = min(optimalSolution, solution[N - 1][2]);
	cout << optimalSolution;

	for (int i = 0; i < N; i++)
		delete[] rgbArr[i];
	delete[] rgbArr;
	for (int i = 0; i < N; i++)
		delete[] solution[i];
	delete[] solution;
}