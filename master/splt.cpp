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

const int N = 1e5 + 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const ll inf = 3e18;

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

pll mx[N<<2];
int lz[N<<2];
int val[N<<2];

void build(int v=1,int tl =0 ,int tr= N) {
	if(tr- tl == 1) {
		mx[v] = {0,tl};
		return;
	}
	int mid=(tl+tr)/2;
	build(lc,tl,mid);
	build(rc,mid,tr);
	mx[v] = max(mx[lc],mx[rc]);
}

void shift(int v) {
	if(lz[v] == 0) return;
	lz[lc] += lz[v];
	lz[rc] += lz[v];
	mx[lc].F += lz[v];
	mx[rc].F += lz[v];
	lz[v] = 0;
}

void upd(int l,int r,int x=-inf,int v=1,int tl = 0,int tr = N) {
	if(l >r)return;
	if(l == tl && r == tr-1) {
		if(x == -1) mx[v] = {0,tl};
		else  {
			mx[v].F += x;
			lz[v] += x;
		}
		return;
	}
	shift(v);
	int mid=(tl+tr)/2;
	upd(l,min(mid-1,r),x,lc,tl,mid);
	upd(max(l,mid),r,x,rc,mid,tr);
	mx[v] = max(mx[lc],mx[rc]);
}

pll gmx(int l,int r,int v =1,int tl = 0, int tr = N) {
	if(l > r) return {0LL,0LL};
	if(l == tl && r == tr-1) return mx[v];
	shift(v);
	int mid=(tl+tr)/2;
	return max( gmx(l,min(mid-1,r),lc,tl,mid) , gmx(max(l,mid),r,rc,mid,tr));
}

void vupd(int pos,int x,int v=1,int tl = 0, int tr = N) {
	if(tr-tl==1) {
		val[v] = x;
		return;
	}
	int mid=(tl+tr)/2;
	if(pos<mid)
		vupd(pos,x,lc,tl,mid);
	else
		vupd(pos,x,rc,mid,tr);
	val[v] = min(val[lc],val[rc]);
}

int gmn(int l,int r,int v=1,int tl =0,int tr= N) {
	if(l >r) return inf;
	if(l == tl&&r == tr-1) return val[v];
	int mid=(tl+tr)/2;
	return min( gmn(l,min(mid-1,r),lc,tl,mid) , gmn(max(l,mid),r,rc,mid,tr));
}

int n,L,S;
int w[N];
int st[N],ft[N];
int dp[N];
int timer;
int h[N];
vector<int> sex[N*2];
vector<int> G[N];

void dfsset(int v) {
	st[v] = timer ++;
	ft[v] = st[v];
	sex[h[v]].pb(st[v]);
	for(int u : G[v]) {
		h[u] = h[v]+1;
		dfsset(u,v);
		ft[v] = ft[u];
	}
}

void dfs(int v) {
	int sum =0;
	for(int u : G[v]) {
		dfs(u);
		sum += dp[u];
	}
	vupd(st[v],sum);
	dp[v] = sum+1;
	upd(st[v],ft[v],w[v]);
	while(true) {
		pll x= gmx(st[v],ft[v]);
		if(x.F <= S) break;
		upd(x.S,x.S);
		vupd(x.S,inf);
	}
	if(sz(sex[h[v]+L])) {
		int x= h[v] + L;
		int l = upper_bound(all(sex[x]),st[v]) - sex[x].begin();
		int r = upper_bound(all(sex[x]),ft[v]) - sex[x].begin()-1;
		for(int i = l ; i <= r; i ++) {
			upd(sex[x][i],sex[x][i]);
			vupd(sex[x][i],inf);
		}
	}
	for(int u : G[v]) {
		int what = gmn(st[u],ft[u]);
		
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>L>>S;
	for(int i = 1; i <= n ;i ++) cin>>w[i];
	for(int i = 2; i<= n ; i++) {
		int p; cin>>p; G[p]
	}
    done;
}

