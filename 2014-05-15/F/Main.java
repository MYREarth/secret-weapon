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
        BigDecimal S=in.nextBigDecimal(),R=BigDecimal.ZERO;
        int n=in.nextInt(),p=in.nextInt(),ans[]=new int[n];
        BigDecimal rate=BigDecimal.valueOf(p).divide(BigDecimal.valueOf(100));
        for (int i=1;i<=n;i++)
            if ((n-i)*p>100)
            {
                ans[i-1]=100;
                S=S.multiply(rate.add(BigDecimal.ONE));
            }
            else
            {
                ans[i-1]=0;
                R=R.add(S.multiply(rate));
            }
        System.out.println(R.setScale(2,BigDecimal.ROUND_DOWN));
        for (int i=0;i<n;i++)
        {
            if (i>0)
                System.out.print(" ");
            System.out.print(ans[i]);
        }
        System.out.println();
    }
}

