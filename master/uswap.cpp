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

int n,m;
int p[N];
vector<pii> sex[N];
vector<int> G[N];
bool mark[N];
vector<int> ans;
int val[N];
vector<int> ahh;

void dfs(int v) {
	mark[v] = true; for(int u : G[v]) if(!mark[u]) dfs(u); ans.pb(v);
} 

int f;
bool cmp(pii a,pii b) {return ((val[a.F] - val[f] +n) % n) < ((val[b.F] - val[f] + n) % n);}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i = 1; i<= n ; i++) {
		cin>>p[i];
	}	
	for(int i = 0 ; i <m ; i ++) {
		int v,u; cin>>v>>u;
		sex[v].pb({u,i+1});
		sex[u].pb({v,i+1});
	}
	
	for(int i = 1; i <= n ; i++) {
		if(mark[i]) continue;
		ahh.clear();
		int v = i;
		int x= 0;
		do {
			val[v] = x++;
			v = p[v];
			ahh.pb(v);
			mark[v] = true;
		} while(v != i);
		for(int x : ahh) {
			f= x;
			sort(all(sex[x]) ,cmp);
			for(int i = 0; i < sz(sex[x])-1; i ++) G[sex[x][i].S].pb(sex[x][i+1].S);
		}
	}
	ms(mark,0); for(int i = 1; i<= m; i ++) if(!mark[i]) dfs(i); reverse(all(ans)); for(int x : ans) cout<<x << ' ';
    done;
}

