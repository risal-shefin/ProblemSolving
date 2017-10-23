#include<bits/stdc++.h>
using namespace std;
set < char > s;
int main()
{
    char x[10002];
    int i;
    scanf(" %[^\n]",x);
    for(i=0;i<strlen(x);i++)
    {
        if(x[i] >= 97 && x[i] <= 122)
        {
            s.insert(x[i]);
        }
    }
    cout << s.size() << endl;
}

