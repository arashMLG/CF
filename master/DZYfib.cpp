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

const int N = 3e5 + 23;
const int sq = 450;
const ll mod = 1e9+9; // 998244353
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
	if(a < 0) a += 10*mod;
	a %= mod;
}

int n,m;
int a[N];
pll f[N+23],pf[N+23];
int t[N<<2];
int fib[N];
pll lz[N<<2];

void build(int v=1,int tl= 1,int tr = n+1) {
	if(tr - tl == 1) {
		t[v] = a[tl];
		return;
	}
	int mid=(tl+tr)/2;
	build(lc,tl,mid);
	build(rc,mid,tr);
	ok(t[v] = t[lc] + t[rc]);
}

int fwd(pii x,int am) {
	int ans=0;
	ok(ans += x.F*f[am].F);
	ok(ans += x.S*f[am].S);
	return ans;
}

int swd(pii x,int am) {
	int ans = 0;
	ok(ans += x.F*pf[am].F);
	ok(ans += x.S*pf[am].S);
	debug(x,am,ans);
	return ans;
}


void shift(int v,int tl,int tr){ 
	ok(t[v] += swd(lz[v],tr-tl));
	if(tr-tl == 1) {
		lz[v] = {0LL,0LL};
		return;
	}
	
	int mid=(tl+tr)/2;
	ok(lz[lc].F += lz[v].F);
	if(tl+1<mid)
		ok(lz[lc].S += lz[v].S);
	ok(lz[rc].F +=fwd(lz[v],mid-tl+1));
	if(mid+1<tr)
		ok(lz[rc].S += fwd(lz[v],mid-tl+2));
	lz[v] = {0LL,0LL};
}

int ql,qr;

void upd(int l,int r,int v=1,int tl = 1,int tr= n+1){ 
	shift(v,tl,tr);
	if(l > r) return;
	if(l == tl && r == tr-1) {
		ok(lz[v].F += fib[tl-ql]);
		if(tl+1<tr)
			ok(lz[v].S += fib[tl-ql+1]);
		shift(v,tl,tr);
		return;
	}
	int mid=(tl+tr)/2;
	upd(l,min(mid-1,r),lc,tl,mid);
	upd(max(l,mid),r,rc,mid,tr);
	ok(t[v] = t[lc] + t[rc]);
}

int sum(int l,int r,int v =1,int tl=1,int tr=n+1) {
	shift(v,tl,tr);
	if(l > r) return 0LL;
	if(l == tl && r == tr-1) {debug(tl,tr,t[v]);return t[v];}
	int mid=(tl+tr)/2;
	return (sum(l,min(mid-1,r),lc,tl,mid) + sum(max(l,mid),r,rc,mid,tr))%mod;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	fib[0] = fib[1] = 1;
	for(int i = 2; i< N ; i++) ok(fib[i] = fib[i-1] + fib[i-2]);
	f[1] = {1LL,0LL}, f[2] = {0LL,1LL};
	pf[1]= {1LL,0LL},pf[2] = {1LL,1LL};
	for(int i= 3; i < N+23 ; i ++) {
		ok(f[i].F = f[i-1].F + f[i-2].F);
		ok(f[i].S = f[i-1].S + f[i-2].S);
		ok(pf[i].F = f[i].F + pf[i-1].F);
		ok(pf[i].S = f[i].S + pf[i-1].S);
	}
	cin>>n>>m;
	for(int i = 1; i<= n ; i++) {
		cin>>a[i];
	}
	build();
	while(m--) {
		int q,l,r;cin>>q>>l>>r;
		if(q == 1) {ql = l,qr = r;upd(l,r);}
		else {cout<<(sum(l,r))%mod << '\n';}
	}
    done;
}

