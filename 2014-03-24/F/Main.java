import java.io.*;
import java.math.*;
import java.util.*;
public class Main
{
    public static void main(String args[])
    {
        new Main().run();
    }
    void run()
    {
        BigInteger c[]=new BigInteger[101];
        c[0]=BigInteger.ONE;
        for (int i=1;i<=100;i++)
        {
            c[i]=BigInteger.ZERO;
            for (int j=0;j<i;j++)
                c[i]=c[i].add(c[j].multiply(c[i-j-1]));
        }
        Scanner in=new Scanner(System.in);
        while (true)
        {
            int n=in.nextInt();
            if (n==-1)
                break;
            System.out.println(c[n]);
        }
    }
}

