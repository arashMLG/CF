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
const int sq = 320;
const ll mod = 1e9+7; // 998244353
const int LOG = 21;
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

int n,m,k;
int a[N];
int l[N],r[N];
int ps[N];
vector<int> v;
int cnt[1<<LOG];
ll javab[N];
ll ans=0;

void add(int x) {
	int f = x^k;
	ans += cnt[f];
	cnt[x] ++;
}

void rem(int x) {
	int f = x^k;
	if(k == 0) ans -= cnt[f] -1;
	else ans -= cnt[f];
	cnt[x] --;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m>>k;
	for(int i =1 ; i<= n ;i ++) {
		cin>>a[i];
		ps[i] = a[i] ^ ps[i-1];
	}
	for(int i = 1; i <= m ;i ++) {
		cin>>l[i]>>r[i]; l[i] --; v.pb(i);
	}
	int curl =0, curr = -1;
	sort(all(v), [&] (int x,int y) {if(l[x] /sq == l[y] / sq) return r[x] < r[y]; return l[x] < l[y];});
	
	for(int i : v) {
		while(curr < r[i])
			add(ps[++curr]);
		while(curl > l[i])
			add(ps[--curl]);
		while(curr > r[i])
			rem(ps[curr--]);
		while(curl < l[i])
			rem(ps[curl++]);
		javab[i] = ans;
	}
	for(int i= 1; i<= m ; i++) cout<<javab[i] << '\n';
    done;
}

