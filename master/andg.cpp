#include<bits/stdc++.h>
#ifdef LOCAL
#include "Essentials/algo/debug.h"
#else
#define debug(...) 69
#endif
using namespace std;


#include <bits/functexcept.h>
#include <iosfwd>
#include <bits/cxxabi_forced.h>
#include <bits/functional_hash.h>

#pragma push_macro("__SIZEOF_LONG__")
#pragma push_macro("__cplusplus")
#define __SIZEOF_LONG__ __SIZEOF_LONG_LONG__
#define unsigned unsigned long
#define __cplusplus 201102L

#define __builtin_popcountl __builtin_popcountll
#define __builtin_ctzl __builtin_ctzll

#pragma pop_macro("__cplusplus")
#pragma pop_macro("__SIZEOF_LONG__")
#undef unsigned
#undef __builtin_popcountl
#undef __builtin_ctzl

//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

//https://quera.org/profile/4dykhk

typedef long long     ll;
typedef long double   ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll>   pll;

const int N = 8388608 + 23;
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

int n,m;
int hah;
bool mark[N];
bool f[N];

void dfs(int v,int id=0){
	mark[v+ hah*id] = true;
	if(id==0 && !f[v]) return;
	if(id==0) {
		int u = v + hah;
		if(!mark[u])
			dfs(v,1);
	} else {
		// case one
		int u;
		for(int i =0 ; i< n ; i++) {
			if(((v>>i) & 1) == 0) {
				u = v | (1 <<i);
				if(!mark[u+hah])
					dfs(u,1);
			}
		}
		
		u = hah - 1- v;
		if(!mark[u])
			dfs(u,0);
	}
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	hah =(1<<n);
	int ans=0;
	for(int i = 0 ;i < m ; i++) {
		int x; cin>>x;
		f[x] = true;
	}
	for(int i = 0 ; i < (1 <<n); i ++){
		if(f[i] && !mark[i]) {
			dfs(i);
			ans++;	
		}
	}
	cout<<ans << '\n';
    done;
}
