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
const int M = 2e5 + 23;
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
vector<pii> G[M][2];
int pp[M][2];
bool mark[N],Mark[M][2];
int cnt =0;
bool sex=false;
bool ans[N];

void add(int v,int u) {
	int id = cnt++;
	G[v][0].pb({u,id}); G[u][1].pb({v,id});
}

void tour(int v,int id) {
	Mark[v][id] = true;
	while(pp[v][id] < sz(G[v][id])) {
		auto [u,eid] = G[v][id][pp[v][id]];
		if(!mark[eid]) {
			mark[eid] = true;
			tour(u,1-id);
			debug(v,id,u,eid);
			ans[eid] = sex;
			sex= !sex;
		}
		pp[v][id] ++;
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i = 0 ; i < n; i++) {
		int v,u; cin>>v>>u;
		add(v,u);
	}
	for(int i = 1; i< M ; i ++) for(int j = 0 ; j< 2;j ++) {
		if(sz(G[i][j]) &1) {
			if(j == 0)
				add(i,0);
			else
				add(0,i);
		}
	}
	if(sz(G[0][0]) &1) add(0,0);
	for(int i = 1; i< M ; i++) for(int j = 0; j < 2 ; j++) {
		if(!Mark[i][j]) {
			tour(i,j);
		}
	}
	for(int i = 0 ; i< n ; i++) {
	 	cout<<(ans[i] ? 'r' : 'b');
	}
    done;
}

