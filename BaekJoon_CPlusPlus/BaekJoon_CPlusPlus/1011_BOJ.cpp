// 백준 1011번 Fly me to the Alpha Centauri

// Input: T = 테스트 케이스, 0 <= x = 출발좌표 < y = 도착 좌표 < 2^31
// condition: 첫 이동과 마지막 이동은 1이다.
//			  i번째에 k만큼 이동했다면 i+1번째 이동은 k-1, k, k+1 만큼만 이동할 수 있다.

// 첫번째 시도: 시간 초과

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