#include<bits/stdc++.h>
#ifdef LOCAL
#include "Essentials/algo/debug.h"
#else
#define debug(...) 69
#endif
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

//https://quera.org/profile/4dykhk

typedef long long     ll;
typedef long double   ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll>   pll;

const int N = 2e5 + 23;
const int M = 1e6+23;
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

void ok(int &a) {
	if(a < 0) a += 10 * mod;
	a %= mod;
}


int fact[N],finv[N];

int C(int n, int r) {
	if(n < 0 || r < 0 || r > n) return 0;
	return fact[n]* finv[r] % mod * finv[n-r]%mod;
}

int n,q,k;
vector<int> divs[M];
int phi[M];
int cnt[M];
int ans=0;

void add(int x) {
	debug(x,divs[x]);
	for(int y : divs[x]) {
		int add = C(cnt[y]+1,k);
		ok(add -= C(cnt[y],k));
		ok(add *= phi[y]);
		ok(ans += add);
		cnt[y] ++;
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
   	phi[1] = 1;
   	for(int i= 2; i< M ; i++) {
   		phi[i]+= i-1;
   		for(int j = i*2; j< M ; j += i)
   			phi[j]-=phi[i];
   	}
	for(int i = 1; i < M ; i++) {
		for(int j = i ; j < M; j+= i) {
			divs[j].pb(i);
		}
	}
	fact[0] = finv[0]= 1; for(int i = 1; i< N; i ++) ok(fact[i] = fact[i-1] * i),finv[i] = pw(fact[i],mod-2);
	for(int i = 1; i <= 6; i ++) debug(i,phi[i]);
	cin>>n>>k>>q;
	for(int i = 0; i < n ;i ++) { int x; cin>>x; add(x);}
	for(int i = 0 ; i < q; i ++){ int x; cin>>x; add(x); cout<<ans << '\n';}
    done;
}

