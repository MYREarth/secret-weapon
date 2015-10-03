import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    long solve(long n, long a, long b, long m) {
        assert a >= 0;
        //long result = 0;
        //for (int i = 0; i < n; ++ i) {
        //    result += (a + b * i) / m;
        //}
        //return result;
        if (b == 0) {
            return n * (a / m);
        }
        if (a >= m) {
            return n * (a / m) + solve(n, a % m, b, m);
        }
        if (b >= m) {
            return (n - 1) * n / 2 * (b / m) + solve(n, a, b % m, m);
        }
        return solve((a + b * n) / m, (a + b * n) % m, m, b);
    }

    long work(long n, long a, long m, long b) {
        a %= m;
        if (n == 0) {
            return 0;
        }
        if (a == 0) {
            return n;
        }
        //long result = 0;
        //for (int i = 0; i < n; ++ i) {
        //    if ((a * i) % m < b) {
        //        result ++;
        //    }
        //}
        //return result;
        // k * m - 1 <= a * (n - 1)
        long maxK = (a * (n - 1) + 1) / m;
        long result = solve(maxK, a + b - 1, m, a) - solve(maxK, a - 1, m, a);
        // a * x >= maxK * m
        // x >= minX
        long minX = (maxK * m + a - 1) / a;
        // a * x < maxK * m + b
        // x < maxX
        long maxX = Math.min((maxK * m + a + b - 1) / a, n);
        return result + (maxX - minX);
        //// for i = 0..(n - 1) (a * i) mod m < b
        //b = Math.min(b, a * (n - 1) + 1);
        //// for j = 0..(b - 1) ([a * (n - 1) + m - j] / m)
        //return solve(b, a * (n - 1) + m - (b - 1), 1, m);
    }

    long doit(long k, long m, long n) {
        long result = 0;
        if (n >= k) {
            if (n >= 2 * k + 1) {
                result += k * m / n;
            } else {
                long b = n - k;
                result += work(k * m / n, k - b, k, b + 1);
            }
            if (k * m % n >= (k - (k * m / n) * n % k) % k + k) {
                result ++;
            }
        }
        return result;
    }

    public static void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    public void run() {
        assert doit(2, 6, 3) == 4;
        assert doit(4, 6, 5) == 3;
        Scanner scanner = new Scanner(System.in);
        long k = scanner.nextLong();
        long m = scanner.nextLong();
        long n = scanner.nextLong();
        System.out.println(doit(k, m, n));
    }
}
