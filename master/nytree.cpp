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

const int N = 1e6 + 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 21;
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
int up[LOG][N];
int h[N];

void update(int v){ 
	for(int i = 1; i< LOG; i ++) up[i][v] = up[i-1][up[i-1][v]];
}

int f(int v,int k) {
	for(int i = 0 ;i < LOG; i ++) if((k >> i)&1) v = up[i][v];
	return v;
}

int lca(int v,int u) {
	if(h[v] > h[u]) swap(v,u);
	u = f(u,h[u]-h[v]);
	if(v == u) return v;
	for(int i = LOG-1; i >= 0 ; i--) if(up[i][v] != up[i][u]) v=up[i][v],u=up[i][u];
	return up[0][v];
}

int dist(int v,int u) {
	int l = lca(v,u);
	return h[v] + h[u] - 2*h[l];
}
int a= 2,b =3;

void add(int v) {
	int x = ++n;
	up[0][x] = v;
	h[x] = h[v] +1;
	update(x);
	if(dist(a,b) < dist(a,x)) b = x;
	if(dist(a,b) < dist(b,x)) a = x; 
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	n = 4;
	for(int i = 1; i<= n ;i ++){
		up[0][i] = 1;
		h[i] = (i != 1);
		update(i);
	}
	cin>>q;
	while(q--) {
		int v; cin>>v;
		add(v);
		add(v);
		cout<<dist(a,b) << '\n';
	}
    done;
}

