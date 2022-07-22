#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<pair<int, int>> v;

    for (int i = 1; i <= N; i++) {
        int get;
        cin >> get;
        v.push_back(make_pair(i, get));
    }

    while (!v.empty()) {
        cout << v.front().first << " ";
        int num = v.front().second;
        v.erase(v.begin());

        if (v.empty()) return 0;

        if (num > 0) {
            for (int i = 0; i < num - 1; i++) {
                v.push_back(v.front());
                v.erase(v.begin());
            }
        }
        else {
            for (int i = 0; i < abs(num); i++) {
                v.insert(v.begin(), v.back());
                v.erase(v.end() - 1);
            }
        }
    }

}