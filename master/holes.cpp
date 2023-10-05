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

const int N = 1e5 + 320 + 23;
const int sq = 320;
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
pii dp[N];
int a[N];

void upd(int i,int x) {
	int l = i/sq * sq;
	int r = (i/sq +1) * sq-1;
	a[i] = x;
	for(int j = i ; j >= l ; j --) {
		int x = min(n,j+a[j]);
		if(x == n || x > r) {
			dp[j] = {1,j};
		} else {
			dp[j] = {dp[x].F + 1, dp[x].S};
		}
	}
}

void go(int i) {
	int ans=0;
	int cur = i;
	while(cur != n) {
		ans += dp[cur].F;
		cur = dp[cur].S;
		if(cur + a[cur] >= n) {
			cout<< cur + 1 << ' ' << ans << '\n';
			return;
		} else {
			cur += a[cur];
		}
		
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i = 0 ; i < n ;i ++) cin>>a[i];
	for(int i = sq-1; i < n ; i+=sq) upd(i,a[i]);
	upd(n-1,a[n-1]);
	while(m--) {
		int q,i;
		cin>>q>>i;
		if(q ==0) {
			int x; cin>>x;
			upd(i-1,x);
		} else {
			go(i-1);
		}
	}
    done;
}

