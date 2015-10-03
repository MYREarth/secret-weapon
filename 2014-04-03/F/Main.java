import java.math.*;
import java.io.*;
import java.util.*;

public class Main {
    boolean isPrime(int n) {
        for (int i = 2; i * i <= n; ++ i) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    long power(long a, int n) {
        long result = 1;
        while (n > 0) {
            n --;
            result *= a;
        }
        return result;
    }

    long[] extendedGCD(long a, long b) {
        if (b == 0) {
            return new long[]{a, 0};
        }
        long[] result = extendedGCD(b, a % b);
        //   b * x + (a - a / b * b) * y
        // = a * y + (x - a / b * y) * b
        return new long[]{result[1], result[0] - a / b * result[1]};
    }

    long inverse(BigInteger bigA, long m) {
        long a = bigA.remainder(BigInteger.valueOf(m)).longValue();
        long[] result = extendedGCD(a, m);
        return (result[0] % m + m) % m;
    }

    public void run() {
        int n = scanner.nextInt();
        int k = scanner.nextInt();
        if (n == 1) {
            System.out.println(power(2, k));
            System.out.println(2);
            return;
        }
        ArrayList <Integer> primes = new ArrayList <Integer>();
        for (int i = 0, p = 2; i < n; ++ i) {
            while (!isPrime(p)) {
                p ++;
            }
            primes.add(p ++);
        }
        BigInteger product = BigInteger.ONE;
        for (int i = 0; i < n; ++ i) {
            product = product.multiply(BigInteger.valueOf(power(primes.get(i), k)));
        }
        BigInteger result = BigInteger.ZERO;
        for (int i = 0; i < n; ++ i) {
            long modulo = power(primes.get(i), k);
            BigInteger semiProduct = product.divide(BigInteger.valueOf(modulo));
            result = result.add(semiProduct.multiply(BigInteger.valueOf(inverse(semiProduct, modulo))).multiply(product.subtract(BigInteger.valueOf(i)))).remainder(product);
        }
        System.out.println(result);
        for (int i = 0; i < n; ++ i) {
            System.out.println(primes.get(i));
        }
    }

    public static void main(String[] args) {
        new Main().run();
    }

    Scanner scanner;

    Main() {
        scanner = new Scanner(System.in);
    }
}
