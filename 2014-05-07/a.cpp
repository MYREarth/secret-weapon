#include <cstdio>
#include <string>
using namespace std;
void read(string &s)
{
    char buf[110];
    scanf("%s",buf);
    s=buf;
}
char vertical(char ch)
{
    switch (ch)
    {
    case 'd':
        return('b');
    case 'b':
        return('d');
    case 'q':
        return('p');
    case 'p':
        return('q');
    case 's':
        return('z');
    case 'z':
        return('s');
    case 'i':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
        return(ch);
    default:
        return('.');
    }
}
string vertical(const string &s)
{
    string ret;
    for (int i=s.size()-1;i>=0;i--)
        ret+=vertical(s[i]);
    return(ret);
}
char horizontal(char ch)
{
    switch (ch)
    {
    case 'p':
        return('b');
    case 'b':
        return('p');
    case 'd':
        return('q');
    case 'q':
        return('d');
    case 's':
        return('z');
    case 'z':
        return('s');
    case 'w':
        return('m');
    case 'm':
        return('w');
    case 'u':
        return('n');
    case 'n':
        return('u');
    case 'c':
    case 'o':
    case 'x':
        return(ch);
    default:
        return('.');
    }
}
string horizontal(const string &s)
{
    string ret;
    for (int i=0;i<s.size();i++)
        ret+=horizontal(s[i]);
    return(ret);
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        string s,t;
        read(s);
        read(t);
        printf("%s\n",s==t || s==vertical(t) || s==horizontal(t) || s==vertical(horizontal(t))?"YES":"NO");
    }
    return(0);
}

