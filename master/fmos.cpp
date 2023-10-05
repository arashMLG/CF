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

const int N = 4e5 + 23;
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

typedef pair<pll,ll> mos;

int mn[N<<2],lz[N<<2];

void build() {
	for(int i = 0; i < (N<<2) ; i ++) mn[i] = lz[i] = inf;
}


void upd(int l,int r,int x,int v = 1,int tl = 0,int tr = N) {
	if(l > r) return;
	if(l == tl && r == tr-1) {
		mn[v] = min(mn[v],x);
		lz[v] = min(lz[v],x);
		return;
	}
	int mid=(tl+tr)/2;
	upd(l,min(mid-1,r),x,lc,tl,mid);
	upd(max(l,mid),r,x,rc,mid,tr);
	mn[v] = min(mn[lc],mn[rc]);
}

int get(int pos,int x=inf,int v=1,int tl = 0 ,int tr = N) {
	x = min(x,lz[v]);
	if(tr - tl == 1) return min(mn[v],x);
	int mid=(tl+tr)/2;
	if(pos<mid)
		return get(pos,x,lc,tl,mid);
	else
		return get(pos,x,rc,mid,tr);
}
	

vector<int> comp;

int fnd(int x){ 
	return upper_bound(all(comp),x) - comp.begin()+1;
}

int n,m;
int x[N],t[N],p[N],b[N];
int ans[N];
set<mos> st;
vector<mos> qu;
map<int,int> mp;

void doit(int v) {
	while(sz(st)) {
		mos now = *st.lower_bound({{x[v],0},0});
		auto l = st.lower_bound({{x[v],0},0});
		if(now.F.F > x[v] + t[v] || l == st.end()) break;
		t[v] += now.F.S;
		st.erase(now);
		ans[v] ++;
	}
	upd(fnd(x[v]),fnd(x[v] + t[v]),x[v]);
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	build();
	for(int i = 0 ; i< n ; i++) {
		cin>>x[i] >> t[i];
		comp.pb(x[i]);
		mp[x[i]] = i;
	}
	for(int i = 0 ; i < m ; i++) {
		cin>>p[i]>>b[i];
		comp.pb(p[i]);
		qu.pb({{p[i],b[i]},i});
	}
	sort(all(comp));
	comp.resize(unique(all(comp)) - comp.begin());
	debug(comp);
	for(int i = 0; i < n ;i ++) {
		upd(fnd(x[i]),fnd(x[i] + t[i]),x[i]);
	}
	for(mos now : qu) {
		st.insert(now);
		int sex = now.F.F;
		int fuck = get(fnd(sex));
		debug(sex,fnd(sex),fuck);
		if(fuck == inf) continue;
		
		doit(mp[fuck]);
	}
	for(int i = 0 ; i < n ;i ++) {
		cout<<ans[i] << ' '<< t[i] << '\n';
	}
    done;
}

