#include<bits/stdc++.h>
#ifdef LOCAL
#include "Essentials/algo/debug.h"
#else
#define debug(...) 69
#endif
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

//https://quera.org/profile/4dykhk

typedef long long     ll;
typedef long double   ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll>   pll;

const int N = 1e5 + 23;
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

vector<int> G[N];
bool mark[N];
int c=0;

void dfs(int v) {mark[v] = true; c++; for(int u : G[v]) if(!mark[u]) dfs(u);}

bool check(int x) {
	while(x) {
		int v= x%10;
		if(v != 4 &&v != 7) return false;
		x /= 10;
	}
	return true;
}

int n,m;
int cnt[N];
vector<pii> a;
int dp[2][N];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i = 0 ; i < m ;i ++) {
		int v,u; cin>>v>>u;
		G[v].pb(u);
		G[u].pb(v);
	}
	for(int i = 1; i <= n ; i++) {
		if(!mark[i]) {
			c= 0;
			dfs(i);
			cnt[c] ++;	
		} 
	}
	
	for(int i = 1;i <= n ; i++) {
		int x = 1;
		while(cnt[i]) {
			int tmp = min(cnt[i],x);
			a.pb({tmp*i, tmp});
			cnt[i] -= tmp;
			x*= 2;
		}
	}
	debug(a);
	fill(dp[0],dp[0] + N,N+69);
	dp[0][0] = 0;
	dp[0][a[0].F] = a[0].S;
	for(int i = 1; i < sz(a) ; i++) {
		auto [val,cost] = a[i];
		bool now = i&1;
		for(int j =0 ; j < N ;j ++) {
			dp[now][j] = dp[now^1][j];
			if(val <= j) {
				dp[now][j] = min(dp[now][j], dp[now^1][j-val] + cost);
			}
		}
	}
	int ans = N+69;
	bool sex = (sz(a)-1)&1;
	for(int i = 1 ; i< N; i ++) {
		if(check(i)) 
			ans = min(ans,dp[sex][i]);
	}
	cout<< (ans >= N ? -1 : ans-1) <<'\n';
    done;
}

