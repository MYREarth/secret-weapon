import java.io.*;
import java.math.*;
import java.util.*;
public class Main {
    public static void main (String args[]) throws Exception {
        new Main().run();
    }

    BigInteger[] f;

    void run() throws Exception {
        Scanner in = new Scanner(new File("permutations.in"));
        PrintWriter out = new PrintWriter(new File("permutations.out"));
        n = in.nextInt();
        f = new BigInteger[n + 1];
        f[0] = BigInteger.ONE;
        for (int i = 1; i <= n; ++i) {
            f[i] = f[i - 1].multiply(BigInteger.valueOf(i));
        }
        int[] a = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = in.nextInt();
        }
        int[] b = new int[n];
        for (int i = 0; i < n; ++i) {
            b[i] = in.nextInt();
        }
        BigInteger ans = rank(b).subtract(rank(a)).add(isPermutation(b));
       out.println(ans);
        out.close();
    }

    int n;

    BigInteger rank(int[] a) {
        BigInteger ret = BigInteger.ZERO;
        boolean same = false;
        for (int i = 0; i < n && !same; ++i) {
            int cnt = a[i] - 1;
            for (int j = 0; j < i; ++j) {
                if (a[j] < a[i]) {
                    --cnt;
                }
                if (a[j] == a[i]) {
                    same = true;
                }
            }
            ret = ret.add(BigInteger.valueOf(cnt).multiply(f[n - i - 1]));
        }
        return ret;
    }

    BigInteger isPermutation(int[] a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (a[i] == a[j]) {
                    return BigInteger.ZERO;
                }
            }
        }
        return BigInteger.ONE;
    }
}
