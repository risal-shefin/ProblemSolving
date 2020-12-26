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
#define eps 1e-6

const ll sz = 2e5 + 10;

struct pnt {
    double x, y;
} ara[sz];

inline ll clockwise(pnt a, pnt b, pnt c)
{
    double ret = (a.x*b.y+b.x*c.y+c.x*a.y) - (a.y*b.x+b.y*c.x+c.y*a.x);

    if(ret < 0)
        return 1;
    else if(abs(ret) <= eps)
        return -1;
    else
        return 0;
}

inline double sq(double x) {return x*x;}

inline double dist(pnt a, pnt b)
{
    return sqrtl(sq(a.x-b.x) + sq(a.y-b.y));
}

int main()
{
    ll n, h;
    cin >> n >> h;

    for1(i, n)
        sd(ara[i].x), sd(ara[i].y);

    pnt eye = {ara[n].x, ara[n].y + h};

    double ans = dist(ara[n-1], ara[n]);

    for(ll i = n-1; i >= 2;) {

        ll stop = -1, linear = 0;

        for(ll j = i-1; j >= 1; j--) {

            ll got = clockwise(eye, ara[i], ara[j]);

            if(got == -1) {
                stop = j, linear = 1;
                break;
            }
            else if(got == 1) {
                stop = j;
                break;
            }
        }
        if(stop == -1)
            break;

        if(linear) {
            if(stop == i-1) ans += dist(ara[stop], ara[stop+1]);
            i = stop;
            continue;
        }

        double dy1 = eye.y-ara[i].y, dx1 = eye.x-ara[i].x;
        double dy3 = ara[stop+1].y-ara[stop].y, dx3 = ara[stop+1].x-ara[stop].x;

        double ch = ara[stop+1].x*dy3 - ara[stop+1].y*dx3;
        double ce = eye.x*dy1 - eye.y*dx1;

        double X, Y;

        if(abs(dy3) <= eps) {
            Y = ara[stop].y;
            X = (ce+dx1*Y)/dy1;
        }
        else {
            Y = (ce*dy3-dy1*ch) / (dx3*dy1-dx1*dy3);
            X = (ch+dx3*Y)/dy3;
        }

        ans += dist(ara[stop], {X, Y});

        i = stop;
    }

    cout << setprecision(7) << fixed << ans << EL;

    return 0;
}
