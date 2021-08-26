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
#ifdef LOCALXOX
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

const ll sz = 3e5 + 10, yo = 3e5+1;
char s[sz];
ll suf[sz];
set <int> lst[sz+yo];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, q;
        sl(n), sl(q);
        scanf("%s", s+1);

        suf[n+1] = 0;

        rep1(i, n) {
            ll cur = (s[i] == '+')? 1 : -1;
            if(i%2 == 0) cur *= -1;

            suf[i] = cur + suf[i+1];
            lst[ suf[i] + yo].insert(i);

            //dbg(mp(i, suf[i]));
        }

        while(q--) {
            ll l, r;
            sl(l), sl(r);

            ll sum = suf[l] - suf[r+1];

            if(sum == 0) pf("0\n");
            else if(abs(sum) & 1) {
                pf("1\n");

                ll need = (sum/2+1);
                if(sum < 0) need = sum/2 - 1;
                //if(l % 2 == 0) sum *= -1, need *= -1;

                need += suf[r+1];
                //dbg(need);

                auto it = --lst[need+yo].upper_bound(r);
                pf("%d\n", *it);
            }
            else {
                pf("2\n");

                ll need1 = sum/2+1, need2 = 1;
                if(sum < 0) need1 = sum/2 - 1, need2 = -1;
                //if(l % 2 == 0) sum *= -1, need1 *= -1, need2 *= -1;

                need1 += suf[r+1], need2 += suf[r+1];

                auto it1 = --lst[need1+yo].upper_bound(r);
                auto it2 = --lst[need2+yo].upper_bound(r);

                if(*it1 > *it2) swap(it1, it2);

                pf("%d %d\n", *it1, *it2);
            }
        }

        for(ll i = yo-n; i <= yo+n; i++) lst[i].clear();
    }

    return 0;
}

