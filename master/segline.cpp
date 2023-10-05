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

const int N = 1500 + 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const int inf = 1e9 + 23;

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

int n,s,m,k;
int a[N],mn[N],ps[N];
int dp[N][N];

bool check(int x) {
	for(int i = 1; i<= n ;i ++) {
		ps[i] = (a[i] <= x) + ps[i-1];
	}
	for(int i= 1; i<= n; i ++) {
		for(int j = 1; j <= m ; j ++) {
			dp[i][j] = max(dp[i-1][j], dp[mn[i]-1][j-1] + (ps[i] - ps[mn[i]-1]));
		}
	}
	return (dp[n][m] >= k);
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    iota(mn,mn+N,1);
	cin>>n>>s>>m>>k;
	for(int i =1 ; i <= n ; i ++) {
		cin>>a[i];
	}
	for(int i = 0 ; i < s; i ++) {
		int l,r; cin>>l>>r;
		for(int i = l; i <= r; i ++) mn[i] = min(mn[i],l);
	}
	int l = 0,r = inf;
	while(r-l>1) {
		int mid=(l+r)/2;
		if(check(mid)) r = mid; else l = mid;
	}
	if(r == inf) r = -1;
	cout<< r;
    done;
}

