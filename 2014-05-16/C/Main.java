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
        BufferedReader reader=new BufferedReader(new FileReader(new File("radix.in")));
        PrintWriter writer=new PrintWriter(new File("radix.out"));
        BigInteger x=new BigInteger(reader.readLine());
        int n=x.bitLength();
        if (n==0)
            n=1;
        for (int i=n-1;i>=0;i--)
            writer.print(x.testBit(i)?1:0);
        writer.println();
        reader.close();
        writer.close();
    }
}

