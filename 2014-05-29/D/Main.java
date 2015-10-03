import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        BigInteger n = scanner.nextBigInteger();
        BigInteger m = scanner.nextBigInteger();
        BigInteger p = scanner.nextBigInteger();
        System.out.println(solve(n, m).mod(p));
    }

    BigInteger solve(BigInteger n, BigInteger m) {
        if (n.compareTo(m) > 0) {
            return solve(m, n);
        }
        BigInteger result = BigInteger.ZERO;
        result = result.add(n.multiply(BigInteger.valueOf(3)));
        result = result.subtract(n.multiply(m).multiply(BigInteger.valueOf(2)));
        result = result.add(n.multiply(n));
        result = result.add(n.multiply(n).multiply(n).multiply(m).multiply(BigInteger.valueOf(8)));
        result = result.subtract(n.multiply(n).multiply(n).multiply(n).multiply(BigInteger.valueOf(4)));
        result = result.divide(BigInteger.valueOf(6));
        result = result.add((n.add(BigInteger.ONE).multiply(n).shiftRight(1)).multiply(m.add(BigInteger.ONE).multiply(m).shiftRight(1)));
        return result;
    }
}
