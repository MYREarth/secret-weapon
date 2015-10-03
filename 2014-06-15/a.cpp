#include <cstdio>
char s[20];
bool a[52][52];
int b[10];
void get()
{
    for (int i=0;i<8;i+=2)
    {
        if (s[i]=='0')
        {
            b[i>>1]=-1;
            continue;
        }
        b[i>>1]=s[i]-'A';
        if (s[i+1]=='+')
            b[i>>1]+=26;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",s);
        get();
        for (int j=0;j<4;j++)
            for (int k=0;k<4;k++)
            {
                if (j==k || b[j]==-1 || b[k]==-1)
                    continue;
                a[b[j]<26?b[j]+26:b[j]-26][b[k]]=true;
            }
    }
    for (int k=0;k<52;k++)
        for (int i=0;i<52;i++)
            for (int j=0;j<52;j++)
                if (a[i][k] && a[k][j])
                    a[i][j]=true;
    bool flag=false;
    for (int i=0;i<52;i++)
        if (a[i][i])
        {
            flag=true;
            break;
        }
    printf("%sbounded\n",flag?"un":"");
    return(0);
}

