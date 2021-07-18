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

const ll sz = 1e5 + 10;
ll cnt[26];

int main()
{
    fastio;

    ll t;
    cin >> t;

    while(t--) {
        string s;
        cin >> s;

        set <char>tmp;
        for(char &ch : s) tmp.insert(ch);

        if(tmp.size() == 1) {
            cout << s << EL;
            continue;
        }

        ms(cnt, 0);
        for(char &ch : s) cnt[ch-'a']++;

        ll mnc, mn = inf;
        for0(i, 26) {
            if(cnt[i] != 0 && cnt[i] < mn)
                mn = cnt[i], mnc = i;
        }

        if(mn == 1) {
            cout << (char)(mnc+'a');
            cnt[mnc] = 0;

            for0(i, 26) {
                while(cnt[i] > 0) {
                    cout << (char)(i+'a');
                    cnt[i]--;
                }
            }
            cout << EL;
            continue;
        }

        for0(i, 26) {
            if(cnt[i] != 0) {
                mnc = i;
                break;
            }
        }

        if(cnt[mnc] <= 3 || (cnt[mnc]-1)*2 <= s.size()) {
            cout << (char)(mnc+'a');
            cnt[mnc]--;

            while(cnt[mnc] > 0) {
                cout << (char)(mnc+'a');
                cnt[mnc]--;

                for0(i, 26) {
                    if(cnt[i] > 0 && i != mnc) {
                        cout << (char)(i+'a');
                        cnt[i]--;
                        break;
                    }
                }
            }

            for0(i, 26) {
                while(cnt[i] > 0) {
                    cout << (char)(i+'a');
                    cnt[i]--;
                }
            }
            cout << EL;
        }
        else if(tmp.size() == 2) {
            cout << (char)(mnc+'a');
            cnt[mnc]--;

            for0(i, 26) {
                while(cnt[i] > 0 && i != mnc) {
                    cout << (char)(i+'a');
                    cnt[i]--;
                }
            }

            while(cnt[mnc] > 0) {
                cout << (char)(mnc+'a');
                cnt[mnc]--;
            }
            cout << EL;
        }
        else {
            cout << (char)(mnc+'a');
            cnt[mnc]--;

            ll other;
            for0(i, 26) {
                if(cnt[i] > 0 && i != mnc) {
                    cout << (char)(i+'a');
                    cnt[i]--, other = i;
                    break;
                }
            }

            while(cnt[mnc] > 0) {
                cout << (char)(mnc+'a');
                cnt[mnc]--;
            }

            for0(i, 26) {
                if(cnt[i] > 0 && i != other) {
                    cout << (char)(i+'a');
                    cnt[i]--;
                    break;
                }
            }

            for0(i, 26) {
                while(cnt[i] > 0) {
                    cout << (char)(i+'a');
                    cnt[i]--;
                }
            }
            cout << EL;
        }
    }

    return 0;
}
