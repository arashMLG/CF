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

struct seg {
	int t[N<<2];
	int lz[N<<2];
	
	seg() {
		for(int i = 0 ; i < (N<<2);i++) t[i] = 0;
	}
	
	void shift(int v,int tl,int tr) {
		if(lz[v] == 0) return;
		int mid=(tl+tr)/2;
		lz[lc] += lz[v];
		lz[rc] += lz[v];
		t[lc] += lz[v] * (mid-tl);
		t[rc] += lz[v] * (tr-mid);
		lz[v] = 0;
	}
	
	void update(int l,int r,int x,int v=1,int tl= 1,int tr = N) {
		if(l > r) return;
		if(l == tl && r == tr-1) {
			t[v] += x*(tr-tl);
			lz[v] += x;
			return;
		}
		shift(v,tl,tr);
		int mid=(tl+tr)/2;
		update(l,min(mid-1,r),x,lc,tl,mid);
		update(max(l,mid),r,x,rc,mid,tr);
		t[v] = t[lc] + t[rc];
	}
	
	void upd(int pos,int x) {
		update(pos,pos,x);
	}
	
	void upd(int l,int r,int x) {
		update(l,r,x);
	}
	
	int fk(int k,int v=1,int tl=1,int tr = N) {
		if(tr-tl==1) {
			return tl;
		}
		shift(v,tl,tr);
		int mid=(tl+tr)/2;
		if(t[lc] < k) 
			return fk(k-t[lc],rc,mid,tr);
		else
			return fk(k,lc,tl,mid);
	}
	
	int sum(int l,int r,int v=1,int tl=1,int tr= N){ 
		//debug(l,r);
		if(l>r) return 0LL;
		if(l == tl && r == tr-1) return t[v];
		shift(v,tl,tr);
		int mid=(tl+tr)/2;
		return sum(l,min(mid-1,r),lc,tl,mid) + sum(max(l,mid),r,rc,mid,tr);
	}
} L,R,inv;

int n;
int a[N];
int pos[N];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i=1; i<= n ;i ++) {
		cin>>a[i];
		pos[a[i]] = i;
	}
	int ans =0;
	for(int i = 1; i <= n ; i++) {
		int p = pos[i];
		ans += inv.sum(p,N-1);
		inv.upd(p,1);
		L.upd(p+1,N-1,1);
		R.upd(1,p-1,1);
		int x= inv.fk((i+1)/2);
		int javab = ans;
		
		javab += L.sum(1,x-1) + R.sum(x+1,N-1);
		debug(x,javab,L.sum(1,x-1),R.sum(x,N-1));
		int f = (i+1)/2- 1;
		javab -= f*(f-1)/2;
		f= i - (i+1)/2;
		javab -= f*(f-1)/2;
		cout<<javab << '\n';
	}
    done;
}


