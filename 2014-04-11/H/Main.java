import java.io.*;
import java.math.*;
import java.util.*;
public class Main
{
    static public void main(String args[]) throws Exception
    {
        new Main().run();
    }
    Main() throws Exception
    {
        reader=new BufferedReader(new FileReader(new File("transformations.in")));
    }
    BufferedReader reader;
    PrintWriter writer=new PrintWriter(System.out);
    StringTokenizer tokenizer=new StringTokenizer("");
    BigInteger four=BigInteger.valueOf(4),ten=BigInteger.TEN,zero=BigInteger.ZERO;
    void run() throws Exception
    {
        int T=nextInt();
        while (T-->0)
        {
            long x=nextLong();
            BigInteger n=BigInteger.valueOf(x);
            String ans="";
            while (n.compareTo(four)!=0)
                if (n.mod(ten).compareTo(zero)==0)
                {
                    n=n.divide(ten);
                    ans+="A";
                }
                else if (n.mod(ten).compareTo(four)==0)
                {
                    n=n.divide(ten);
                    ans+="B";
                }
                else
                {
                    n=n.shiftLeft(1);
                    ans+="C";
                }
            writer.println(new StringBuffer(ans).reverse().toString());
        }
        reader.close();
        writer.close();
    }
    int nextInt() throws Exception
    {
        return(Integer.parseInt(next()));
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
}

