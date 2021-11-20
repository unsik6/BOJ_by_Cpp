// 백준 1011번 Fly me to the Alpha Centauri

// Input: T = 테스트 케이스, 0 <= x = 출발좌표 < y = 도착 좌표 < 2^31
// condition: 첫 이동과 마지막 이동은 1이다.
//			  i번째에 k만큼 이동했다면 i+1번째 이동은 k-1, k, k+1 만큼만 이동할 수 있다.

// 두번째 풀이
// 풀이 자체는 두번째 풀이 참조
// 시간초과의 원인: length의 최대가 2^31이므로 n++로 n 찾는데 오래걸림
// 연산 시 int 오버플로우 발생 => long long

// 그냥 출력할 때, 나중에 넣으려고 개행 안 넣었는데 그거 때매 틀렸습니다 양산

#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	long long T;
	cin >> T;
	long long* arrX = new long long[T];
	long long* arrY = new long long[T];
	for (int t = 0; t < T; t++) cin >> arrX[t] >> arrY[t];
	for (int t = 0; t < T; t++)
	{
		long long length = arrY[t] - arrX[t];
		long long n{ 1 };
		while (n * n <= length) n++;
		n--;

		if (length == n * n) cout << 2 * n - 1 << endl;
		else
		{
			length -= n * n;
			cout << 2 * n - 1 + (length <= n ? 1 : 2) << endl;
		}
		
		// 올림 활용 예제
		/*length = ceil((double)(length - n * n) / n);
		cout << 2 * n - 1 + length << endl;*/

		// 범위 직접 구현 예제
		/*if (length == n * n) cout << n + n - 1 << endl;
		else if (n * n < length && length <= n + n * n) cout << n + n << endl;
		else if (length > n * n + n && length < (n + 1) * (n + 1)) cout << n + n + 1 << endl;*/
	}
}



// 첫번째 풀이: 시간 초과

// 2^31보다 작으므로 int 범위 내에 있다.
// 가장 최적화된 경로는 1로 시작해서 1로 끝나는 피라미드형으로 올라가는 것이다.
// 왜냐하면 최소한으로 이동해야 하기 때문에 한번에 최대한 많이 이동해야 하기 때문이다.
// length = y - x
// 만약 정확하게 피라미드형으로 이동할 경우, length는
// length = n(n+1)/2 + n(n-1)/2 (n은 한번에 가장 멀리 이동한 거리)
//		  = n^2
// 그러므로 먼저 length를 넘지 않는 최대의 n을 찾는다.
// 이후에는 설탕 배달(Q2839) 문제와 비슷하다. 다만, 최대 범위가 계속 바뀐다.
// length - n^2이 남은 범위라고 했을 때, 남은 범위를 (n-2), (n-1), n 크기의 주머니에 담는 것이다.
// 이때 가장 최대한 적은 수의 주머니로 담는 것이다.
// 만약 (n-2), (n-1), n의 주머니로 딱 나누어 떨어질 수 없다면, n--를 하고
// 다시 (n-2), (n-1), n의 범위에서 주머니로 나눈다.
// 만약 n = 4일 때, length - n^2 = 10이라면 4, 4, 2으로 나눌 수 있다.
// 다만, 이럴 경우 이동 거리가 [1, 2, 3, 4, 4, 2. 3. 2. 1]가 된다.
// 이럴 경우, [4, 2] 사이의 교환이 불가능해지지만 3, 3으로 치환이 가능하므로 상관없다.
// 주머니 중에 n 크기의 주머니와 n-2의 주머니가 있다면, n-1의 주머니가 반드시 1개 이상 있어야 하지만
// 자동으로 치환되니 무시해도 된다.

//#include<iostream>
//using namespace std;
//
//int main()
//{
//	// input
//	int T;
//	cin >> T;
//	int* arrX = new int[T];
//	int* arrY = new int[T];
//	for (int t = 0; t < T; t++) cin >> arrX[t] >> arrY[t];
//
//	// Test repitition
//	for (int t = 0; t < T; t++)
//	{
//		int length = arrY[t] - arrX[t];
//		if (length < 4)
//		{
//			cout << length << endl;
//			continue;
//		}
//		// find maximum distance
//		int n = 1;	// n >= 1
//		int nCnt = 0;
//		int n_1Cnt = 0;
//		int n_2Cnt = 0;
//		while (n * n <= length) n++;
//		n--;
//		if (length == n * n)
//		{
//			cout << 2 * n - 1;
//			continue;
//		}
//		int rest = 0;
//		while (n > 1)
//		{
//			rest = length - n * (n - 1);
//			nCnt = rest / n;
//			while (nCnt >= 0)
//			{
//				rest -= n * nCnt;
//				n_1Cnt = rest / (n - 1);
//				rest -= (n - 1) * n_1Cnt;
//				if (n > 2)
//				{
//					while (n_1Cnt >= 0)
//					{
//						n_2Cnt = rest / (n - 2);
//						rest -= (n - 2) * n_2Cnt;
//						if (rest == 0) break;
//						else
//						{
//							n_1Cnt--;
//							rest = length - n * (n - 1);
//							rest -= n * nCnt;
//							rest -= (n - 1) * n_1Cnt;
//						}
//					}
//				}
//				if (rest == 0) break;
//				else
//				{
//					nCnt--;
//					rest = length - n * (n - 1);	// rest 초기화
//				}
//			}
//			if (rest == 0) break;
//			else n--;
//		}
//		cout <<  2 * (n - 1) + nCnt + n_1Cnt + n_2Cnt << endl << endl;
//	}
//}

// 두번째 풀이 : 시간 초과
// 2^31보다 작으므로 int 범위 내에 있다.
// 최소한으로 이동해야 하기 때문에 한번에 최대한 많이 이동해야 하기 때문에
// 한번에 가장 멀리 이동한 길이가 n일 때
// 가장 짧은 경로는 1로 시작해서 1로 끝나는 피라미드형으로 올라가는 것이다.

// length = y - x
// 만약 정확하게 피라미드형으로 이동할 경우, length는
// length = n(n+1)/2 + n(n-1)/2 (n은 한번에 가장 멀리 이동한 거리)
//		  = n^2
// length = n^2를 만족할 때, [1, 2, 3, 2, 1]의 형태이므로
// 이동한 횟수 = n + (n - 1) = 2n -1이 된다.
// 즉, len(1) = 1, len(4) = 3, len(9) = 5, len(16) = 7 ...의 길이가 된다.

// n^2의 길이의 가장 최적화 경로에서 (n+1)^2의 길이의 가장 최적화 경로로
// 길이가 증가할 때는 다음과 같은 규칙이 성립된다.
// n^2의 길이에서는 [1, 2, ... , n-1 , n, n-1, n-2, ... , 2, 1]의 형태가 가장 최적화 형태이므로
// n^2에서 (n+1)^2로 길이가 증가하는 중이라면
// 중간의 이동거리에 +1될 경우, 연결이 끊기기 때문에 반드시 횟수가 증가하게 된다.

// 각 이동은 처음 1에서 n까지의 증가 구간과 종결 1까지의 감소 구간으로 구분할 수 있는데
// (n+1)^2길이의 최적화 경로의 직전 이동 패턴은 [1, 2, ... , n-1, n, n, n, n-1, n-2, ... ,2, 1]이다.
// 그리고 최적화된 (n+1)^2의 패턴은 가운데 n이 n+1이 되는 것이다.

// 결국 n^2의 길이에서의 가장 최적화된 경로에서 (n+1)^2의 길에서의 가장 최적화된 경로로 가는 것은
// 길이가 1 증가할 때마다, 감소구간에서 마지막 1을 제외한 구간에 1을 더해주는 것이다.
// 즉, 최적화된 n^2의 패턴에서 길이가 1 늘어나면 반드시 이동횟수가 1 늘어나고,
// 이후 뒤에서 두번째 1부터  n-1까지 뒤에서부터
// 1을 더해주면 가운데 n이 2개가 생기는 최적화 경로가 나타난다.

// 가운데 n이 2개가 생기는 최적화 경로는 이동횟수가 (n^2최적화 이동횟수)+1이다.
// 즉 이동횟수가 (n^2최적화 이동횟수)+1인 경로는
// 처음에 맨 뒤에 1추가
// 그 이후로 1 ~ n - 1까지 뒤에서부터 1씩 더해주므로
// 1 + n - 1 - 1 + 1 = n번 존재한다.
// 마찬가지로 (n+1)^2의 최적화 경로 직전까지는 가운데 n이 3개 필요하므로 같은 방식을 한번 더한다.

// 그러므로
// len(n^2) = 2n -1
// len(n^2 + 1 ~ n^2 + n) = 2n
// len(n^2 + n + 1 ~ n^2 + 2n) = 2n + 1
// len((n+1)^2) = 2n + 1
// 이런 식으로 진행된다.
// 결국 n^2의 형태마다 홀수의 길이로 정해진다.

//#include<iostream>
//using namespace std;
//
//int main()
//{
//	int T;
//	cin >> T;
//	int* arrX = new int[T];
//	int* arrY = new int[T];
//	for (int t = 0; t < T; t++) cin >> arrX[t] >> arrY[t];
//	for (int t = 0; t < T; t++)
//	{
//		// 먼저 길이를 구한다.
//		int length = arrY[t] - arrX[t];
//
//		// 길이보다 작으면서 가장 큰 n^2를 갖는 n을 찾는다.
//		int n = 1;	// length가 1일 때, n은 1이므로 n은 1보다 작을 수 없다.
//		while (n * n <= length) n++;
//		n--;
//
//		// length가 n^2 형태일 경우
//		if (n * n == length) cout << 2 * n - 1;
//		// 아니라면 n^2와 (n+1)^2 사이의 2개의 구간 중에서 어떤 구간인지 찾는다.
//		else
//		{
//			length -= n * n;
//			if (length <= n) cout << 2 * n;
//			else cout << 2 * n + 1;
//		}
//	}
//}