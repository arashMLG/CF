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

int mx[N<<2];

void upd(int l,int r,int x,int v = 1,int tl = 1, int tr = N) {
	if(l > r) return;
	if(l == tl && r == tr-1) {
		mx[v] = max(mx[v],x);
		return;
	}
	int mid=(tl+tr)/2;
	upd(l,min(mid-1,r),x,lc,tl,mid);
	upd(max(l,mid),r,x,rc,mid,tr);
}

int get(int pos,int x = 0,int v=1,int tl = 1,int tr=N) {
	x = max(x,mx[v]);
	if(tr-tl == 1) return x;
	int mid=(tl+tr)/2;
	if(pos < mid)
		return get(pos,x,lc,tl,mid);
	else
		return get(pos,x,rc,mid,tr);
}

int n;
int a[N];
vector<int> comp;
int dp[N];
pair<int,pii> lst[N];
vector<int> ind[N];
vector<int> sex;
vector<int> ans;

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	fill(mx,mx+N,-1);
	cin>>n;
	for(int i = 1 ; i <= n ; i++) {
		cin>>a[i];
		comp.pb(a[i]);
	}
	sort(all(comp));
	comp.resize(unique(all(comp)) - comp.begin());
	for(int i = 1 ; i <= n ; i ++) a[i] = lower_bound(all(comp),a[i])-comp.begin()+1;
	for(int i = 1; i<= n ;i ++) {
		sex.clear();
		for(int j = sz(ind[a[i]])-1; j >= max(0,sz(ind[a[i]])-3); j --) {
			int x = get(ind[a[i]][j]);
			if(x != 0)
				sex.pb(x);
		}
		if(sz(ind[a[i]]) >= 3) {
			sex.pb(ind[a[i]][sz(ind[a[i]])-3]);
		}
		dp[i] =dp[i-1];
		lst[i] = lst[i-1];
		for(int u : sex) {
			if(dp[i] < dp[u-1] + 1) {
				lst[i] = {u-1,{a[u],a[i]}};
				dp[i] = dp[u-1]+1;
			}
		}
		if(sz(ind[a[i]])) {
			int l = ind[a[i]].back();
			upd(l+1,i-1,l);
		}
		ind[a[i]].pb(i);
	}
	int X = n;
	while(true) {
		if(lst[X].S.F == 0) break;
		ans.pb(lst[X].S.S); ans.pb(lst[X].S.F);
		ans.pb(lst[X].S.S); ans.pb(lst[X].S.F);
		X = lst[X].F;
	}
	reverse(all(ans));
	cout<<sz(ans) << '\n';
	for(int x : ans) cout<<comp[x-1] << ' ';
    done;
}

