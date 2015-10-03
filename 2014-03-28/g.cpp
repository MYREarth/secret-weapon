#include <cstdio>
#include <cstring>
#include <cctype>
#include <utility>
#include <algorithm>
using namespace std;
const int base=10000000,p=15;
const char kind[][20]={"Nothing","One pair","Two pairs","Three of a kind","Straight","Flush","Full house","Four of a kind","Straight flush","Royal flush"};
struct card
{
    char value,suit;
    card(){}
    card(char *s)
    {
        if (isdigit(s[0]))
            value=s[0]-'0';
        else if (s[0]=='T')
            value=10;
        else if (s[0]=='J')
            value=11;
        else if (s[0]=='Q')
            value=12;
        else if (s[0]=='K')
            value=13;
        else
            value=14;
        if (s[1]=='S')
            suit=0;
        else if (s[1]=='C')
            suit=1;
        else if (s[1]=='D')
            suit=2;
        else
            suit=3;
    }
    card(int value,int suit):value(value),suit(suit){}
    int hash()
    {
        return(value-2);
    }
};
inline bool operator <(const card &a,const card &b)
{
    return(a.value<b.value || a.value==b.value && a.suit<b.suit);
}
inline bool operator ==(const card &a,const card &b)
{
    return(a.value==b.value && a.suit==b.suit);
}
struct hand
{
    card a[5];
    hand(const card &u,const card &v,const card &w,const card &x,const card &y)
    {
        a[0]=u,a[1]=v,a[2]=w,a[3]=x,a[4]=y;
    }
    bool small()
    {
        return(a[0].value==2 && a[1].value==3 && a[2].value==4 && a[3].value==5 && a[4].value==14);
    }
    bool flush()
    {
        for (int i=1;i<5;i++)
            if (a[i].suit!=a[0].suit)
                return(false);
        return(true);
    }
    bool straight()
    {
        for (int i=1;i<5;i++)
            if (a[i].value!=a[i-1].value+1)
                return(false);
        return(true);
    }
    int value()
    {
        if (small())
        {
            a[4].value=1;
            sort(a,a+5);
        }
        int c[20]={0};
        for (int i=0;i<5;i++)
            c[a[i].value]++;
        pair <int,int> b[5];
        int m=0;
        for (int i=1;i<=14;i++)
            if (c[i])
                b[m++]=make_pair(c[i],i);
        sort(b,b+m);
        reverse(b,b+m);
        int ret=0;
        for (int i=0;i<m;i++)
            ret=ret*p+b[i].second;
        bool f=flush(),s=straight();
        if (f && s && a[4].value==14)
            ret+=9*base;
        else if (f && s)
            ret+=8*base;
        else if (b[0].first==4)
            ret+=7*base;
        else if (b[0].first==3 && b[1].first==2)
            ret+=6*base;
        else if (f)
            ret+=5*base;
        else if (s)
            ret+=4*base;
        else if (b[0].first==3)
            ret+=3*base;
        else if (b[0].first==2 && b[1].first==2)
            ret+=2*base;
        else if (b[0].first==2)
            ret+=base;
        return(ret);
    }
};
card a[10][2];
int n,tot,N,value[10],cnt[10],f[2600000];
char buf[10];
card common[7],deck[60];
void del(const card &a)
{
    for (int i=0;i<N;i++)
        if (deck[i]==a)
        {
            for (int j=i+1;j<N;j++)
                deck[j-1]=deck[j];
            N--;
            break;
        }
}
int calc(card *b)
{
    card a[7];
    for (int i=0;i<7;i++)
        a[i]=b[i];
    sort(a,a+7);
    int ret=0;
    for (int i=0;i<=2;i++)
    {
        int u=a[i].hash();
        for (int j=i+1;j<=3;j++)
        {
            int v=u*13+a[j].hash();
            bool b=a[i].suit==a[j].suit;
            for (int k=j+1;k<=4;k++)
            {
                int w=v*13+a[k].hash();
                bool c=b&a[j].suit==a[k].suit;
                for (int l=k+1;l<=5;l++)
                {
                    int x=w*13+a[l].hash();
                    bool d=c&a[k].suit==a[l].suit;
                    for (int o=l+1;o<=6;o++)
                    {
                        int y=x*13+a[o].hash();
                        bool e=d&a[l].suit==a[o].suit;
                        if (f[y<<1|e]==0)
                            f[y<<1|e]=hand(a[i],a[j],a[k],a[l],a[o]).value();
                        ret=max(ret,f[y<<1|e]);
                    }
                }
            }
        }
    }
    return(ret);
}
int best()
{
    int id=max_element(value+1,value+n+1)-value;
    if (count(value+1,value+n+1,value[id])!=1)
        return(0);
    return(id);
}
void dfs(int dep,int first)
{
    if (dep==0)
    {
        for (int i=1;i<=n;i++)
        {
            common[5]=a[i][0];
            common[6]=a[i][1];
            value[i]=calc(common);
        }
        tot++;
        cnt[best()]++;
        return;
    }
    for (int i=first;i<=N-dep;i++)
    {
        common[5-dep]=deck[i];
        dfs(dep-1,i+1);
    }
}
int main()
{
    freopen("poker.in","r",stdin);
    freopen("poker.out","w",stdout);
    for (int i=2;i<=14;i++)
        for (int j=0;j<4;j++)
            deck[N++]=card(i,j);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        for (int j=0;j<2;j++)
        {
            scanf("%s",buf);
            a[i][j]=buf;
            del(a[i][j]);
        }
    dfs(5,0);
    printf("First bet\n");
    for (int i=1;i<=n;i++)
    {
        int p=__gcd(cnt[i],tot);
        printf("Player %d: %d/%d\n",i,cnt[i]/p,tot/p);
    }
    for (int i=0;i<3;i++)
    {
        scanf("%s",buf);
        common[i]=buf;
        del(common[i]);
    }
    tot=0;
    memset(cnt,0,sizeof(cnt));
    dfs(2,0);
    printf("Second bet\n");
    for (int i=1;i<=n;i++)
    {
        int p=__gcd(cnt[i],tot);
        printf("Player %d: %d/%d\n",i,cnt[i]/p,tot/p);
    }
    scanf("%s",buf);
    common[3]=buf;
    del(common[3]);
    tot=0;
    memset(cnt,0,sizeof(cnt));
    dfs(1,0);
    printf("Third bet\n");
    for (int i=1;i<=n;i++)
    {
        int p=__gcd(cnt[i],tot);
        printf("Player %d: %d/%d\n",i,cnt[i]/p,tot/p);
    }
    scanf("%s",buf);
    common[4]=buf;
    del(common[4]);
    dfs(0,0);
    int ans=best();
    if (ans==0)
        printf("No winner: Draw\n");
    else
        printf("Winner is Player %d, %s\n",ans,kind[value[ans]/base]);
}

