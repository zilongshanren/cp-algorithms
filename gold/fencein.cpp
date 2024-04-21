#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int A, B, N, M;
    cin >> A >> B >> N >> M;

    vector<int> VA(N + 1), HA(M + 1);
    for (int i = 0; i < N; i++) {
        cin >> VA[i];
    }
    for (int j = 0; j < M; j++) {
        cin >> HA[j];
    }

    //排序，计算垂直方向的fence 长度
    sort(VA.begin(), VA.end());
    for (int i = 0; i < N; i++) {
        VA[i] = VA[i + 1] - VA[i];
    }
    VA[N] = A - VA[N];


    //排序，计算水平方向的 fence 长度
    sort(HA.begin(), HA.end());
    for (int i = 0; i < M; i++) {
        HA[i] = HA[i + 1] - HA[i];
    }
    HA[M] = B - HA[M];

    //把fence 长度排序，类似krustal 算法
    sort(VA.begin(), VA.end());
    sort(HA.begin(), HA.end());
    N++; M++;

    //移除水平和垂直方向上的最小的两列
    long long result = 1ll * VA[0] * (M - 1) +
        1ll * HA[0] * (N - 1);
    for (int vi = 1, hi = 1; vi < N && hi < M; ) {
        //先把水平方向的移除完
        if (VA[vi] < HA[hi]) {
            //水平方向的index + 1
            result += VA[vi++] * (M - hi);
        } else {
            //继续移除垂直方向上fence, 随着水平和垂直方向的fence 的移除，要拆除的数量相应地减少
            result += HA[hi++] * (N - vi);
        }
    }
    cout << result << endl;

    return 0;
}
