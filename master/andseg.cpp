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

const int N = 5e5 + 23;
const int sq = 450;
const ll mod = 998244353; // 998244353
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

int n,k,m;
vector< pair<pll,int>> seg;
int ps[N],check[N];
vector<pll> zero,one;
vector<int> G[N];
int dp[N];

void ok(int &a) {
	if(a < 0) a += 2*mod;
	a %= mod;
}

int solve(int id) {
	zero.clear(); one.clear(); for(int i = 0; i <= n; i ++) G[i].clear(),check[i] = 0,ps[i]= i,dp[i] =0;
	
	for(auto [e,x] : seg) {
		if((x >> id)&1) {
			one.pb(e);
			check[e.S] ++;
			check[e.F-1] --;
		} else {
			zero.pb(e);
			G[e.S].pb(e.F);
		}
	}
	debug(zero);
	for(int i = n-1; i >= 0 ; i--) check[i] += check[i+1];
	
	int L =-1;
	dp[0] = 1;
	ps[0] = 1;
	for(int i = 1; i <= n ; i ++) {
		if(check[i]) {
			dp[i] = 0;
		} else {
			ok(dp[i] = ps[i-1] - (L == -1 ? 0 : ps[L]));
		}
		debug(i,dp[i],L);
		ok(ps[i] = dp[i] + ps[i-1]);
		for(int u : G[i]) L = max(L,u-1);
	}
	int ans;
	ok(ans = ps[n] - (L == -1 ? 0 : ps[L]));
	debug(ans);
	return ans;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>k>>m;
	for(int i = 0 ; i < m ; i ++) {
		int l,r,x; cin>>l>>r>>x;
		seg.pb({{l,r},x});
	}
	int ans =1;
	for(int i = 0 ; i < k ; i ++) {
		ok(ans *= solve(i));
	}
	cout<<ans;
    done;
}

