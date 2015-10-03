import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    Main() {
        reader = new BufferedReader(new InputStreamReader(System.in));
        tokenizer = new StringTokenizer("");
    }

    public static void main(String[] args) {
        new Main().run();
    }

    public void run() {
        try {
            BigInteger n = new BigInteger(next());
            int m = nextInt();
            int[] a = new int[m + 1];
            for (int i = 0; i <= m; ++ i) {
                a[i] = nextInt();
            }
            PriorityQueue <Long> heap = new PriorityQueue <Long>();
            long result = 0;
            for (int i = 0; i <= m; ++ i) {
                if (n.testBit(i)) {
                    result += a[i];
                    heap.offer((long)a[i]);
                }
            }
            while (heap.size() > 1) {
                long x = heap.poll();
                long y = heap.poll();
                result += x + y;
                heap.offer(x + y);
            }
            System.out.println(result);
        } catch (IOException ex) {
        }
    }

    String next() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    Integer nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    BufferedReader reader;
    StringTokenizer tokenizer;
}
