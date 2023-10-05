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
#define int      ll

ll pw(ll a, ll b, ll md = mod){ll res = 1; while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

int n;
vector<int> G[N];
int a[N];
int ans[N],d[N],pp[N],cd[N],lp[N];

// d = diameter too subtree v
// pp= path az leaf to v va ye path dige
// cd= diameter to bache ha
// lp= path az leaf ta v

void dfs(int v,int p = -1) {
	ans[v] = d[v] = pp[v] = lp[v] = a[v];
	for(int u : G[v]) if(u != p) {
		dfs(u,v);
		
		// baray ans[v]
		// ans[v] 
		// ans[u]
		// d[u] + d[v] -> dota diam
		// pp[v] + lp[u] -> pp az v lp az u
		// lp[v] + pp[u] -> pp az u lp az v
		ans[v] = max({ ans[v] , ans[u], d[u] + d[v] , pp[v] + lp[u] , pp[u] + lp[v]});
		// baray d[v]
		// d[v]
		// d[u]
		// lp[u] + lp[v] -> diam az v migzare 
		d[v] =   max({ d[v] , d[u] , lp[v] + lp[u]});
		// baray pp[v]
		// pp[v]
		// pp[u] + a[v] -> pp az u baad fagat v ham ezafe mikonim
		// lp[u] + a[v] + cd[v] -> path ta leaf az (u +v) daim az bache hay dige
		// d[u] + lp[v] -> diam az u, path sz leaf az v
		pp[v] =  max({pp[v], pp[u] + a[v] , lp[u] + a[v] + cd[v], d[u] + lp[v]});
		// baray cd[v]
		// cd[v]
		// d[u] -> diam az bache
		cd[v] = max(cd[v] , d[u]);
		// baray lp[v]
		// lp[v]
		// lp[u] + d[v] -> maximum masir az leaf ta v az u rad she
		lp[v] = max(lp[v] , lp[u] + a[v]);
	}
	debug(v,ans[v],d[v],pp[v],cd[v],lp[v]);
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i = 1; i<= n ;i ++) cin>>a[i];
	for(int i =1; i < n ; i++) {
		int v,u; cin>>v>>u;
		G[v].pb(u);
		G[u].pb(v);
	}
	dfs(1);
	cout<<ans[1];
    done;
}

