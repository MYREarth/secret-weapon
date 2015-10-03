import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    public void run() {
        try {
            Scanner scanner = new Scanner(new File("apple.in"));
            int n = scanner.nextInt();
            int[] a = new int[n];
            int sum = 0;
            for (int i = 0; i < n; ++ i) {
                a[i] = scanner.nextInt();
                sum += a[i];
            }
            PrintWriter writer = new PrintWriter(new File("apple.out"));
            if (sum % 2 != 0) {
                writer.println(0);
            } else {
                sum /= 2;
                Arrays.sort(a);
                BigInteger[] ways = new BigInteger[sum + 1];
                Arrays.fill(ways, BigInteger.ZERO);
                ways[0] = BigInteger.ONE;
                int maxSum = 0;
                for (int i = 0; i < n; ++ i) {
                    maxSum += a[i];
                    maxSum = Math.min(maxSum, sum);
                    for (int j = maxSum; j >= a[i]; -- j) {
                        ways[j] = ways[j].add(ways[j - a[i]]);
                    }
                }
                writer.println(ways[sum].shiftRight(1));
            }
            writer.close();
        } catch (FileNotFoundException ex) {
        }
    }
}
