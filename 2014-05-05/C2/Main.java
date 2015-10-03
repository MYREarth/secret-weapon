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
        BigInteger c[][]=new BigInteger[130][130];
        for (int i=0;i<=120;i++)
        {
            c[i][0]=c[i][i]=BigInteger.ONE;
            for (int j=1;j<i;j++)
                c[i][j]=c[i-1][j-1].add(c[i-1][j]);
        }
        Scanner in=new Scanner(new File("catalonian.in"));
        PrintWriter out=new PrintWriter(new File("catalonian.out"));
        while (true)
        {
            int n;
            n=in.nextInt();
            if (n==0)
                break;
            out.println(c[2*n][n].divide(BigInteger.valueOf(n+1)));
        }
        out.close();
    }
}

