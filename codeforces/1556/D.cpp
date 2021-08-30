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

const ll sz = 1e4 + 10;
ll ara[sz];

inline ll ask(ll x, ll y, bool f)
{
    if(f)
        cout << "or " << x << " " << y << endl;
    else
        cout << "and " << x << " " << y << endl;

    ll ret; cin>>ret;
    return ret;
}

inline bool find_val(ll prv, ll _or, ll _and, ll b)
{
    if((_and >> b) & 1)
        return 1;
    if(!((_or>>b) & 1))
        return 0;

    return !((prv>>b)&1);
}

int main()
{
    fastio;

    ll n, k;
    cin >> n >> k;

    ll or1 = ask(1, 2, 1), or2 = ask(2, 3, 1), or3 = ask(1, 3, 1);
    ll and1 = ask(1, 2, 0), and2 = ask(2, 3, 0), and3 = ask(1, 3, 0);

    rep0(b, 30) {
        bool zero = 0, one = 0;

        if((or1>>b) & 1) {

            if( ((and1>>b) & 1) || ((and3>>b) & 1))
                one = 1;
            else {
                if((or3>>b) & 1) {

                    if((or2>>b) & 1)
                        zero = 1;
                    else
                        one = 1;
                }
                else
                    zero = 1;
            }
        }
        else
            zero = 1;

        if(one)
            ara[1] = (ara[1] << 1) | 1;
        else
            ara[1] <<= 1;
    }

    for(ll i = 2; i <= n; i++) {

        ll _or, _and;
        if(i==2) _or = or1, _and = and1;
        else if(i==3) _or = or2, _and = and2;
        else {
            _or = ask(i-1, i, 1);
            _and = ask(i-1, i, 0);
        }

        rep0(b, 30) {
            bool got = find_val(ara[i-1], _or, _and, b);

            if(got) ara[i] = (ara[i] << 1) | 1;
            else ara[i] <<= 1;
        }
    }

    sort(ara+1, ara+n+1);

    cout << "finish " << ara[k] << endl;

    return 0;
}
