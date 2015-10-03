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
        int n=in.nextInt();
        long a[]=new long[n+1],b[]=new long[n+1];
        for (int i=1;i<=n;i++)
        {
            a[i]=in.nextLong();
            a[i]--;
        }
        for (int i=1;i<=n;i++)
        {
            b[i]=in.nextLong();
            b[i]--;
        }
        BigInteger ans[]=new BigInteger[2];
        ans[0]=BigInteger.ONE;
        ans[1]=BigInteger.ZERO;
        for (int i=1;i<=n;i++)
        {
            long one=dp(b[i])-dp(a[i]-1);
            long zero=b[i]-a[i]+1-one;
            BigInteger tmp[]=new BigInteger[2];
            tmp[0]=ans[0].multiply(BigInteger.valueOf(zero)).add(ans[1].multiply(BigInteger.valueOf(one)));
            tmp[1]=ans[0].multiply(BigInteger.valueOf(one)).add(ans[1].multiply(BigInteger.valueOf(zero)));
            ans[0]=tmp[0];
            ans[1]=tmp[1];
        }
        System.out.println(ans[1]);
    }
    long dp(long x)
    {
        if (x<0)
            return(0);
        int n=63,a[]=new int[64];
        long f[][]=new long[64][2];
        long g[][]=new long[64][2];
        for (int i=n;i>0;i--)
        {
            a[i]=(int)(x&1);
            x>>=1;
        }
        g[0][0]=1;
        for (int i=1;i<=n;i++)
            for (int j=0;j<=1;j++)
                for (int k=0;k<=1;k++)
                {
                    f[i][j^k]+=f[i-1][j];
                    if (k<a[i])
                        f[i][j^k]+=g[i-1][j];
                    if (k==a[i])
                        g[i][j^k]+=g[i-1][j];
                }
        return(f[n][1]+g[n][1]);
    }
}

