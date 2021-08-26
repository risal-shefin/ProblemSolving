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

ll cnt[10], idx, p[2009], yo;
bool chk[10009];
string s, ans;

bool isPrime(ll n)
{
    if(n == 0) return 0;

    for(ll i = 0; p[i]*p[i] <= n && i < idx; i++)
        if(n % p[i] == 0)
            return 1;

    return 0;
}

void solve(ll pos, ll num)
{
    if(yo < num) return;

    if(pos == s.size()) {
        string tmp = to_string(num);

        if((ans.empty() || tmp.size() < ans.size()) && isPrime(num)) {
            //dbg(num);
            yo = num;
            ans = tmp;
            return;
        }
        return;
    }

    solve(pos+1, num);
    solve(pos+1, num*10 + (s[pos] - '0'));
}

int main()
{
    fastio;

    idx = 0;
    for(ll i = 2; i <= 10000; i++) {
        if(!chk[i]) {
            for(ll j = i*i; j <= 10000; j += i)
                chk[j] = 1;

            p[idx++] = i;
        }
    }

    ll t;
    cin >> t;

    while(t--) {
        ll n; cin>>n;
        cin >> s;

        bool got = 0;

        ms(cnt, 0);
        for(char &ch : s) {
            ll x = ch - '0';
            if(x != 2 && x != 3 && x != 5 && x != 7) {
                cout << "1\n" << x << EL;
                got = 1;
                break;
            }
            cnt[ch-'0']++;
        }
        if(got) continue;

        if(cnt[1] > 0) {
            cout << "1\n1\n";
            continue;
        }

        for1(i, 9) {
            if(cnt[i] > 1) {
                cout << "2\n" << i << i << EL;
                got = 1;
                break;
            }
        }
        if(got) continue;

        yo = inf;
        ans = "";
        solve(0, 0);

        cout << ans.size() << EL;
        cout << ans << EL;
    }

    return 0;
}
