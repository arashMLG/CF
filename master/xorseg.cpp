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

struct SegTree {
	int t[N<<2];
	bool lz[N<<2];
	
	void init() {for(int i = 0 ; i< N*4; i ++) t[i] = lz[i] = 0;}
	
	void shift(int v,int tl,int tr) {
		if(!lz[v] || tr - tl == 1) return;
		int mid=(tl+tr)/2;
		t[lc] = (mid-tl) - t[lc];
		t[rc] = (tr - mid) - t[rc];
		lz[lc] = !lz[lc];
		lz[rc] = !lz[rc];
		lz[v] = 0;
	}
	
	void st(int pos,bool x,int v = 1, int tl = 0, int tr = N-1) {
		if(tr - tl == 1) {
			t[v] = x;
			return;
		}
		int mid=(tl+tr)/2;
		
		if(pos<mid)
			st(pos,x,lc,tl,mid);
		else
			st(pos,x,rc,mid,tr);
		t[v] = t[lc] + t[rc];
	}
	
	void upd(int l,int r, int v =1,int tl = 0 ,int tr = N-1) {
		if(l > r) return;
		if(l == tl && r == tr-1) {
			t[v] = (tr-tl) - t[v];
			lz[v]= !lz[v];
			return;
		}
		shift(v,tl,tr);
		int mid=(tl+tr)/2;
		upd(l,min(mid-1,r),lc,tl,mid);
		upd(max(mid,l),r,rc,mid,tr);
		t[v] = t[lc] + t[rc];
	}
	
	int sum(int l,int r,int v= 1,int tl = 0, int tr = N-1) {
		if(l > r) return 0;
		
		if(l == tl && r == tr-1) {
			return t[v];
		}
		shift(v,tl,tr);
		int mid = (tl+tr)/2;
		return sum(l,min(mid-1,r),lc,tl,mid) + sum(max(l,mid),r,rc,mid,tr);
	}
	
} seg[LOG];

int n,m;
int a[N];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	
	for(int i = 0; i < LOG; i++) seg[i].init();
	
	cin>>n;
	for(int i = 0 ; i < n ; i++) { 
		cin>>a[i];
		for(int j = 0 ; j< LOG; j ++) {
			seg[j].st(i,(a[i] >> j) &1);
		}
	}
	
	cin>>m;
	
	while(m--) {
		int q,l,r; cin>>q>>l>>r; l--,r--;
		if(q == 1) {
			ll ans =0;
			for(int i = 0 ; i < LOG; i++) {
				ans += (1LL << i) * seg[i].sum(l,r);
			}
			cout<<ans<<'\n';
		} else {
			int x; cin>>x;
			for(int i = 0; i < LOG; i++) {
				if((x >> i) &1) {
					seg[i].upd(l,r);
				}
			}
		}
	}
    done;
}
