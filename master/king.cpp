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

int n,q;
vector<int> G[N];
int st[N],h[N];
int up[N][LOG];
int timer;
bool mark[N];

void dfs(int v,int p = 1) {
	st[v] = timer ++;
	up[v][0] = p;
	for(int i = 1; i< LOG; i ++) {
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for(int u : G[v]) if(u != p){
		h[u] = h[v] + 1;
		dfs(u,v);
	}
}

int f(int v,int k) {
	for(int i = 0; i < LOG ; i ++)
		if((k >> i) &1)
			v = up[v][i];
	return v;
}

int lca(int v,int u) {
	if(h[v] > h[u]) swap(v,u);
	u= f(u,h[u] - h[v]);
	if(v == u) return v;
	for(int i = LOG-1; i>= 0 ; i --) 
		if(up[v][i] != up[u][i])
			v = up[v][i],u= up[u][i];
	return up[v][0];
}

int dist(int v,int u) {
	int l = lca(v,u);
	return h[v] + h[u] - 2*h[l];
}

vector<int> G2[N];
vector<int> hmm,sex;
bool is[N];
int ans=0;

int dp(int v) {
	int sum = 0;
	for(int u : G2[v]) {
		sum += dp(u);
	}
	if(is[v]) {
		ans += sum;
		return 1;
	} else {
		if(sum == 1 || sum == 0) return sum;
		else {
			ans ++;
			return 0;
		}
	}
}

void solve() {
	int k; cin>>k;
	hmm.clear(); sex.clear();
	for(int i = 0 ; i < k ; i++) {
		int v; cin>>v;
		hmm.pb(v);
	}
	sort(all(hmm) , [&](int a,int b) {return st[a] < st[b];});
	bool can= true;
	for(int i = 0 ;i < sz(hmm) ; i++) {
		int v= hmm[i];
		if(mark[up[v][0]]) can =false;
		mark[v] = true;
	}
	for(int v : hmm) mark[v] = false;
	if(!can) {
		cout<<-1 << '\n';
		return;
	}
	for(int v: hmm) sex.pb(v);
	for(int i = 0 ; i < sz(hmm)-1 ; i ++) {
		int l = lca(hmm[i],hmm[i+1]);
		sex.pb(l);
	}
	for(int x : hmm) is[x] = true;
	sort(all(sex)); sex.resize(unique(all(sex)) - sex.begin());
	sort(all(sex), [&](int a,int b) {return st[a] < st[b];});
	debug(hmm,sex);
	for(int i = 1; i < sz(sex) ; i++) {
		G2[lca(sex[i],sex[i-1])].pb(sex[i]);
	}
	ans = 0;
	dp(sex[0]);
	cout<<ans << '\n';
	for(int v : sex) G2[v].clear(),is[v] = false;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i = 1 ; i <n ; i++) {
		int v,u; cin>>v>>u;
		G[v].pb(u); G[u].pb(v);
	}
	cin>>q;
	dfs(1);
	while(q--) {
		solve();
	}
    done;
}

