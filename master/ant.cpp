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

const int N = 1e5 + 23;
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

int n,m;
int a[N];
pii mn[N<<2];
int gc[N<<2];

pii merg(pii x,pii y) {
	if(x.F == y.F) {
		return {x.F,x.S + y.S};
	} else {
		return min(x,y);
	}
}

void build(int v=1,int tl=0,int tr=n) {
	if(tr - tl ==1) {
		mn[v] = {a[tl],1};
		gc[v] = a[tl];
		return;
	}
	int mid=(tl+tr)/2;
	build(lc,tl,mid);
	build(rc,mid,tr);
	gc[v] = __gcd(gc[lc],gc[rc]);
	mn[v] = merg(mn[lc],mn[rc]);
}

int qgc(int l,int r,int v= 1,int tl = 0, int tr= n) {
	if(l > r) return 0;
	
	if(l == tl && r == tr-1) {
		return gc[v];
	}
	int mid=(tl+tr)/2;
	return __gcd( qgc(l,min(mid-1,r),lc,tl,mid) , qgc(max(l,mid),r,rc,mid,tr));
}

pii qmn(int l,int r,int v = 1,int tl = 0,int tr = n) {
	if(l > r) return {inf,0};
	
	if(l == tl && r == tr-1) {
		return mn[v];
	}
	int mid=(tl+tr)/2;
	debug(tl,tr,l,r);
	return merg( qmn(l,min(mid-1,r),lc,tl,mid) , qmn(max(l,mid),r,rc,mid,tr));
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n; for(int i = 0;  i< n ; i++) cin>>a[i];
	build();
	cin>>m;
	while(m--) {
		int l,r; cin>>l>>r; l--,r--;
		pii x = qmn(l,r);
		int y = qgc(l,r);
		if(y % x.F == 0) {
			cout<<(r-l+1) - x.S << '\n';
		} else {
			cout<<r-l+1 << '\n';
		}
	}
    done;
}

