#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
unsigned getip(const string &s)
{
    unsigned a,b,c,d;
    sscanf(s.c_str(),"%u.%u.%u.%u",&a,&b,&c,&d);
    return(a<<24|b<<16|c<<8|d);
}
struct packet
{
    string in,out,proto,spt,dpt;
    unsigned src,dst;
    int len;
    packet(stringstream &sin)
    {
        string tmp;
        while (sin>>tmp)
        {
            int pos=tmp.find("=");
            update(tmp.substr(0,pos),tmp.substr(pos+1));
        }
    }
    void update(const string &name,const string &value)
    {
        if (name=="IN")
            in=value;
        else if (name=="OUT")
            out=value;
        else if (name=="SRC")
            src=getip(value);
        else if (name=="DST")
            dst=getip(value);
        else if (name=="PROTO")
            proto=value;
        else if (name=="SPT")
            spt=value;
        else if (name=="DPT")
            dpt=value;
        else
            len=atoi(value.c_str());
    }
};
struct rule
{
    string in,out,proto,spt,dpt,target;
    unsigned src,dst;
    int pkts,bytes,smask,dmask;
    bool snega,dnega,sall,dall;
    rule(stringstream &sin)
    {
        pkts=bytes=0;
        sall=dall=true;
        string op;
        while (sin>>op)
        {
            string tmp;
            if (op=="-i")
                sin>>in;
            else if (op=="-o")
                sin>>out;
            else if (op=="-p")
                sin>>proto;
            else if (op=="--sport")
                sin>>spt;
            else if (op=="--dport")
                sin>>dpt;
            else if (op=="-s")
            {
                sall=snega=false;
                sin>>tmp;
                if (tmp=="!")
                {
                    snega=true;
                    sin>>tmp;
                }
                get_ip(src,smask,tmp);
            }
            else if (op=="-d")
            {
                dall=dnega=false;
                sin>>tmp;
                if (tmp=="!")
                {
                    dnega=true;
                    sin>>tmp;
                }
                get_ip(dst,dmask,tmp);
            }
            else
                sin>>target;
        }
    }
    void get_ip(unsigned &net,int &mask,const string &s)
    {
        int pos=s.find("/");
        if (pos==string::npos)
        {
            net=getip(s);
            mask=32;
        }
        else
        {
            net=getip(s.substr(0,pos));
            mask=atoi(s.substr(pos+1).c_str());
        }
    }
    void reset()
    {
        pkts=bytes=0;
    }
    bool accept(const packet &now)
    {
        if (!same(in,now.in) || !same(out,now.out) || !same(proto,now.proto) || !same(spt,now.spt) || !same(dpt,now.dpt))
            return(false);
        if (!sall && !same_ip(src,smask,snega,now.src) || !dall && !same_ip(dst,dmask,dnega,now.dst))
            return(false);
        return(true);
    }
    bool same(const string &a,const string &b)
    {
        return(a.empty() || a==b);
    }
    bool same_ip(unsigned net,int mask,bool nega,unsigned ip)
    {
        unsigned tmp=~0U;
        for (int i=0;i<32-mask;i++)
            tmp^=1U<<i;
        ip&=tmp;
        return(nega?net!=ip:net==ip);
    }
    void print()
    {
        printf("%8d%8d%8s%8s%8s%8s",pkts,bytes,target.c_str(),f(proto),f(in),f(out));
        printf("%22s%22s%8s%8s\n",g(sall,src,smask,snega),g(dall,dst,dmask,dnega),f(spt),f(dpt));
    }
    const char *f(const string &s)
    {
        return(s.empty()?"any":s.c_str());
    }
    const char *g(bool all,unsigned net,int mask,bool nega)
    {
        if (all)
            return("anywhere");
        stringstream sout;
        if (nega)
            sout<<"! ";
        sout<<(net>>24)<<"."<<(net>>16&255)<<"."<<(net>>8&255)<<"."<<(net&255);
        if (mask!=32)
            sout<<"/"<<mask;
        return(sout.str().c_str());
    }
};
struct chain
{
    string policy;
    int pkts,bytes;
    vector <rule> rules;
    chain()
    {
        clear();
    }
    void clear()
    {
        policy="ACCEPT";
        pkts=bytes=0;
        rules.clear();
    }
    void set(const string &s)
    {
        policy=s;
        pkts=bytes=0;
    }
    void reset()
    {
        pkts=bytes=0;
        for (int i=0;i<rules.size();i++)
            rules[i].reset();
    }
    void apply(const packet &now)
    {
        for (int i=0;i<rules.size();i++)
            if (rules[i].accept(now))
            {
                rules[i].pkts++;
                rules[i].bytes+=now.len;
                if (rules[i].target=="RETURN")
                {
                    pkts++;
                    bytes+=now.len;
                }
                if (rules[i].target!="LOG")
                    return;
            }
        pkts++;
        bytes+=now.len;
    }
    void print(const string &name)
    {
        printf("Chain %s (policy %s %d packets, %d bytes)\n",name.c_str(),policy.c_str(),pkts,bytes);
        printf("%8s%8s%8s%8s%8s%8s%22s%22s%8s%8s\n","pkts","bytes","target","proto","in","out","source","destination","sport","dport");
        for (int i=0;i<rules.size();i++)
            rules[i].print();
    }
};
chain input,output,forward;
chain &get_chain(const packet &now)
{
    if (now.out.empty())
        return(input);
    if (now.in.empty())
        return(output);
    return(forward);
}
chain &get_chain_by_name(const string &s)
{
    if (s=="INPUT")
        return(input);
    else if (s=="OUTPUT")
        return(output);
    return(forward);
}
char buf[1000000];
int main()
{
    freopen("iptables.in","r",stdin);
    freopen("iptables.out","w",stdout);
    while (gets(buf))
    {
        stringstream sin(buf);
        string op;
        if (!(sin>>op))
            continue;
        if (op=="recv")
        {
            packet now(sin);
            get_chain(now).apply(now);
        }
        else
        {
            sin>>op;
            if (op=="-vL")
            {
                input.print("INPUT");
                output.print("OUTPUT");
                forward.print("FORWARD");
                printf("\n");
            }
            else
            {
                string name;
                sin>>name;
                chain &now=get_chain_by_name(name);
                if (op=="-F")
                    now.clear();
                else if (op=="-P")
                {
                    string target;
                    sin>>target;
                    now.set(target);
                }
                else if (op=="-Z")
                    now.reset();
                else
                    now.rules.push_back(rule(sin));
            }
        }
    }
    return(0);
}

