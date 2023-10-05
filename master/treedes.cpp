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

int n;
vector<int> G[N];
int d[2][N];
int V,U;
int deg[N];
vector<int> Q;
bool mark[N];
int par[N];
bool sex[N];

void dfs(int v,int id,int p = -1) {
	par[v] = p;
	if(p == -1) d[id][v] = 0;
	for(int u : G[v]) if(u != p) {
		d[id][u] = d[id][v] +1;
		dfs(u,id,v);
	}
}

ll ans=0;
vector<vector<int>> javab;

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i = 1; i < n ; i++) {
		int v,u; cin>>v>>u;
		G[v].pb(u);
		G[u].pb(v);
	}
	dfs(1,0);
	V = max_element(d[0]+1,d[0] + n+1) - d[0];
	dfs(V,0);
	U = max_element(d[0]+1,d[0]+n+1) - d[0];
	dfs(U,1);
	int fuck=V;
	while(fuck != -1) {
		sex[fuck] = true;
		fuck= par[fuck];
	}
	for(int i = 1; i <= n ; i++) {
		deg[i] = sz(G[i]);
		if(!sex[i] && deg[i] == 1) {
			Q.pb(i);
		}
	}
	while(sz(Q)) {
		int v = Q.back(); Q.pop_back();
		for(int u : G[v]) {
			deg[u] --;
			if(deg[u] == 1 && !sex[u]) Q.pb(u);
		}
		
		if(d[0][v] > d[1][v]) {
			ans += d[0][v];
			javab.pb({V,v,v});
		} else {
			ans += d[1][v];
			javab.pb({U,v,v});
		}
	}
	fuck = V;
	while(fuck != U) {
		ans += d[1][fuck];
		javab.pb({U,fuck,fuck});
		fuck = par[fuck];
	}
	cout<<ans << '\n';
	for(auto vec : javab) { for(int x : vec) cout<<x << ' '; cout<<'\n';}
    done;
}

