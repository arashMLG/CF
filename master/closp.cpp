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
const ll inf = 5e18;

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

int t[N<<2];

void build() {for(int i = 1; i< (N<<2) ;i++) t[i] = inf;}

void upd(int pos,int x,int v=1,int tl = 0, int tr = N) {
	if(tr-tl == 1) {
		t[v] = min(t[v],x);
		return;
	}
	int mid=(tl+tr)/2;
	if(pos<mid)
		upd(pos,x,lc,tl,mid);
	else
		upd(pos,x,rc,mid,tr);
	t[v] = min(t[lc],t[rc]);
}

int mn(int l,int r,int v=1,int tl= 0 ,int tr= N) {
	if(l > r) return inf;
	if(l == tl && r == tr-1) return t[v];
	int mid=(tl+tr)/2;
	return min( mn(l,min(mid-1,r),lc,tl,mid) , mn(max(l,mid),r,rc,mid,tr));
}

int n,m;
pll a[N];

int dist(int i,int j) {
	return abs(a[i].F - a[j].F) * (a[i].S + a[j].S);
}

vector<int> L[N];
vector<pll> Q[N];
int l[N],r[N];
stack<int> st;
int ans[N];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i = 1; i<=n ;i ++) cin>>a[i].F >> a[i].S;
    st.push(0);
    for(int i = 1; i<= n ; i++) {
    	while(a[st.top()].S > a[i].S) st.pop();
    	l[i] = st.top();
    	st.push(i);
    } while(sz(st)) st.pop();
    st.push(n+1);
    for(int i = n; i >= 1; i--) {
    	while(a[st.top()].S > a[i].S) st.pop();
    	r[i] = st.top();
    	st.push(i); 
    }
    for(int i = 1; i<= n ; i++) {
    	L[r[i]].pb(i);
    	L[i].pb(l[i]);
    }
    for(int i = 0; i < m ; i++) {
    	int le,ri; cin>>le>>ri;
    	Q[ri].pb({le,i});
    }
    build();
    for(int i = 1; i<= n ;i ++) {
    	for(int u : L[i]) upd(u,dist(i,u));
    	for(auto [u,id] : Q[i]) ans[id] = mn(u,i);
    }
    for(int i = 0 ;i < m ; i++) cout<<ans[i] << '\n';
    done;
}

