/*백준 11726번 보석 도둑

input: 직사각형의 한 변의 길이 n (1 <= n <= 1,000)

output: 크기 1x2, 2x1의 직사각형들로 채울 수 있는 경우의 수

DP로 풀 수 있다.
긴 변의 길이를 i라고 했을 때, i번째 칸에 넣을 수 있는 경우의 수는
1) 2x1의 직사각형 1개
2) 1x2의 직사각형 2개
이다.
이때, 2번을 선택할 경우, i+1번째에서는 아무것도 넣을 수 없다.

그러므로 i번째에 선택하는 경우는 i-1에서 1번을 선택했을 때와 i-2에서 2번을 선택했을 때이므로
dp[i] = dp[i-1] + dp[i-2]이다.
1일 때와 2일 때는 각각 1, 2이므로 이는 피보나치수와 완전히 똑같다.
*/

#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;

	int* dp = new int[n];
	if (n == 1) cout << 1;
	else if (n == 2) cout << 2;
	else
	{
		// 초기값은 아래의 상황들에 해당한다.
		dp[0] = 1;
		dp[1] = 2;
		// 값이 매우 커지므로 나머지 연산의 분배법칙을 이용한다.
		for (int i = 2; i < n; i++)
			dp[i] = ((dp[i - 1] % 10007) + (dp[i - 2] % 10007)) % 10007;
		cout << dp[n - 1];
	}
	
		
	delete[] dp;
	return 0;
}