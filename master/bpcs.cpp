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

const int N = 1e6 + 23;
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

int n;
int a[N];
pii wow[1<<LOG];

pii add(pii x,int y) {
	if(y == -1) return x;
	if(y == x.F || y == x.S) return x;
	if(y > x.S) {
		x.F = x.S;
		x.S = y;
	} else if(y > x.F) {
		x.F = y;
	}
	return x;
}

pii add(pii x,pii y) {
	x= add(x,y.F);
	x= add(x,y.S);
	return x;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	for(int i = 0 ; i< (1<<LOG) ; i ++) wow[i] = {-1,-1};
	cin>>n;
	for(int i = 0 ; i < n ; i++) {
		cin>>a[i];
		wow[a[i]] = add(wow[a[i]],i);
	}
	for(int i = 0 ;i < LOG; i ++)
		for(int mask = 0 ; mask < (1<<LOG) ; mask ++)
			if((mask >> i)&1)
				wow[mask ^ (1<<i)] = add(wow[mask ^ (1<<i)] , wow[mask]);
	
	int ans =0;
	for(int i = LOG-1; i >= 0 ; i--) {
		ans |= (1 << i);
		bool x = false;
		for(int j = 0 ; j < n ; j++) {
			int num = ans & (~a[j]);
			if(wow[num].F > j)
				x = true;
		}
		if(!x) ans ^= (1<<i);
	}
	cout<<ans;
    done;
}

