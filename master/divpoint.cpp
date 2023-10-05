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

const int N = 1e3 + 23;
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
int x[N],y[N];
vector<int> v[2][2];

void solve() {
	for(int i = 0 ; i < 2; i ++) for(int j = 0 ;j < 2;j ++) v[i][j].clear();
	for(int i = 0 ; i < n ; i++) {
		v[x[i]&1][y[i]&1].pb(i);
	}
	if(sz(v[0][0]) == n) {
		for(int i : v[0][0]) x[i]/=2, y[i]/=2;
		solve();
	} else if(sz(v[0][1]) == n) {
		for(int i : v[0][1]) y[i] --;
		solve();
	} else if(sz(v[1][0]) == n) {
		for(int i : v[1][0]) x[i] --;
		solve();
	} else if(sz(v[1][1]) == n) {
		for(int i : v[1][1]) x[i]--,y[i]--;
		solve();
	}
	if(sz(v[0][0]) + sz(v[1][1]) == n) {
		cout<<sz(v[0][0]) << '\n';
		for(int i : v[0][0]) cout<< i+1 << ' ';
		exit(0);
	} else if(sz(v[0][1]) + sz(v[1][0]) == n) {
		cout<<sz(v[0][1]) << '\n';
		for(int i : v[0][1]) cout<<i+1 << ' ';
		exit(0);
	} else {
		cout<<sz(v[0][0]) + sz(v[1][1]) << '\n';
		for(int i : v[0][0]) cout<<i+1 << ' ';
		for(int i : v[1][1]) cout<<i+1 << ' ';
		exit(0);
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i= 0 ;i < n ;i ++) cin>>x[i] >>y[i];
	solve();
    done;
}

