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

// === Debug macro starts here ===
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
// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 2e5;
string s;
vector <ll> lst;
ll n, m, p, h, ara[sz], cnt[(1<<15)];

ll solve(ll msk)
{
    vector <int> bt;
    for0(i, m) {
        if((msk>>i) & 1)
            bt.pb(i);
    }

    ms(cnt, 0);

    for0(i, n) {
        ll nmsk = 0;

        for(int j = 0; j < bt.size(); j++) {
            if((ara[i] >> bt[j]) & 1)
                nmsk |= (1<<j);
        }
        cnt[nmsk]++;
    }

    ll lim = 1<<bt.size();

    for0(mask, lim) {

        // iterate over all the subsets of the mask
        for(ll i = mask; i > 0; i = (i-1) & mask){
            if(i != mask)
                cnt[i] += cnt[mask];
        }
    }

    ll h = n/2 + (n&1), mx = 0, ret = 0;

    for0(mask, lim) {
        if(cnt[mask] >= h) {
            ll btcnt = __builtin_popcountll(mask);

            if(btcnt > mx)
                mx = btcnt, ret = mask;
        }
    }

    return ret;
}

int main()
{
    fastio;

    cin >> n >> m >> p;

    for0(i, n) {
        cin >> s;

        ll msk = 0;

        for0(j, s.size()) {
            if(s[j] == '1')
                msk |= (1LL<<j);
        }
        ara[i] = msk;
        lst.pb(msk);
    }
    srand(time(NULL));
    random_shuffle(all(lst));

    ll lim = 1<<p, mx = 0, ans = 0;

    for(ll i = 0; i < min((ll)50, (ll)lst.size()); i++) {

        ll got = solve(lst[i]);
        ll btcnt = __builtin_popcountll(got);

        if(btcnt > mx) {
            mx = btcnt;
            ll now = 0;

            for(ll j = 0, k = 0; j < m; j++) {
                if((lst[i] >> j) & 1) {

                    if((got>>k) & 1)
                        now |= (1LL << j);

                    k++;
                }
            }

            ans = now;
        }
    }

    for0(i, m) {
        if((ans>>i) & 1)
            cout << "1";
        else
            cout << "0";
    }
    cout << EL;

    return 0;
}

