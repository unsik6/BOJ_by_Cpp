// 백준 1026번 보물

// input: 배열 A, B의 길이 N(자연수) (1<= N <=50)
//		  배열 A의 요소, 배열 B의 요소 (0 <= x <= 100)

// condition: S = A[0]*B[0] + ... + A[N-1]*B[N-1]의 최솟값 출력
//			  A의 요소들의 위치는 재배열할 수 있으나 B는 할 수 없다.
//			  B의 값이 작을수록 A의 값이 커야 가장 작은 값이 나온다.


#include<iostream>
#include<algorithm>
using namespace std;

bool decreasingOrder(int _a, int _b)
{
	return _a > _b;
}

int main()
{
	int N;
	cin >> N;
	int* A = new int[N];
	int* B = new int[N];
	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < N; i++) cin >> B[i];
	sort(A, A + N);
	sort(B, B + N, decreasingOrder);
	
	int s = 0;
	for (int i = 0; i < N; i++)
		s += A[i] * B[i];
	cout << s;

	delete[] A;
	delete[] B;
	return 0;
}