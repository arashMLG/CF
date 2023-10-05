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

const int N =5e5 + 23;
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
int a[N];
vector<int> v;
int ps[N],pp[N];
pair<int,pll> ans;

void get(int l,int r) {
	int x = pp[r] / pp[l-1];
	x -= ps[r] - ps[l-1];
	ans = max(ans,{x,{l,r}});
}

void solve() {
	v.clear();
	cin>>n;
	for(int i = 1; i <= n ; i ++)  {
		cin>>a[i];
		if(a[i] > 1) v.pb(i);
	}
	__int128_t x= 1;
	for(int i : v) {
		x *= a[i];
		if(x > inf) {
			cout<<v[0] << ' ' << v.back() << '\n';
			return;
		}
	}
	ans = {1, {1,1}};
	ps[0] =0 ,pp[0] =1;
	for(int i= 1; i <= n ; i++) {
		ps[i] = ps[i-1] + a[i];
		pp[i] = pp[i-1] * a[i];
	}
	for(int i = 0 ; i < sz(v) ;i ++) {
		for(int j = i; j < sz(v); j ++) {
			get(v[i],v[j]);
		}
	}
	cout<<ans.S.F << ' ' << ans.S.S << '\n';
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	int t= 1;
	cin>>t;
	for(int i = 1; i <= t; i ++) {
		#ifdef LOCAL
			cout<<"\n------------------\n" << "test case: " <<  i<< endl;
		#endif
		solve();
		#ifdef LOCAL
			cout<<endl;
		#endif
	}
    done;
}


