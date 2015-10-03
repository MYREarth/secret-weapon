import java.io.*;
import java.math.*;
import java.util.*;
public class Main
{
    static public void main(String args[]) throws Exception
    {
        new Main().run();
    }
    BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer tokenizer=new StringTokenizer("");
    PrintWriter writer=new PrintWriter(System.out);
    void run() throws Exception
    {
        int n=90;
        BigInteger fib[]=new BigInteger[n];
        fib[0]=BigInteger.ONE;
        fib[1]=BigInteger.ZERO;
        for (int i=2;i<n;i++)
            fib[i]=fib[i-1].add(fib[i-2]);
        BigInteger a[]=new BigInteger[n],b[]=new BigInteger[n];
        for (int i=1;i<n;i++)
        {
            a[i]=fib[i-1];
            b[i]=fib[i];
        }
        long T=nextLong();
        while (T-->0)
        {
            BigInteger R=BigInteger.valueOf(nextLong()),S=BigInteger.valueOf(nextLong());
            BigInteger k1=null,k2=null;
            for (int i=1;i<n;i++)
                for (int j=i+1;j<n;j++)
                {
                    BigInteger tmp=a[i].multiply(b[j]).subtract(b[i].multiply(a[j]));
                    if (tmp.signum()==0)
                        continue;
                    BigInteger x=R.multiply(b[j]).subtract(S.multiply(b[i]));
                    BigInteger y=S.multiply(a[i]).subtract(R.multiply(a[j]));
                    if (x.mod(tmp.abs()).signum()!=0 || y.mod(tmp.abs()).signum()!=0)
                        continue;
                    x=x.divide(tmp);
                    y=y.divide(tmp);
                    if (x.signum()>0 && y.signum()>0 && x.compareTo(y)<=0 && better(x,y,k1,k2))
                    {
                        k1=x;
                        k2=y;
                    }
                }
            writer.println(k1+" "+k2);
        }
        reader.close();
        writer.close();
    }
    long nextLong() throws Exception
    {
        return(Long.parseLong(next()));
    }
    String next() throws Exception
    {
        while (!tokenizer.hasMoreTokens())
            tokenizer=new StringTokenizer(reader.readLine());
        return(tokenizer.nextToken());
    }
    boolean better(BigInteger a,BigInteger b,BigInteger c,BigInteger d)
    {
        return(c==null || a.compareTo(c)<0 || a.compareTo(c)==0 && b.compareTo(d)<0);
    }
}

