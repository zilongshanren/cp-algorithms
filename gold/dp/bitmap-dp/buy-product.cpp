#include<bits/stdc++.h>

using namespace std;

const int K = 3;
const int N = 8;


int main(int argc, char *argv[])
{
    int total[1<<K][N] = {{0}};

    for (int i = 1; i < (1<<K); ++i) {
        for (int j = 0; j < N; ++j) {
            total[i][j] = 10000;
        }
    }

    int price[K][N] = {
        {6,9,5,4,8,9,1,6},
        {8,4,6,4,7,5,7,4},
        {5,3,9,7,3,5,1,4}
    };

    for (int x = 0; x < K; ++x) {
        total[1<<x][0] = price[x][0];
    }

    int n = N;
    int k = K;
    for(int d = 1; d < n; d++) {
        for(int s = 0; s < (1<<k); s++) {
            total[s][d] = total[s][d-1];
            for(int x = 0; x < k; x++) {
                if(s&(1<<x)) {
                    total[s][d] = min(total[s][d], total[s^(1<<x)][d-1]+price[x][d]);
                }
            }
        }
    }
    for (int i = 0; i < (1<<K); ++i) {
        for (int j = 0; j < N; ++j) {
            cout<<total[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    //111
    cout<<"ans = "<<total[(1<<k)-1][n-1]<<endl;


    return 0;
}
