#include<iostream>
#include<algorithm>
using namespace std;

// input
int N, M;
int input_arr[100'000]{ 0 };
void input() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> input_arr[i];
    sort(input_arr, input_arr + N);
    cin >> M;
}

bool solve_query(int _target) {
    int l = 0, r = N - 1;
    while (l <= r) {
        int m = (r + l) / 2;
        if (input_arr[m] == _target)    // 중간값 = 찾는값
            return true;
        if (input_arr[m] > _target)    // 찾는값 < 중간값
            r = m - 1;
        if (input_arr[m] < _target)    //         중간값 < 찾는값
            l = m + 1;
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    for (int i = 0; i < M; i++) {
        int query = 0;
        cin >> query;
        cout << solve_query(query) << '\n';
    }
}