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
const int LOG = 20;
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

int n,m;
int x[LOG<<1];
int a[N];
bool cum[LOG<<1];
int dp[1<<LOG];
int adj[LOG<<1];
vector<int> G[LOG<<1];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
    for(int i = 0 ; i<  n; i ++) {
    	cin>>a[i];
    	a[i] --;
	}
	for(int i = 0 ;i < m ; i++) cin>>x[i];
	for(int i = 1; i < n ; i++) {
		if(a[i] == a[i-1]) {
			cum[a[i]] = true;
		} else {
			adj[a[i]] |= (1LL<<a[i-1]);
			adj[a[i-1]] |= (1LL<<a[i]);
		}
	}
	for(int i = 0 ; i < 40 ;i ++) {
		for(int j = 0 ; j < 40; j ++) {
			if(((adj[i]) >> j) &1)
				G[i].pb(j);
		}
	}
	cum[a[0]] = true;
	cum[a[n-1]] = true;
	for(int mask = 0 ; mask < (1 <<LOG) ; mask ++) {
		bool wellshit = false;
		for(int i = 0 ;i < LOG; i ++) {
			if(cum[i+LOG] && ((mask >> i)&1)) {
				wellshit = true;
				break;
			}
		}
		
		for(int i = 0; i < LOG; i ++) if((mask >> i)&1) {
			for(int u : G[i+LOG]) {
				if(u >= LOG) {
					int uu = u-LOG;
					if((mask >> uu)&1) {
						wellshit = true;
					}
				}
			}
		}
		if(wellshit) {
			dp[mask] = inf;
			continue;
		}
		int sum = 0;
		for(int i = 0 ; i < LOG; i ++) {
			if(((mask >> i)&1) == 0)
				sum += x[i+LOG];
		}
		dp[mask] = sum;
	}
	for(int i = 0 ; i < LOG; i++)
		for(int mask = 0 ; mask < (1 <<LOG) ; mask ++)
			if((mask >>i)&1)
				dp[mask] = min(dp[mask], dp[mask^ (1LL << i)]);
	int ans =inf;
	for(int mask = 0 ; mask < (1 << LOG) ; mask ++)  {
		bool wellshit = false;
		for(int i = 0 ;i < LOG; i ++) {
			if(cum[i] && ((mask >> i)&1)) {
				wellshit = true;
				break;
			}
		}
		
		for(int i = 0; i < LOG; i ++) if((mask >> i)&1) {
			for(int u : G[i]) {
				if(u < LOG) {
					int uu = u;
					if((mask >> uu)&1) {
						wellshit = true;
					}
				}
			}
		}
		if(wellshit) {
			continue;
		}
		int wow = 0;
		int tot = 0;
		for(int i = 0 ; i < LOG; i ++) {
			if(((mask >> i) & 1) == 0) {
				tot += x[i];
			} else {
				wow |= adj[i];
			}
		}
		wow = (~wow) & ((1LL << 40)-1);
		wow = wow >> LOG;
		//debug(tot + dp[wow]);
		ans = min(ans,tot + dp[wow]);
	}
	cout<<ans;
    done;
}

