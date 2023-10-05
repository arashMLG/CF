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
#define int      ll

ll pw(ll a, ll b, ll md = mod){ll res = 1; while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

int t[N<<2];
int lz[N<<2];

void shift(int v) {
	if(lz[v] == 0) return;
	t[lc] += lz[v];
	t[rc] += lz[v];
	lz[lc] += lz[v];
	lz[rc] += lz[v];
	lz[v] = 0;
}

void Upd(int l,int r,int x,int v= 1,int tl = 0, int tr = N) {
	if(l > r) return;
	
	if(l == tl && r == tr-1) {
		t[v] += x;
		lz[v] += x;
		return; 
	}
	shift(v);
	int mid=(tl+tr)/2;
	Upd(l,min(mid-1,r),x,lc,tl,mid);
	Upd(max(l,mid),r,x,rc,mid,tr);
	t[v] = min(t[lc], t[rc]);
}

int mn(int l,int r,int v=1,int tl = 0 , int tr= N) {
	if(l > r) return inf;
	
	if(l == tl && r == tr-1) return t[v];
	shift(v);
	int mid=(tl+tr)/2;
	return min( mn(l,min(mid-1,r), lc,tl,mid) , mn( max(l,mid),r,rc,mid,tr));
}

void upd(int l,int r,int x) {
	Upd(l,r,x);
}

void upd(int pos,int x) {
	Upd(pos,pos,x);
}

int n,q;
int dist[N];
int ft[N],par[N];
vector<int> G[N];
vector<pair<pll,int>> Q[N];
int ans[N],wp[N];

void dfs(int v) {
	
	for(int u : G[v]) {
		int x = wp[u];
		upd(u,ft[u],-x);
		upd(1,u-1,x);
		upd(ft[u]+1,n,x);
		dfs(u);
		upd(u,ft[u],x);
		upd(1,u-1,-x);
		upd(ft[u]+1,n,-x);
	}
	for(auto [qu,id] : Q[v]) {
		auto [l,r] = qu;
		ans[id] = mn(l,r);
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	iota(ft,ft+N,0);
	cin>>n>>q;
	for(int i = 2; i <= n; i ++) {
		int p,w; cin>>p>>w;
		G[p].pb(i);
		dist[i] = dist[p] + w;
		par[i]= p;
		wp[i] = w;
	}
	for(int i= n; i>= 1; i --) {
		ft[par[i]] = max(ft[par[i]],ft[i]);
	}
	for(int i = 0 ; i < q; i ++) {
		int v,l,r; cin>>v>>l>>r;
		Q[v].pb({{l,r},i});
	}
	for(int i= 1;i <= n ;i ++) {
		debug(ft[i],dist[i]);
		if(sz(G[i]) == 0) {
			debug("yay");
			upd(i,dist[i]);
		} else {
			upd(i,inf);
		}
	}
	dfs(1);
	for(int i =0 ;i < q; i ++) cout<<ans[i] << '\n';
	
    done;
}

