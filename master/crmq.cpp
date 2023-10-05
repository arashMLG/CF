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

const int N = 2e5 + 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const ll inf = 8e18;

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
ll a[N];
ll t[N<<2];
ll lz[N<<2];

void build(int v = 1, int tl = 0, int tr = n) {
	if(tr - tl ==1) {
		t[v] = a[tl];
		return;
	}
	int mid=(tl+tr)/2;
	build(lc,tl,mid);
	build(rc,mid,tr);
	t[v] = min(t[lc],t[rc]);
}

void shift(int v) {
	t[lc] += lz[v];
	t[rc] += lz[v];
	lz[lc] += lz[v];
	lz[rc] += lz[v];
	lz[v] = 0LL;
}

void add(int l,int r,int x,int v =1,int tl = 0, int tr = n) {
	if(l > r) return;
	if(l == tl && r == tr-1) {
		t[v] += x;
		lz[v] += x;
		return;
	}
	shift(v);
	int mid=(tl+tr)/2;
	add(l,min(mid-1,r),x,lc,tl,mid);
	add(max(l,mid),r,x,rc,mid,tr);
	t[v] = min(t[lc],t[rc]);
}

ll mn(int l,int r,int v=1,int tl = 0, int tr = n) {
	if(l > r) return inf;
	
	if(l == tl && r == tr-1) {
		return t[v];
	}	
	shift(v);
	int mid=(tl+tr)/2;
	return min(mn(l,min(mid-1,r),lc,tl,mid) , mn(max(l,mid),r,rc,mid,tr));
}

void Add(int l,int r,int x) {
	if(r < l) {
		add(l,n-1,x);
		add(0,r,x);
	} else {
		add(l,r,x);
	}
}

ll Mn(int l, int r) {
	if(r < l) {
		return min( mn(l,n-1), mn(0,r));
	} else {
		return mn(l,r);
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	scanf("%d",&n);
	for(int i=0; i< n;i++) scanf("%lld",a+i);
	build();
	scanf("%d",&m);
	while(m--) {
		int l,r; char c;
		scanf("%d %d",&l,&r);
		c=getchar();
		if(c == '\n') {
			cout<<Mn(l,r)<<'\n';
		} else {
			int x;
			scanf("%d",&x);
			Add(l,r,x);
		}
	}
    done;
}
