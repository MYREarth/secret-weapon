#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <sstream>
using namespace std;
char tmp[1000000],buf[1000000];
int main()
{
    int T;
    scanf("%d",&T);
    gets(buf);
    while (T--)
    {
        gets(buf);
        stringstream sin(buf);
        vector <string> a;
        string name;
        while (sin>>name)
            a.push_back(name);
        set <string> S;
        while (1)
        {
            gets(buf);
            if (strcmp(buf,"what does the fox say?")==0)
                break;
            sscanf(buf,"%*s%*s%s",tmp);
            S.insert(tmp);
        }
        bool first=true;
        for (int i=0;i<a.size();i++)
        {
            if (S.count(a[i]))
                continue;
            if (!first)
                printf(" ");
            first=false;
            printf("%s",a[i].c_str());
        }
        printf("\n");
    }
    return(0);
}

