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
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const ldb inf = 1e18;

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
//#define int         ll

ll pw(ll a, ll b, ll md = mod){ll res = 1; while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

typedef pair<ldb,int>  pli;

int n,m;
vector<pli> G[N];
MinHeap(pli) pq;
ldb s[N],dist[N],mul[N];
bool mark[N];


int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i = 0 ; i< N ; i++) s[i] = 0.0,dist[i] = inf,mul[i] = 1.0;
	cin>>n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1 ; j <= n ; j ++) { 
			int p; cin>>p;
			G[j].pb({1.0 -(p)/100.0,i});
		}
	}
	dist[n] = 0.0;
	pq.push({dist[n],n});
	while(sz(pq)) {
		int v=  pq.top().S; pq.pop();
		if(mark[v]) continue;
		mark[v] = true;
		debug(v,dist[v],G[v]);
		for(auto [w,u] : G[v]) if(!mark[u]) {
			ldb ns,ndist,nmul;
			nmul = mul[u] * w;
			ns = s[u] + (1.0 + dist[v]) * mul[u] * (1.0- w);
			ndist = (nmul + ns) / (1.0 - nmul);
			dist[u] = ndist;
			s[u] = ns;
			mul[u] = nmul;
			pq.push({dist[u],u});
		}
	}
	cout<< fixed << setprecision(10) << dist[1];
    done;
}


