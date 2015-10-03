import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    public void run() {
        BigInteger[] result = prepare(60);
        try {
            Scanner reader = new Scanner(new File("catalonian.in"));
            PrintWriter writer = new PrintWriter(new File("catalonian.out"));
            while (true) {
                int n = reader.nextInt();
                if (n == 0) {
                    break;
                }
                writer.println(result[n]);
            }
            writer.close();
        } catch (FileNotFoundException ex) {
        }
    }

    BigInteger[] prepare(int n) {
        BigInteger[] tree = new BigInteger[n + 1];
        BigInteger[] forest = new BigInteger[n + 1];
        Arrays.fill(tree,   BigInteger.ZERO);
        Arrays.fill(forest, BigInteger.ZERO);
        forest[0] = tree[0] = BigInteger.ONE;
        for (int i = 1; i <= n; ++ i) {
            BigInteger[] choose = new BigInteger[n + 1];
            choose[0] = BigInteger.ONE;
            for (int j = 1; j <= n; ++ j) {
                choose[j] = choose[j - 1].multiply(tree[i - 1].add(BigInteger.valueOf(j - 1))).divide(BigInteger.valueOf(j));
            }
            for (int j = n; j >= 0; -- j) {
                BigInteger result = BigInteger.ZERO;
                for (int k = 0; i * k <= j; ++ k) {
                    result = result.add(forest[j - i * k].multiply(choose[k]));
                }
                forest[j] = result;
            }
            choose = new BigInteger[n + 1];
            choose[0] = BigInteger.ONE;
            for (int j = 1; j <= n; ++ j) {
                choose[j] = choose[j - 1].multiply(forest[i].add(BigInteger.valueOf(j - 1))).divide(BigInteger.valueOf(j));
            }
            for (int j = n; j >= 0; -- j) {
                BigInteger result = BigInteger.ZERO;
                for (int k = 0; i * k <= j; ++ k) {
                    result = result.add(tree[j - i * k].multiply(choose[k]));
                }
                tree[j] = result;
            }
        }
        return forest;
    }

    public static void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }
}
