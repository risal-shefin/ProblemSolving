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

const ll sz = 3e5 + 10, LN = 20;
ll a[sz], c[sz], neg[sz], pa[LN][sz], pre[sz];
vector <int> g[sz];

void add(ll j, ll p)
{
    pa[0][j] = p;

    for(int i=1; i<LN; i++) {
        if(pa[i-1][j] != -1) {
            pa[i][j] = pa[i-1][pa[i-1][j]];
        }
    }
}

ll kth(ll v, ll k)
{
    ll cur = v;

    for0(i, LN) {
        if((k>>i) & 1)
            cur = pa[i][cur];
    }

    return cur;
}

int main()
{
    fastio;

    ms(pa, -1);

    ll q;
    cin >> q >> a[0] >> c[0];
    pre[0] = a[0];

    for1(i, q) {
        ll op; cin >> op;

        if(op == 1) {
            ll p;
            cin >> p >> a[i] >> c[i];
            pre[i] = a[i] + pre[p];

            add(i, p);
        }
        else {
            ll v, w;
            cin >> v >> w;

            if(pre[v] <= neg[v]) {
                cout << 0 << " " << 0 << endl;
                continue;
            }
            else if(neg[v] != 0) {
                ll mn = min(w, pre[v]-neg[v]);
                neg[v] += mn;

                cout << mn << " " << mn*c[v] << endl;
                continue;
            }

            ll cur = v, num = 0;

            rep0(k, LN) {
                if(pa[k][cur] == -1)
                    continue;

                ll p = pa[k][cur];
                if(neg[p] == 0) {
                    cur = p;
                    num |= (1<<k);
                }
            }

            ll answ = 0, ansc = 0;

            if(cur != 0) {
                ll p = pa[0][cur];
                if(pre[p] > neg[p]) {
                    ll mn = min(w, pre[p] - neg[p]);
                    answ += mn, w -= mn, ansc = mn*c[p];
                    neg[p] += mn;
                }
            }

            while(w != 0 && num>=0) {
                ll p = kth(v, num);

                ll mn = min(w, a[p]);
                answ += mn, w -= mn, ansc += mn*c[p];
                neg[p] = mn;
                if(pa[0][p] != -1)
                    neg[p] += neg[ pa[0][p] ];

                num--;
            }
            //dbg(cur);
            //dbg(mp(pre[1], neg[1]));

            cout << answ << " " << ansc << endl;
        }
    }

    return 0;
}
