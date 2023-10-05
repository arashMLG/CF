#include<bits/stdc++.h>
#ifdef LOCAL
#include "Essentials/algo/debug.h"
#else
#define debug(...) 69
#endif
using namespace std;

//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

//https://quera.org/profile/4dykhk

typedef long long     ll;
typedef long double   ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll>   pll;

const int N = 1e3 + 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const ll inf = 1e18;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define F           first
#define S           second
#define pb          push_back
#define ms(x,y)     memset((x) , (y) , sizeof (x))
#define done        return cout<<endl , 0;
#define kill(x)     cout<<x<<endl, exit(0);
#define isIn(x,s,e) ((x) >= (s) && (x) <= e)
#define all(x)      x.begin(),x.end()
#define sz(x)       (int)x.size()
#define pc(x)       __builtin_popcount(x)
#define ctz(x)      __builtin_ctz(x)
#define MinHeap(x)  priority_queue<x, vector<x> , greater<x> >
#define MaxHeap(x)  priority_queue<x, vector<x>>
#define lc          (v << 1)
#define rc          ((v<<1) |1)
//#define int      ll

ll pw(ll a, ll b, ll md = mod){ll res = 1; while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

int n,m;
int a[N];
ldb dp[N][N];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i =1 ; i<= n ; i++) cin>>a[i];
	for(int i = 1; i<= n ; i++) for(int j = 1; j <= n ; j++) {
		dp[i][j] = a[i] > a[j];
	}
	while(m--) {
		int x,y; cin>>x>>y;
		for(int i = 1; i<= n ;i ++) if(i != x && i != y){
			dp[x][i] = dp[y][i] = (dp[x][i] + dp[y][i]) / 2.0;
			dp[i][x] = dp[i][y] = (dp[i][x] + dp[i][y]) / 2.0;
		}
		dp[x][y] = dp[y][x] = 0.5;
	}
	ldb ans =0;
	for(int i = 1; i<= n ; i++) for(int j = i+1; j<= n ;j ++) ans += dp[i][j];
	cout<< fixed<< setprecision(10) << ans;
    done;
}

