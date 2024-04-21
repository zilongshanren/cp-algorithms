/*
 * Same solution as tmwilliamlin:
 *
 * - Use dijkstra to calculate distances from s, u, and v.
 * - Consider the dijkstra tree from s to t. Note that this is a DAG.
 * - We basically need to choose one path on this DAG, choose a starting node for u, and a exiting node for v.
 * - We define dpForward(i) = min cost from any node from i forwards through the DAG to t, for v to get to that node.
 * - Define dpBackward(i) i min cost for v to get to a node x, where x is along the path from s to i in the DAG.
 * - Loop through all nodes i on the DAG. One answer candidate is (distance from u to node i) + min(dpForward(i), dpBackward(i))
 *
 * - Alternatively the answer could just be from u directly to v
 */

//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000LL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define PI acos(-1.0)
// #define MOD (int)(2e+9+11)
#define MOD (int)(1e+9+7)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;

#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize
#define SORT(vec) sort(all(vec))
#define RSORT(vec) sort(vec.rbegin(),vec.rend())

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

// @formatter:off
// Source: Benq (https://github.com/bqi343/USACO) [Modified]
namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);
    template<class T> void reA(T A[], int sz);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) {
        re(first); re(rest...);
    }

    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.pA,p.pB); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
    template<class T> void reA(T A[], int sz) { F0R(i, sz) re(A[i]); }

    void setupIO(const string &PROB = "") {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        if (PROB.length() != 0) {
            ifstream infile(PROB + ".in");
            if (infile.good()) {
                freopen((PROB + ".in").c_str(), "r", stdin);
                freopen((PROB + ".out").c_str(), "w", stdout);
            }
        }
    }
}
using namespace input;

namespace output {
    template<class T1, class T2> void prD(const pair<T1,T2>& x);
    template<class T, size_t SZ> void prD(const array<T,SZ>& x);
    template<class T> void prD(const vector<T>& x);
    template<class T> void prD(const set<T>& x);
    template<class T1, class T2> void prD(const map<T1,T2>& x);

    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void prD(const T& x) { cout << x; cout.flush(); }
    template<class Arg, class... Args> void prD(const Arg& first, const Args&... rest) {
        prD(first); prD(rest...);
    }

    template<class T1, class T2> void prD(const pair<T1,T2>& x) {
        prD("{",x.pA,", ",x.pB,"}");
    }
    template<class T> void prDContain(const T& x) {
        prD("{");
        bool fst = 1; for (const auto& a: x) prD(!fst?", ":"",a), fst = 0; // const needed for vector<bool>
        prD("}");
    }
    template<class T, size_t SZ> void prD(const array<T,SZ>& x) { prDContain(x); }
    template<class T> void prD(const vector<T>& x) { prDContain(x); }
    template<class T> void prD(const set<T>& x) { prDContain(x); }
    template<class T1, class T2> void prD(const map<T1,T2>& x) { prDContain(x); }

    void psD() { prD("\n"); }
    template<class Arg> void psD(const Arg& first) {
        prD(first); psD(); // no space at end of line
    }
    template<class Arg, class... Args> void psD(const Arg& first, const Args&... rest) {
        prD(first," "); psD(rest...); // print w/ spaces
    }


    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
        pr(first); pr(rest...);
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
        pr(x.pA, " ", x.pB);
    }
    template<class T> void prContain(const T& x) {
        bool fst = 1; for (const auto& a: x) pr(!fst?" ":"",a), fst = 0; // const needed for vector<bool>
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

    void ps() { pr("\n"); }
    template<class Arg> void ps(const Arg& first) {
        pr(first); ps(); // no space at end of line
    }
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
        pr(first," "); ps(rest...); // print w/ spaces
    }
}
using namespace output;
// @formatter:on

/* ============================ */

#define MAXN 100000

int n, m, s, t, u, v;
vii adj[MAXN];
ll distS[MAXN];
ll distU[MAXN];
ll distV[MAXN];
vi parent[MAXN];
vi dpChildren[MAXN];
bool reachable[MAXN];

void dijkstra(ll dist[MAXN], int source) {
    SET(dist, LL_INF, MAXN);
    dist[source] = 0;

    min_heap<ii> pq; pq.push({0, source});
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();
        trav(v, adj[u.pB]) {
            if (dist[v.pA] > dist[u.pB] + v.pB) {
                dist[v.pA] = dist[u.pB] + v.pB;
                pq.push({dist[v.pA], v.pA});
            }
        }
    }
}

void dijkstraParent(ll dist[MAXN], int source) {
    SET(dist, LL_INF, MAXN);
    dist[source] = 0;

    min_heap<ii> pq; pq.push({0, source});
    while (!pq.empty()) {
        ii u = pq.top(); pq.pop();
        trav(v, adj[u.pB]) {
            if (dist[v.pA] > dist[u.pB] + v.pB) {
                dist[v.pA] = dist[u.pB] + v.pB;
                parent[v.pA].clear(); parent[v.pA].pb(u.pB);
                pq.push({dist[v.pA], v.pA});
            } else if (dist[v.pA] == dist[u.pB] + v.pB) {
                parent[v.pA].pb(u.pB);
            }
        }
    }
}

ll memo[MAXN];
ll dp(int u) {
    if (memo[u] != -1) return memo[u];
    ll best = distV[u];
    trav(v, dpChildren[u]) {
        MIN(best, dp(v));
    }
    return memo[u] = best;
}
ll memo2[MAXN];
ll dpBack(int u) {
    if (memo2[u] != -1) return memo2[u];
    ll best = distV[u];
    trav(v, parent[u]) {
        MIN(best, dpBack(v));
    }
    return memo2[u] = best;
}

int main() {
    setupIO();

    cin >> n >> m >> s >> t >> u >> v;
    --s; --t; --u; --v;
    F0R(i, m) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }

    dijkstra(distU, u);
    dijkstra(distV, v);
    dijkstraParent(distS, s);

    SET(memo, -1, MAXN);
    SET(memo2, -1, MAXN);
    SET(reachable, false, MAXN);
    queue<int> q; q.push(t);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (!reachable[u]) {
            reachable[u] = true;
            trav(v, parent[u]) {
                dpChildren[v].pb(u);
                q.push(v);
            }
        }
    }
    ll ans = distU[v];
    F0R(i, n) {
        if (reachable[i]) {
            MIN(ans, distU[i] + min(dp(i), dpBack(i)));
        }
    }
    cout << ans << "\n";

    return 0;
}
