
#include<bits/stdc++.h>

using namespace std;


const int N = 6;
pair<int,int> best[1<<N];

int main(int argc, char *argv[])
{
    int n = N;
    int weight[N] = {2,3,3,5,6,1};

    //totoal weight
    int x = 10;

    best[0] = {1, 0};

    for (int s = 1; s < (1<<n); s++) {
        // initial value: n+1 rides are needed
        best[s] = {n+1,0};
        for (int p = 0; p < n; p++) {
            if (s&(1<<p)) {
                auto option = best[s^(1<<p)];
                if (option.second+weight[p] <= x) {
                    // add p to an existing ride
                    option.second += weight[p];
                } else {
                    // reserve a new ride for p
                    option.first++;
                    option.second = weight[p];
                }
                best[s] = min(best[s], option);
            }
        }
    }
    cout<<"ans = "<<best[(1<<N)-1].first<<endl;
    return 0;
}
