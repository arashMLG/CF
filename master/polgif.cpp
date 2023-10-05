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

const int N = 1e6 + 23;
const int sq = 1e3+23;
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

int n,k;
int a[N];
int cnt[N];
bitset<N> dp,mark;

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>k;
	for(int i = 1;i <= n ;i ++) cin>>a[i];
	int one=0,two =0;
	for(int i =1; i<= n ; i++) {
		if(!mark[i]) {
			int v = i;
			int len=0;
			do {
				mark[v] = true;
				len++;
				v = a[v];
			}while(v != i);
			cnt[len] ++;
			one += len/2;
			two += len%2;
		}
	}
	
	dp[0] =1;
	for(int i = n; i>=1 ; i--) {
		if(!cnt[i]) continue;
		int p = 1;
		while(cnt[i]) {
			int x = min(cnt[i],p);
			dp |= (dp << x*i);
			cnt[i] -= x;
			p *= 2;
		}
	}
	int mn = k;
	if(!dp[k]) mn = k+1;
	int mx = 2*min(k,one);
	k -= min(k,one);
	mx += min(k,two);
	cout<<mn << ' ' << mx << '\n';
    done;
}

