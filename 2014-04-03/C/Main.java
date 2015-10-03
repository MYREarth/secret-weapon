import java.io.*;
import java.math.*;
import java.util.*;
public class Main
{
    public static void main(String args[])
    {
        new Main().run();
    }
    BigInteger calc(int n,int m,Polynomial a,Polynomial s)
    {
        if (n+1<m)
            return(BigInteger.ZERO);
        int l=0,r=n,ans=-1;
        while (l<=r)
        {
            int mid=l+r>>1;
            BigInteger now=a.apply(mid);
            if (s.apply(mid).add(now.multiply(BigInteger.valueOf(n-mid))).compareTo(now.multiply(BigInteger.valueOf(m)))>=0)
            {
                ans=mid;
                l=mid+1;
            }
            else
                r=mid-1;
        }
        BigInteger sigma=s.apply(ans);
        return(sigma.divide(BigInteger.valueOf(m-n+ans)));
    }
    void run()
    {
        Scanner in=new Scanner(System.in);
        int T=in.nextInt();
        while (T-->0)
        {
            int n=in.nextInt(),m=in.nextInt(),K=in.nextInt();
            BigInteger a0=in.nextBigInteger(),c[]=new BigInteger[K+1];
            for (int i=K;i>=0;i--)
                c[i]=in.nextBigInteger();
            Polynomial f[]=init(K,a0,c);
            System.out.println(calc(n,m,f[0],f[1]));
        }
    }
    BigInteger apply(int K,BigInteger c[],int x)
    {
        BigInteger ret=BigInteger.ZERO;
        for (int i=K;i>=1;i--)
            ret=ret.add(c[i]).multiply(BigInteger.valueOf(x));
        return(ret.add(c[0]));
    }
    Polynomial[] init(int K,BigInteger a0,BigInteger c[])
    {
        BigInteger a[]=new BigInteger[K+3];
        a[0]=a0;
        for (int i=1;i<K+3;i++)
            a[i]=a[i-1].add(apply(K,c,i));
        BigInteger s[]=new BigInteger[K+3];
        s[0]=a[0];
        for (int i=1;i<K+3;i++)
            s[i]=s[i-1].add(a[i]);
        Polynomial ret[]=new Polynomial[2];
        ret[0]=lagrange(K+1,a);
        ret[1]=lagrange(K+2,s);
        return(ret);
    }
    Polynomial lagrange(int K,BigInteger s[])
    {
        Polynomial ret=new Polynomial();
        for (int i=0;i<=K;i++)
        {
            Polynomial now=new Polynomial(s[i]);
            for (int j=0;j<=K;j++)
            {
                if (i==j)
                    continue;
                now=now.multiply(new Polynomial(BigInteger.valueOf(-j),BigInteger.ONE));
            }
            for (int j=0;j<=K;j++)
            {
                if (i==j)
                    continue;
                now=now.divide(BigInteger.valueOf(i-j));
            }
            ret=ret.add(now);
        }
        return(ret);
    }
    class Polynomial
    {
        int n;
        Fraction a[];
        Polynomial()
        {
            init(0);
        }
        Polynomial(BigInteger a0)
        {
            init(0);
            a[0]=new Fraction(a0);
        }
        Polynomial(BigInteger a0,BigInteger a1)
        {
            init(1);
            a[0]=new Fraction(a0);
            a[1]=new Fraction(a1);
        }
        void init(int m)
        {
            n=m;
            a=new Fraction[n+1];
            for (int i=0;i<=n;i++)
                a[i]=new Fraction(BigInteger.ZERO);
        }
        Polynomial add(Polynomial b)
        {
            Polynomial ret=new Polynomial();
            ret.init(Math.max(n,b.n));
            for (int i=0;i<=ret.n;i++)
            {
                if (i<=n)
                    ret.a[i]=ret.a[i].add(a[i]);
                if (i<=b.n)
                    ret.a[i]=ret.a[i].add(b.a[i]);
            }
            return(ret);
        }
        Polynomial multiply(Polynomial b)
        {
            Polynomial ret=new Polynomial();
            ret.init(n+b.n);
            for (int i=0;i<=n;i++)
                for (int j=0;j<=b.n;j++)
                    ret.a[i+j]=ret.a[i+j].add(a[i].multiply(b.a[j]));
            return(ret);
        }
        Polynomial divide(BigInteger b)
        {
            Polynomial ret=new Polynomial();
            ret.init(n);
            for (int i=0;i<=n;i++)
                ret.a[i]=a[i].multiply(new Fraction(BigInteger.ONE,b));
            return(ret);
        }
        BigInteger apply(int x0)
        {
            BigInteger x=BigInteger.valueOf(x0);
            Fraction ret=new Fraction(BigInteger.ZERO);
            for (int i=n;i>=1;i--)
                ret=ret.add(a[i]).multiply(new Fraction(x));
            return(ret.add(a[0]).u);
        }
    }
    class Fraction
    {
        BigInteger u,v;
        Fraction(BigInteger x)
        {
            u=x;
            v=BigInteger.ONE;
        }
        Fraction(BigInteger x,BigInteger y)
        {
            BigInteger p=x.gcd(y);
            x=x.divide(p);
            y=y.divide(p);
            if (y.signum()<0)
            {
                x=x.negate();
                y=y.negate();
            }
            u=x;
            v=y;
        }
        Fraction add(Fraction b)
        {
            return(new Fraction(u.multiply(b.v).add(v.multiply(b.u)),v.multiply(b.v)));
        }
        Fraction multiply(Fraction b)
        {
            return(new Fraction(u.multiply(b.u),v.multiply(b.v)));
        }
    }
}

