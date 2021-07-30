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

const ll sz = 2e5 + 10;
char s[sz];
ll pre[3][sz], cnt[3][sz][3];

int main()
{
    ll n, q;
    cin >> n >> q;
    scanf("%s", s);

    for0(i, n) {
        ll now = s[i] - 'a';
        pre[now][i] = 1;

        ll rem = i%3;
        cnt[now][i][rem] = 1;

        if(i != 0) {
            for0(j, 3)
                pre[j][i] += pre[j][i-1];

            for0(j, 3)
                for0(k, 3)
                    cnt[j][i][k] += cnt[j][i-1][k];
        }
    }

    while(q--) {
        ll l, r;
        sl(l), sl(r);
        l--, r--;

        ll a = pre[0][r], b = pre[1][r], c = pre[2][r];
        if(l != 0) a -= pre[0][l-1], b -= pre[1][l-1], c -= pre[2][l-1];

        ll tmp[] = {a, b, c};
        ll ans = inf;
        vector <ll> v = {0, 1, 2};

        do {
            ll tot = 0;
            for0(i, v.size()) {
                ll now = v[i];

                ll ase = cnt[now][r][i];
                if(l != 0) ase -= cnt[now][l-1][i];

                tot += (tmp[now] - ase);
                //dbg(mp(tmp[now], ase));
            }

            ans = min(ans, tot);

        } while(next_permutation(all(v)));

        pf("%lld\n", ans);
    }

    return 0;
}
