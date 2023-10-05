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

const int N = 2e5 + 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 30;
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

int n,m,s;
vector<pll> G[N];
vector<int> D[N],dom[N];
vector<int> Din[N];
int dist[N];
vector<pair<pll,int>> edges;
MinHeap(pll) pq;
vector<int> topol;
int up[N][LOG];
int sum[N];
bool mark[N];
int h[N];
int ans=0;

void dijk() {
	fill(dist,dist+N,inf);
	dist[s] = 0;
	pq.push({0,s});
	while(sz(pq)) {
		int v = pq.top().S; pq.pop();
		if(mark[v]) continue;
		mark[v] = true;
		for(auto [u,w] : G[v]) if(!mark[u]){
			dist[u] = min(dist[u],dist[v] + w);
			pq.push({dist[u],u});
		}
	}
}

void dtopols(int v) {
	mark[v] = true;
	for(int u : D[v]) if(!mark[u]) dtopols(u);
	topol.pb(v);
}

void dfs(int v) {
	sum[v] = 1;
	for(int u : dom[v]) dfs(u),sum[v] += sum[u];
	if(v != s) ans = max(ans,sum[v]);	
	debug(v,dom[v],sum[v]);
}

int f(int v,int k) {
	for(int i = 0 ; i < LOG; i ++)
		if((k >> i)&1)
			v= up[v][i];
	return v;
}

int lca(int v,int u) {
	if(h[v] > h[u]) swap(v,u);
	u = f(u,h[u] - h[v]);
	if(v == u) return v;
	for(int i = LOG-1; i>= 0; i--)
		if(up[v][i] != up[u][i])
			v= up[v][i],u=up[u][i];
	return up[v][0];
}

void update(int v){ 
	for(int i = 1; i < LOG; i ++) {
		up[v][i] = up[up[v][i-1]][i-1];
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m>>s;
	for(int i = 0 ;i < m ; i++) {
		int v,u,w; cin>>v>>u>>w;
		G[v].pb({u,w});
		G[u].pb({v,w});
		edges.pb({{v,u},w});
	}
	dijk();
	ms(mark,0);
	for(auto [e,w] : edges) {
		auto [v,u] = e;
		if(dist[v] >= inf || dist[u] >= inf) continue;
		if(dist[v] > dist[u]) swap(v,u);
		if(dist[v] + w == dist[u]) D[v].pb(u),Din[u].pb(v);
	}
	for(int i = 1; i <= n ;i ++) {
		if(dist[i] < inf && !mark[i]) dtopols(i);
	}
	reverse(all(topol));
	up[s][0] = s;
	update(s);
	for(int i = 1; i< sz(topol); i ++) {
		int v = topol[i];
		int l = Din[v][0];
		for(int j = 1; j< sz(Din[v]) ; j ++) l = lca(l,Din[v][j]);
		up[v][0] = l;
		h[v] = h[l] +1;
		dom[l].pb(v);
		update(v);
	}
	dfs(s);
	cout<<ans << '\n';
    done;
}

