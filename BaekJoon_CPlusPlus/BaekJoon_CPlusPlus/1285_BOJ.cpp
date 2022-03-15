// 백준 1258번 동전 뒤집기

// input: 행렬의 한 변의 길이 N (1 <= N <= 20, 자연수)
//		  각 행의 동전의 상태 (H = 앞면, T = 뒷면)

// condition: 가능한 행위: 1개의 행 또는 열에 있는 모든 동전들을 뒤집는다.

// output: 최소한의 뒷면만 보이도록 했을 때, 최소한의 뒷면 동전의 수

// 1x1, 2x2, 3x3 순으로 서브 프러블럼이 존재한다.
// 예를 들어 (0,0), (0..1, 0..1) 이런 식이다.
// 다만, 기존의 문제가 영향을 받지 않게 하기 위해서, i번째 행과 열만 뒤집는다.
// 이때 경우의 수는 4가지이다.
//  (1) 안 뒤집는다.
//  (2) 행만 뒤집는다.
//  (3) 열만 뒤집는다.
//  (4) 행과 열 모두 뒤집는다.
// 이중 최소의 동전의 개수를 갖는 경우를 선택한다.

// 중요한 점은 (i, i)이다.
// 행을 먼저 뒤집냐, 열을 먼저 뒤집냐에 따라
// 그 다음 행위에 대한 연산이 달라질 수 있다.

#include <iostream>
using namespace std;


int GetNumOfBackWithSwitchingLines(bool** _mat, int _N, int _lineNum, bool _switchRow, bool _switchCol)
{
	int numOfBack = 0;
	if (_switchRow)
	{
		for (int f = 0; f < _N; f++)
			_mat[_lineNum][f] = !_mat[_lineNum][f];
	}
	if (_switchCol)
	{
		for (int i = 0; i < _N; i++)
			_mat[i][_lineNum] = !_mat[i][_lineNum];
	}

	for (int i = 0; i < _lineNum; i++)
	{
		if (!_mat[_lineNum][i]) numOfBack++;
		if (!_mat[i][_lineNum]) numOfBack++;
	}
	if (!_mat[_lineNum][_lineNum]) numOfBack++;

	return numOfBack;
}

int main()
{
	int N;
	cin >> N;
	
	// true = front, false = back
	bool** originMat = new bool*[N];
	for (int i = 0; i < N; i++)
	{
		originMat[i] = new bool[N];
		string inputRow;
		cin >> inputRow;
		for (int f = 0; f < N; f++)
			originMat[i][f] = (inputRow[f] == 'H');
	}

	int numOfBack = 0;
	for (int i = 0; i < N; i++)
	{
		
	}






	for (int i = 0; i < N; i++)
	{
		delete[] originMat[i];
	}
	delete[] originMat;
}
