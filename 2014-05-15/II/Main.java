import java.io.*;
import java.math.*;
import java.util.*;
public class Main
{
    static public void main(String args[])
    {
        new Main().run();
    }
    void run()
    {
        Scanner in=new Scanner(System.in);
        long p=in.nextLong();
        if (p%4==3)
            System.out.println("NO");
        else
        {
            System.out.println("YES");
            long x=solve(p-1,p);
            Gauss ans=gcd(new Gauss(p,0),new Gauss(x,1));
            System.out.println(Math.abs(ans.a)+" "+Math.abs(ans.b));
        }
    }
    long solve(long a,long p)
    {
        if ((p+1)%4==0)
            return(power(a,(p+1)/4,p));
        else
        {
            long t,h,b,pb=-1;
            long tmp[]=calcH(p);
            t=tmp[0];
            h=tmp[1];
            if (t>=2)
            {
                Random rng=new Random();
                while (true)
                {
                    b=rng.nextLong()%(p-2)+2;
                    if (power(b,p/2,p)==p-1)
                        break;
                }
                pb=power(b,h,p);
            }
            long s=power(a,h/2,p);
            for (int step=2;step<=t;step++)
            {
                long ss=mulmod(mulmod(s,s,p),a,p);
                for (int i=0;i<t-step;i++)
                    ss=mulmod(ss,ss,p);
                if (ss+1==p)
                    s=mulmod(ss,pb,p);
                pb=mulmod(pb,pb,p);
            }
            return(mulmod(s,a,p));
        }
    }
    long power(long x,long y,long mod)
    {
        long ret=1;
        for (;y>0;y>>=1)
        {
            if (y%2==1)
                ret=mulmod(ret,x,mod);
            x=mulmod(x,x,mod);
        }
        return(ret);
    }
    long mulmod(long x,long y,long mod)
    {
        long ret=0;
        for (;y>0;y>>=1)
        {
            if (y%2==1)
                ret=(ret+x)%mod;
            x=(x+x)%mod;
        }
        return(ret);
    }
    long []calcH(long p)
    {
        long ret[]=new long[2];
        long tmp=p-1;
        for (ret[0]=0;(tmp&1)==0;tmp/=2)
            ret[0]++;
        ret[1]=tmp;
        return(ret);
    }
    Gauss gcd(Gauss a,Gauss b)
    {
        if (b.zero())
            return(a);
        return(gcd(b,a.mod(b)));
    }
    BigInteger quos(BigInteger a,BigInteger n)
    {
        return(a.subtract(a.mod(n)).divide(n));
    }
    class Gauss
    {
        long a,b;
        Gauss(long a,long b)
        {
            this.a=a;
            this.b=b;
        }
        boolean zero()
        {
            return(a==0 && b==0);
        }
        Gauss mod(Gauss x)
        {
            BigInteger w0=BigInteger.valueOf(a),w1=BigInteger.valueOf(b);
            BigInteger z0=BigInteger.valueOf(x.a),z1=BigInteger.valueOf(x.b);
            BigInteger n=z0.multiply(z0).add(z1.multiply(z1));
            BigInteger u0=quos(w0.multiply(z0).add(w1.multiply(z1)),n);
            BigInteger u1=quos(w1.multiply(z0).subtract(w0.multiply(z1)),n);
            BigInteger p=w0.subtract(z0.multiply(u0)).add(z1.multiply(u1));
            BigInteger q=w1.subtract(z0.multiply(u1)).subtract(z1.multiply(u0));
            return(new Gauss(p.longValue(),q.longValue()));
        }
    }
}

