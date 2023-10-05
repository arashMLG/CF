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

int n,m,q;
vector<int> G[N];
vector<pii> edges;
int dist[N];
queue<int> Q;
bool mark[N];

int bfs(int x) {
	for(int  i =0 ; i <x; i ++) {
		auto [v,u] = edges[i];
		G[v].pb(u);  G[u].pb(v);
	}
	dist[1] =0;
	int ans =0;
	Q.push(1);
	ms(mark,0);
	mark[1] = true;
	while(sz(Q)) {
		int v = Q.front(); Q.pop();
		ans = max(ans,dist[v]);
		for(int u : G[v]) if(!mark[u]) {
			dist[u] = dist[v] + 1;
			mark[u] = true;
			Q.push(u);
		}
	}
	for(int i = 0 ; i < x; i++) {
		auto [v,u] = edges[i];
		G[v].pop_back();  G[u].pop_back();
	}
	return ans;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m>>q;
	for(int i = 0 ; i < m ; i++) {
		int v,u; cin>>v>>u;
		G[v].pb(u);
		G[u].pb(v);
	}
	for(int i = 0 ; i < q; i++) {
		int v,u; cin>>v>>u;
		edges.pb({v,u});
	}
	int i = 0;
	while(i <= q) {
		int ahh = bfs(i);
		int l = i, r = q+1;
		while(r-l>1) {
			int mid=(l+r)/2;
			int x=  bfs(mid);
			if(ahh <= x*2) l = mid;
			else r= mid;
		}
		for(int j = i ; j < r; j++) cout<< ahh << ' ';
		i = r;
	}
    done;
}

