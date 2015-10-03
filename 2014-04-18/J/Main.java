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
        Scanner in=new Scanner(System.in);
        BigDecimal x=in.nextBigDecimal();
        BigDecimal y=in.nextBigDecimal();
        System.out.println(x.divide(y,0,BigDecimal.ROUND_DOWN));
    }
}

