// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define sl(n) scanf("%lld", &n)
#define si(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define inf (1LL << 61)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; ++i)
#define for0(i, stop) for(ll i = 0; i < stop; ++i)
#define rep1(i, start) for(ll i = start; i >= 1; --i)
#define rep0(i, start) for(ll i = (start-1); i >= 0; --i)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

// === DEBUG MACRO STARTS HERE === //
#ifndef ONLINE_JUDGE
#define DEBUG
#define SYS_COL system("COLOR")
#endif

int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; \
                cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":" \
                <<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value,
            Ostream&>::type operator<<(Ostream& os,  const Cont& v) {
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
#else
#define dbg(x)
#endif
// === DEBUG MACRO ENDS HERE === //

#define ff first
#define ss second

const int sz = 1e5 + 10, block = 41, LCM = 60;

struct info {
    int cst, nxt;
} val[sz/block+10][60];

int a[sz], n;

void calc(int b)
{
    int start = b*block, stop = min(n-1, (b+1)*block-1);

    for(int t = 0; t < LCM; ++t) {
        int cur = t, cst = 0;

        for(int j = start; j <= stop; ++j) {
            if(cur % a[j] == 0) ++cur, ++cst;
            ++cur, ++cst;

            if(cur >= LCM) cur -= LCM;
        }
        val[b][t] = {cst, cur};
    }
}

int query(int l, int r)
{
    int lb = l/block, rb = r/block, cur = 0, ret = 0;

    if(lb == rb) {
        for(int i = l; i <= r; ++i) {
            if(cur % a[i] == 0) ++cur, ++ret;

            ++cur, ++ret;
            if(cur >= LCM) cur -= LCM;
        }
        return ret;
    }

    int stop = (lb+1)*block;
    for(int i = l; i < stop; ++i) {
        if(cur % a[i] == 0) ++cur, ++ret;

        ++cur, ++ret;
        if(cur >= LCM) cur -= LCM;
    }

    for(int i = lb+1; i < rb; ++i) {
        info &got = val[i][cur];
        cur = got.nxt, ret += got.cst;
    }

    for(int i = rb*block; i <= r; ++i) {
        if(cur % a[i] == 0) ++cur, ++ret;

        ++cur, ++ret;
        if(cur >= LCM) cur -= LCM;
    }

    return ret;
}

int main()
{
    fastio;

    cin >> n;
    for0(i, n) cin >> a[i];

    int lim = (n-1)/block;
    for(int i = 0; i <= lim; i++) calc(i);

    int q; cin >> q;
    while(q--) {
        char ch; int x, y;
        cin >> ch >> x >> y;

        if(ch == 'A') {
            x--, y -= 2;
            cout << query(x, y) << EL;
        }
        else {
            x--;
            a[x] = y;
            calc(x/block);
        }
    }

    return 0;
}

