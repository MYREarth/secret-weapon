#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
const char name[][10]={"Pre","In","Post"};
struct tree
{
    int root,l[26],r[26];
    tree():root(-1)
    {
        memset(l,-1,sizeof(l));
        memset(r,-1,sizeof(r));
    }
    string pre(int x)
    {
        if (x==-1)
            return("");
        return(char(x+'A')+pre(l[x])+pre(r[x]));
    }
    string in(int x)
    {
        if (x==-1)
            return("");
        return(in(l[x])+char(x+'A')+in(r[x]));
    }
    string post(int x)
    {
        if (x==-1)
            return("");
        return(post(l[x])+post(r[x])+char(x+'A'));
    }
};
char buf[30];
int lq[6],b[3][2],a[3][26];
vector <tree> pool[10000000];
map <ll,int > M;
ll encode(int id0,int l0,int r0,int id1,int l1,int r1,int id2,int l2,int r2)
{
    int p[3]={id0,id1,id2};
    int l[3]={l0,l1,l2};
    int r[3]={r0,r1,r2};
    ll ret=0;
    for (int i=0;i<3;i++)
    {
        ret=ret*10+p[i]+1;
        if (p[i]==-1)
            l[i]=r[i]=0;
    }
    for (int i=0;i<3;i++)
        ret=ret*100+l[i];
    for (int i=0;i<3;i++)
        ret=ret*100+r[i];
    return(ret);
}
int idx,vis[26];
bool check(int id0,int l0,int r0,int id1,int l1,int r1)
{
    assert(r0-l0==r1-l1);
    idx++;
    for (int i=l0;i<=r0;i++)
        vis[a[id0][i]]=idx;
    for (int i=l1;i<=r1;i++)
        if (vis[a[id1][i]]!=idx)
            return(false);
    return(true);
}
bool same(int id0,int l0,int r0,int id1,int l1,int r1)
{
    assert(r0-l0==r1-l1);
    int len=r0-l0+1;
    for (int i=0;i<len;i++)
        if (a[id0][l0+i]!=a[id1][l1+i])
            return(false);
    return(true);
}
vector <tree> fuck(int id0,int l0,int r0,int id1,int l1,int r1,int id2,int l2,int r2,int kind)
{
    vector <tree> solve(int id0,int l0,int r0,int id1,int l1,int r1,int id2,int l2,int r2);
    int id[3]={id0,id1,id2};
    int l[3]={l0,l1,l2};
    int r[3]={r0,r1,r2};
    vector <tree> ret;
    for (int i=0;i<3;i++)
    {
        if (id[i]==-1)
            continue;
        for (int j=i+1;j<3;j++)
        {
            if (id[j]==-1)
                continue;
            assert(r[i]-l[i]==r[j]-l[j]);
            if (b[i][kind]==b[j][kind] && !same(id[i],l[i],r[i],id[j],l[j],r[j]))
                return(ret);
            if (b[i][kind]!=b[j][kind] && !check(id[i],l[i],r[i],id[j],l[j],r[j]))
                return(ret);
        }
    }
    id0=id1=id2=-1;
    for (int i=0;i<3;i++)
    {
        if (id[i]==-1)
            continue;
        if (b[i][kind]==0)
            id0=id[i],l0=l[i],r0=r[i];
        else if (b[i][kind]==1)
            id1=id[i],l1=l[i],r1=r[i];
        else
            id2=id[i],l2=l[i],r2=r[i];
    }
    return(solve(id0,l0,r0,id1,l1,r1,id2,l2,r2));
}
tree merge(int root,const tree &L,const tree &R)
{
    tree ret;
    for (int i=0;i<26;i++)
    {
        if (L.l[i]!=-1)
            ret.l[i]=L.l[i];
        if (L.r[i]!=-1)
            ret.r[i]=L.r[i];
        if (R.l[i]!=-1)
            ret.l[i]=R.l[i];
        if (R.r[i]!=-1)
            ret.r[i]=R.r[i];
    }
    ret.l[root]=L.root;
    ret.r[root]=R.root;
    ret.root=root;
    return(ret);
}
vector <tree> solve(int id0,int l0,int r0,int id1,int l1,int r1,int id2,int l2,int r2)
{
    ll tmp=encode(id0,l0,r0,id1,l1,r1,id2,l2,r2);
    if (M.count(tmp))
        return(pool[M[tmp]]);
    vector <tree> ret;
    int cnt=(id0==-1)+(id1==-1)+(id2==-1);
    if (id0!=-1 && l0>r0 || id1!=-1 && l1>r1 || id2!=-1 && l2>r2)
        ret.push_back(tree());
    else if (cnt==2)
    {
        int len,root;
        vector <tree> L,R;
        if (id0!=-1)
        {
            len=r0-l0;
            root=a[id0][l0];
            for (int k=0;k<=len;k++)
            {
                L=fuck(id0,l0+1,l0+k,-1,-1,-1,-1,-1,-1,0);
                R=fuck(id0,l0+k+1,r0,-1,-1,-1,-1,-1,-1,1);
                if (!L.empty() && !R.empty())
                    for (int i=0;i<L.size();i++)
                        for (int j=0;j<R.size();j++)
                            ret.push_back(merge(root,L[i],R[j]));
            }
        }
        else if (id1!=-1)
            for (int k=l1;k<=r1;k++)
            {
                root=a[id1][k];
                L=fuck(-1,-1,-1,id1,l1,k-1,-1,-1,-1,0);
                R=fuck(-1,-1,-1,id1,k+1,r1,-1,-1,-1,1);
                if (!L.empty() && !R.empty())
                    for (int i=0;i<L.size();i++)
                        for (int j=0;j<R.size();j++)
                            ret.push_back(merge(root,L[i],R[j]));
            }
        else
        {
            len=r2-l2;
            root=a[id2][r2];
            for (int k=0;k<=len;k++)
            {
                L=fuck(-1,-1,-1,-1,-1,-1,id2,l2,l2+k-1,0);
                R=fuck(-1,-1,-1,-1,-1,-1,id2,l2+k,r2-1,1);
                if (!L.empty() && !R.empty())
                    for (int i=0;i<L.size();i++)
                        for (int j=0;j<R.size();j++)
                            ret.push_back(merge(root,L[i],R[j]));
            }
        }
    }
    else if (id1!=-1)
    {
        int root;
        if (id0!=-1)
            root=a[id0][l0];
        else
            root=a[id2][r2];
        int pos=-1;
        for (int i=l1;i<=r1;i++)
            if (a[id1][i]==root)
            {
                pos=i;
                break;
            }
        int len=pos-l1;
        if (pos!=-1 && (id0==-1 || a[id0][l0]==root) && (id2==-1 || a[id2][r2]==root))
        {
            vector <tree> L=fuck(id0,l0+1,l0+len,id1,l1,pos-1,id2,l2,l2+len-1,0);
            vector <tree> R=fuck(id0,l0+len+1,r0,id1,pos+1,r1,id2,l2+len,r2-1,1);
            if (!L.empty() && !R.empty())
                for (int i=0;i<L.size();i++)
                    for (int j=0;j<R.size();j++)
                        ret.push_back(merge(root,L[i],R[j]));
        }
    }
    else if (a[id0][l0]==a[id2][r2])
    {
        int len=r0-l0,root=a[id0][l0];
        for (int k=0;k<=len;k++)
        {
            vector <tree> L=fuck(id0,l0+1,l0+k,-1,-1,-1,id2,l2,l2+k-1,0);
            vector <tree> R=fuck(id0,l0+k+1,r0,-1,-1,-1,id2,l2+k,r2-1,1);
            if (!L.empty() && !R.empty())
                for (int i=0;i<L.size();i++)
                    for (int j=0;j<R.size();j++)
                        ret.push_back(merge(root,L[i],R[j]));
        }
    }
    int now=M.size();
    pool[now]=ret;
    M[tmp]=now;
    return(ret);
}
vector <string> pre,in,post;
inline bool cmp(int x,int y)
{
    return(pre[x]<pre[y]);
}
vector <int> c;
bool first=true;
int tot=0;
void calc(int n)
{
    b[0][0]=lq[0],b[0][1]=lq[1];
    b[1][0]=lq[2],b[1][1]=lq[3];
    b[2][0]=lq[4],b[2][1]=lq[5];
    M.clear();
    vector <tree> ans=solve(0,0,n-1,1,0,n-1,2,0,n-1);
    if (ans.empty())
        return;
    if (!first)
        printf("\n");
    first=false;
    for (int i=0;i<6;i++)
        printf("%s%c",name[lq[i]],i==5?'\n':' ');
    pre.resize(ans.size());
    in.resize(ans.size());
    post.resize(ans.size());
    c.resize(ans.size());
    for (int i=0;i<ans.size();i++)
    {
        pre[i]=ans[i].pre(ans[i].root);
        in[i]=ans[i].in(ans[i].root);
        post[i]=ans[i].post(ans[i].root);
        c[i]=i;
    }
    sort(c.begin(),c.end(),cmp);
    for (int i=0;i<c.size();i++)
    {
        int x=c[i];
        printf("%s\n%s\n%s\n",pre[x].c_str(),in[x].c_str(),post[x].c_str());
    }
}
int main()
{
    int n;
    for (int i=0;i<3;i++)
    {
        scanf("%s",buf);
        n=strlen(buf);
        for (int j=0;j<n;j++)
            a[i][j]=buf[j]-'A';
    }
    lq[0]=lq[1]=0;
    lq[2]=lq[3]=1;
    lq[4]=lq[5]=2;
    while (1)
    {
        calc(n);
        if (!next_permutation(lq,lq+6))
            break;
    }
    return(0);
}

