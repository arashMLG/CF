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

const int N = 5e2 + 23;
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const int inf = 2e9;

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
int dp[N][N];

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n;
    for(int i = 0 ; i< n ; i++)  {
    	char c; cin>>c; a[i] = c- 'a'+1;
    }
    
    for(int i = 0; i < n ; i++) {
    	dp[i][i] = 1;
    }
    for(int len =2; len <= n; len ++) {
    	for(int i = 0 ; i+len -1 < n ; i ++) {
    		int l = i;
    		int r = i + len-1;
    		dp[l][r] = dp[l+1][r] +1;
    		for(int j = i +1; j <= r ; j ++) {
    			if(a[i] == a[j] ) {
    				dp[l][r] = min(dp[l][r], dp[l+1][j-1] + dp[j][r]);
    			}
    		}
    	}
    }
    cout<<dp[0][n-1];
    done;
}

