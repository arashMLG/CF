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

const int N = 300 + 23;
const int sq = 450;
const ll mod = 1e9+7; // 998244353
const int LOG = 23;
const ll INF = 1e9+23;

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

struct Matrix{
    int n, m;
    int M[N][N];
    Matrix(int _n = N, int _m = N, ll num = 0){
        n = _n, m = _m;
        if(num == -1){
            for(int i = 0; i < n; i ++){
                for(int j = 0; j < m; j ++){
                    M[i][j] = (i == j ? 0 : -INF);
                }
            }
        }
        else{
            for(int i = 0; i < n; i ++){
                for(int j = 0; j < m; j ++){
                    M[i][j] = num;
                }
            }
        }
    }
    void Print(bool f = 0){
        cout << "=======N.N=======\n";
        if(f) cout << "Size : " << n << ' ' << m << '\n';
        for(int i = 0; i < n; i ++, cout << '\n'){
            for(int j = 0; j < m; j ++) cout << M[i][j] << ' ';
        }
        cout << "=======N.N=======\n";
    }
    Matrix operator * (const Matrix &T){
        Matrix R = Matrix(n, T.m, -INF);
        if(m != T.n){
            cout << "Cannot * Matrices !" << '\n'; return R;
        }
        for(int i = 0; i < n; i ++){
            for(int k = 0; k < m; k ++){
                for(int j = 0; j < T.m; j ++){
                    if(M[i][k] > -INF && T.M[k][j] > -INF)
                        R.M[i][j] = max(R.M[i][j], M[i][k] + T.M[k][j]);
                }
            }
        }
        return R;
    }
    Matrix operator ^ (const ll &t){
        Matrix R = Matrix(n, n, -1);
        if(n != m){
            cout << "Cannot ^ Matrix !" << '\n'; return R;
        }
        if(t == 0) return R;
        Matrix T = Matrix(n, m);
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < m; j ++){
                T.M[i][j] = M[i][j];
            }
        }
        ll p = t;
        while(p){
            if(p & 1LL) R = (R * T);
            T = (T * T), p /= 2;
        }
        return R;
    }
};

int n,m;
Matrix adj(N,N,-1);
Matrix b(N,N);

bool check(int x) {
	b = adj^x;
	for(int i = 1; i<= n ; i++) if(b.M[i][i] > 0) return true;
	return false;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i = 0 ; i < m ; i++) {
		int v,u,x,y; cin>>v>>u>>x>>y;
		adj.M[v][u] = x;
		adj.M[u][v] = y;
	}
	int l = 0,r= N;
	while(r-l>1) {
		int mid=(l+r)/2;
		if(check(mid)) r= mid;
		else l = mid;
	}
	cout<< r % N;
    done;
}

