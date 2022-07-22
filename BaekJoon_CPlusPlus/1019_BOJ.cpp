// 백준 1019번 책 페이지

// 도저히 안 되겠다.
// 추후 복습 필요.
// 8시간 동안 고쳤지만 안 됨.

//https://sangdo913.tistory.com/119
//#pragma once
//#include<cstdio>
//#include <iostream>
//using namespace std;
//
//long long pow(int cnt) {
//    if (cnt < 0) return 0;
//
//    if (cnt == 0) {
//        return 1;
//    }
//
//    long long half = pow(cnt / 2);
//    half *= half;
//    if (cnt & 1) half *= 10;
//    return half;
//}
//
//long long cnt[10];
//
//int getDigit(long long n) {
//    int res = 0;
//    while (n) {
//        res++;
//        n /= 10;
//    }
//    return res - 1;
//}
//int main() {
//    long  long n;
//    cin >> n;
//
//    int digit = getDigit(n);
//    long long p = pow(digit);
//
//    for (int i = 0; i < digit; i++) {
//        cnt[0] -= (digit - i) * (pow(i + 1) - pow(i));
//    }
//
//    cnt[0] -= digit;
//
//    for (int i = digit; i > 0; i--) {
//        int fr = n / p;
//
//        for (int i = 0; i < fr; i++) {
//            cnt[i] += p;
//        }
//
//        for (int i = 0; i < 10; i++) cnt[i] += fr * digit * pow(digit - 1);
//
//        n %= p;
//
//        cnt[fr] += n + 1;
//        digit--;
//        p /= 10;
//    }
//
//    for (int i = 1; i <= n; i++) {
//        cnt[i]++;
//    }
//    for (int i = 0; i < 10; i++) {
//        printf("%d ", cnt[i]);
//    }
//    return 0;
//}


#include <iostream>
#include <cmath>
using namespace std;

int N;
unsigned long long ea[10] = { 0 };
int GetMaxDigit(int);
int main()
{
	cin >> N;
	int digit = GetMaxDigit(N);
	int p = pow(10, digit);
	for (int i = 0; i < digit; i++) ea[0] -= (digit - i) * (pow(10, i + 1) - pow(10, i));
	ea[0] -= digit;
	for (int i = digit; i > 0; i--)
	{
		int now = N / p;
		for (int f = 0; f < now; f++) ea[f] += p;
		for (int k = 0; k < 10; k++) ea[k] += now * digit * (int)pow(10, digit - 1);
		N %= p;
		ea[now] += N + 1;
		digit--;
		p /= 10;
	}
	for (int t = 1; t <= N; t++) ea[t]++;
	for (int c = 0; c < 10; c++) cout << ea[c] << " ";
}

int GetMaxDigit(int n)
{
	int result = 0;
	while (n)
	{
		n /= 10;
		result++;
	}
	return result-1;
}