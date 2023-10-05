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

const int N = 1e6+ 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const int inf = 2e9;

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

int n,m,s,t;
int dp[N];
int out[N];
vector<int> G[N];
deque<int> Q;
bool mark[N];

void bfs() {
	dp[t]= 0;
	Q.push_front(t);
	while(sz(Q)) {
		int v = Q.front(); Q.pop_front();
		if(mark[v]) continue;
		mark[v] = true;
		for(int u : G[v]) {
			if(dp[u] > dp[v]) {
				if(out[u] == 1) {
					dp[u] = dp[v];
					Q.push_front(u);
				} else {
					dp[u] = dp[v] + 1;
					Q.push_back(u);
				}
				out[u] --;
			}
		}
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    fill(dp,dp+N,inf);
	cin>>n>>m;
	for(int i = 0 ; i < m ; i ++) {
		int v,u; cin>>v>>u;
		out[v] ++;
		G[u].pb(v);
	}
	cin>>s>>t;
	bfs();
	cout<<(dp[s] == inf? -1 : dp[s]) << '\n';
    done;
}

