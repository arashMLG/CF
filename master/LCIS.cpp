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

const int N = 500 + 23;
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
int a[N],b[N];
pair<int,pii> dp[N][N];
map<int,int> mp;
pair<int,pii> ans = {0,{-1,-1}};
vector<int> javab;

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i = 0 ; i < n; i ++) cin>>a[i];
	cin>>m;
	for(int i = 0 ; i< m; i ++)  cin>>b[i];
	for(int i = 0 ; i< n; i++) {
		mp.clear();
		for(int j = 0 ; j< m ; j ++) {
			if(a[i] == b[j]) {
				dp[i][j] = {1,{-1,-1}};
				for(int k = i-1; k >= 0 ; k--){
					if(a[k] < a[i] && mp.count(a[k])) {
						dp[i][j] = max(dp[i][j], {dp[k][mp[a[k]]].F + 1, {k,mp[a[k]]}});
					}
				}
				ans=  max(ans,{dp[i][j].F,{i,j}});
			}
			mp[b[j]] = max(mp[b[j]],j);
		}
	}
	auto [x,y] = ans.S;
	while(x != -1) {
		javab.pb(a[x]);
		auto [xx,yy] = dp[x][y].S;
		debug(x,y);
		x= xx;
		y = yy;
	}
	cout<<sz(javab) << '\n';
	reverse(all(javab));
	for(int f: javab) cout<<f << ' ';
    done;
}

