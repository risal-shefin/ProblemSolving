#include <bits/stdc++.h>

using namespace std;

#define eps 1e-15
double eqarea, th1, a, b;
int h;

double bsearch(double starth, double endh)

{
    int cnt = 100;
    double ansh;
    while(cnt--) {
        double midh = (starth + endh) / 2.0;
        b = a - (midh + midh) / tan(th1);
        double tmpar = 0.5 * (a + b) * midh;
        if(abs(eqarea - tmpar) <= eps) {
            ansh = midh;
        }
        if(tmpar < eqarea)
            starth = midh;
        else
            endh = midh;
    }

    return ansh;
}

int main()

{
    int n;
    scanf("%d %d", &n, &h);
    double area = 0.5 * 1 * h;
    eqarea = (area) / (n * 1.0);
    th1 = atan(h / 0.5);
    a = 1;
    n--;
    double dh = h;
    int counter = -1;
    vector <double> st;
    while(n--) {
        double ansh;
        ansh = bsearch(0, dh);
        dh -= ansh;
        a = b;
        st.push_back(dh);
        counter++;
    }

    cout << fixed << setprecision(15) << st[counter];
    for(int i = counter - 1; i >= 0; i--) {
        printf(" ");
        cout << fixed << setprecision(15) << st[i];
    }
    printf("\n");
    return 0;
}
