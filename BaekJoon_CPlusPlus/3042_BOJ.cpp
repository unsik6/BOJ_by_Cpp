/* 백준 3042번 트리플렛
*
* Input: 그리드의 크기 N (3 <= N <= 100)
*		 N개의 줄에 그리드의 각 행에 대한 정보 (알파벳 또는 . ) (알파벳은 중복 X)

* Output: 직선 선분 상에 알파벳이 3개 모이면 트리플렛이다. 트리플렛의 개수를 구하여라.
*
* 세 점의 종류는 중요하지 않다. 세 점에 대해 기울기가 같은지만 파악한다.
*/

#include<iostream>
#include <utility>
#include<vector>
using namespace std;

#define pos pair<double, double>

double cal(pos a, pos b) {
	return (b.second - a.second) / (b.first - a.first);
}

int main() {
	int n; cin >> n;
	vector<pos>arr;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char k; cin >> k;
			if (k != '.')
				arr.push_back({ (double)i,(double)j });
		}
	}

	int res = 0;
	int len = arr.size();
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			for (int k = j + 1; k < len; k++) {
				if (cal(arr[i], arr[j]) == cal(arr[i], arr[k])
					&& cal(arr[j], arr[k]) == cal(arr[i], arr[k]))
					res++;
			}
		}
	}
	cout << res;
	return 0;
}
