import java.io.*;
import java.math.*;
import java.util.*;
public class Main
{
    static public void main(String args[]) throws Exception
    {
        new Main().run();
    }
    void run() throws Exception
    {
        BigInteger exact[][]=new BigInteger[61][61];
        BigInteger move[]=new BigInteger[61],figure[]=new BigInteger[61];
        BigInteger f[][]=new BigInteger[61][61],g[][][]=new BigInteger[61][61][61];
        for (int i=0;i<=60;i++)
        {
            move[i]=figure[i]=BigInteger.ZERO;
            for (int j=0;j<=60;j++)
            {
                exact[i][j]=f[i][j]=BigInteger.ZERO;
                for (int k=0;k<=60;k++)
                    g[i][j][k]=BigInteger.ZERO;
            }
        }
        for (int i=0;i<=60;i++)
            f[0][i]=g[0][i][0]=BigInteger.ONE;
        for (int i=1;i<=60;i++)
        {
            figure[i]=f[i-1][i-1];
            for (int j=1;j<=60;j++)
                for (int k=1;k<=i;k++)
                    for (int x=0;j*x<=i && x<=k;x++)
                    {
                        BigInteger tmp=power(figure[j],x).multiply(C(BigInteger.valueOf(k),x));
                        g[i][j][k]=g[i][j][k].add(g[i-j*x][j-1][k-x].multiply(tmp));
                    }
            for (int j=1;j<=i;j++)
            {
                exact[i][j]=g[i][i][j];
                for (int k=2;k<=j;k++)
                    if (i%k==0 && j%k==0)
                        exact[i][j]=exact[i][j].subtract(exact[i/k][j/k].multiply(BigInteger.valueOf(j/k)));
                assert(exact[i][j].mod(BigInteger.valueOf(j)).signum()==0);
                exact[i][j]=exact[i][j].divide(BigInteger.valueOf(j));
            }
            for (int j=1;j<=i;j++)
                if (i%j==0)
                    for (int k=1;k<=i;k++)
                        move[i]=move[i].add(exact[i/j][k]);
            for (int j=1;j<=60;j++)
                for (int x=0;j*x<=i;x++)
                    f[i][j]=f[i][j].add(f[i-j*x][j-1].multiply(C(move[j].add(BigInteger.valueOf(x-1)),x)));
        }
        Scanner in=new Scanner(new File("abstract.in"));
        PrintWriter out=new PrintWriter(new File("abstract.out"));
        int cas=0;
        while (true)
        {
            int n=in.nextInt();
            if (n==0)
                break;
            out.println("Case "+(++cas)+": "+move[n]);
        }
        out.close();
    }
    BigInteger C(BigInteger n,int m)
    {
        BigInteger ret=BigInteger.ONE;
        for (int i=0;i<m;i++)
            ret=ret.multiply(n.subtract(BigInteger.valueOf(i)));
        for (int i=1;i<=m;i++)
            ret=ret.divide(BigInteger.valueOf(i));
        return(ret);
    }
    BigInteger power(BigInteger n,int m)
    {
        BigInteger ret=BigInteger.ONE;
        for (int i=1;i<=m;i++)
            ret=ret.multiply(n);
        return(ret);
    }
}

