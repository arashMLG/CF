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

const int N = 1e5 + 5;
const int K = 100 + 5;
const int sq = 450;
const ll mod =998244353; // 998244353
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
#define int      ll

ll pw(ll a, ll b, ll md = mod){ll res = 1; while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

void ok(int &a) {
	if(a < 0) a += 2 *mod;
	a %= mod;
}

int n,k,len;
int a[N];
int dp[N][K],sum[N][K],mx[K];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>k>>len;
	for(int i = 1; i <= n ; i++) cin>>a[i];
	for(int i = 1; i<= n ; i++) {
		if(a[i] > 0) {
			for(int j = 1; j <= k; j ++) if(j != a[i]) mx[j] = i;
		}
		int s = 0;
		for(int j = 1; j <= k; j ++) {
			//debug(i,a[i],j);
			if(a[i] > 0 && j != a[i]) continue;
			int sex = max({mx[j]-1,i-len,0LL});
			//debug(i,j,sex);
			ok(dp[i][j] = sum[i-1][j] - sum[sex][j] + (max(mx[j]-1,i-len) < 0));
			ok(s += dp[i][j]);
			debug(i,j,dp[i][j]);
		}
		for(int j = 1; j <= k; j ++) {
			ok(sum[i][j] = sum[i-1][j] + s-dp[i][j]);
		}
	}
	debug(sum[1][2]);
	int ans=0;
	for(int i = 1; i <= k ; i++) ok(ans += dp[n][i]);
	cout<<ans;
    done;
}

