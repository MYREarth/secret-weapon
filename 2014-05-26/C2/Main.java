import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    public void run() {
        //try {
            int m = 10007;
            int[] count = new int[m];
            for (int a = 2; a <= 150; ++ a) {
                // a^n mod (1e5 + 3)
                int p = 1;
                for (int n = 1; n <= 150; ++ n) {
                    p = (int)((long)p * a % m);
                    count[p] ++;
                }
                System.err.println(p);
            }
            int maxBucket = 0;
            for (int i = 0; i < m; ++ i) {
                maxBucket = Math.max(maxBucket, count[i]);
            }
            System.err.println(maxBucket);
            //Scanner scanner = new Scanner(new File("apple.in"));
            //PrintWriter writer = new PrintWriter(new File("apple.out"));
            //writer.close();
        //} catch (FileNotFoundException ex) {
        //}
    }
}
