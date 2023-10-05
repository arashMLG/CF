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

const int N =5e5 + 23;
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

int n;
int a[N],b[N];
vector<int> c;
int ans[2];

void solve() {
	cin>>n;
	c.resize(2*n-1); iota(all(c),0);
	int sumo=0;
	for(int i = 0 ; i < 2*n-1 ; i++) {
		cin>>a[i]>>b[i]; sumo += b[i];
	}
	sort(all(c), [&] (int i,int j) {return a[i] < a[j];});
	debug(c);
	ans[0] = ans[1] =0;
	for(int i = 0 ; i < 2*n-1; i++) {
		ans[i&1] += b[c[i]];
	}
	cout<<"YES\n";
	if(ans[0] > ans[1]) {
		for(int i = 0; i < 2*n-1; i+=2) cout<<c[i]+1 << ' ';
		
	} else {
		debug(2*n-1);
		for(int i = 1 ;i< 2*n-1; i += 2) {
			cout<<c[i]+1 << ' ';
		}
		cout<<c[2*n-2]+1<< ' ';
	}
	cout<<'\n';
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	int t= 1;
	cin>>t;
	for(int i = 1; i <= t; i ++) {
		#ifdef LOCAL
			cout<<"\n------------------\n" << "test case: " <<  i<< endl;
		#endif
		solve();
		#ifdef LOCAL
			cout<<endl;
		#endif
	}
    done;
}

