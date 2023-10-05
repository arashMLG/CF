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

int q;
map<int,int> par,xo;

pii getPar(int v) {
	if(par[v] == 0) return {v,0};
	pii P = getPar(par[v]);
	par[v]= P.F;
	xo[v] ^=P.S;
	return {par[v],xo[v]};
}

void merge(int v,int u,int x) {
	if(rng()&1) swap(v,u);
	pii P1 = getPar(v);
	pii P2 = getPar(u);
	v = P1.F,u=P2.F;
	if(u == v) return;
	par[v] = u;
	xo[v] = x^P1.S^P2.S;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>q;
    int last=0;
	while(q--) {
		int t,l,r; cin>>t>>l>>r;
		l ^= last,r ^= last;
		if(l > r) swap(l,r);
		r++;
		if(t == 1) {
			int sex; cin>>sex; sex ^= last;
			merge(l,r,sex);
		} else {
			if(!par.count(l) || !par.count(r) || getPar(l).F != getPar(r).F) {
				cout<<-1<<'\n';
				last = 1;
				continue;
			}
			cout<<((getPar(l).S) ^ (getPar(r).S))<<'\n';
			last = getPar(l).S ^ getPar(r).S;
		}
	}
    done;
}


