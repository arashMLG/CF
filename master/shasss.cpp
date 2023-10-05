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

const int N = 5e3 + 23;
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
#define int      ll

ll pw(ll a, ll b, ll md = mod){ll res = 1; while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

int n;
vector<pll> G[N];
ll dp[N][2];
int s[N];
ll fuck[N];

void dfs1(int v,int p = -1) {
	s[v] = 1;
	dp[v][0] = 0;
	for(auto [u,w] : G[v]) if(u != p){
		dfs1(u,v);
		//debug(s[u],w);
		dp[v][0] += 1LL * s[u] * w + dp[u][0];
		s[v] += s[u];
	}
}

int sex;
int V,U;
ll ans[2];
bool me;

void dfs2(int v,int p=-1,int wp = 0) {
	if(p != -1 && v != V && v != U) {
		dp[v][1] = 1LL*(sex-s[v])*wp + 1LL*dp[p][1] + (dp[p][0] - s[v] * wp*1LL - dp[v][0]);
	} else {
		dp[v][1] = 0LL;
	}
	fuck[v] = dp[v][0] + dp[v][1];
	ans[me] = min(ans[me], fuck[v]);
	for(auto [u,w] : G[v]) if(u != p) {
		dfs2(u,v,w);
	}
}

vector<pll> edges;

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i = 1 ; i< n ; i ++) {
		int v,u,w; cin>>v>>u>>w;
		G[v].pb({u,w});
		G[u].pb({v,w});
		edges.pb({v,u});
	}
	dfs1(1);
	sex= n;
	dfs2(1);
	ll sum = 0;
	for(int i = 1; i <= n ; i++) sum += fuck[i];
	sum /= 2;
	debug(sum);
	ll javab = sum;
	for(auto [v,u] : edges) {
		dfs1(v,u);
		dfs1(u,v);
		sex = s[v];
		ans[0] = inf;
		me= 0;
		V = v,U=u;
		dfs2(v,u);
		sex = s[u];
		ans[1] = inf;
		me =1;
		dfs2(u,v);
		int one= s[v],two = s[u];
		
		javab = min(javab, sum- s[v] *fuck[u] - s[u]*fuck[v] + ans[0] * s[u] + ans[1] * s[v] );
		debug(javab,u,v);
	}
	cout<<javab;
    done;
}

