import java.util.Arrays;
import java.util.Scanner;
import java.io.*;
import java.math.BigInteger;

public class Main {
    public static void main(String[] args) throws Exception {
        new Main().run();
    }

    public void run() throws Exception {
        Scanner scanner = new Scanner(new File("rsa.in"));
        PrintWriter writer = new PrintWriter(new File("rsa.out"));
        BigInteger m = scanner.nextBigInteger();
        BigInteger a = scanner.nextBigInteger();
        BigInteger b = scanner.nextBigInteger();
        BigInteger p = a.subtract(b).add(BigInteger.ONE).multiply(getInverse(BigInteger.valueOf(3), m)).remainder(m).add(m).remainder(m);
        if (p.equals(BigInteger.ONE) && a.equals(BigInteger.ONE)) {
            writer.println(-1);
        } else {
            int ppp = 2;
            while (ppp < 1000 && !m.remainder(BigInteger.valueOf(ppp)).equals(BigInteger.ZERO)) {
                ppp ++;
            }
            if (ppp < 1000) {
                BigInteger pp = BigInteger.valueOf(ppp);
                BigInteger qq = m.divide(pp);
                BigInteger d = getInverse(BigInteger.valueOf(3), pp.subtract(BigInteger.ONE).multiply(qq.subtract(BigInteger.ONE)));
                writer.println(power(a, d, m));
            } else {
                BigInteger c = !p.equals(BigInteger.ONE) ? p : a;
                BigInteger cc = c.subtract(BigInteger.ONE).remainder(m).add(m).remainder(m);
                if (cc.gcd(m).equals(BigInteger.ONE)) {
                    writer.println(p.subtract(a).multiply(getInverse(cc, m)).remainder(m).add(m).remainder(m));
                } else {
                    BigInteger pp = cc.gcd(m);
                    BigInteger qq = m.divide(pp);
                    BigInteger d = getInverse(BigInteger.valueOf(3), pp.subtract(BigInteger.ONE).multiply(qq.subtract(BigInteger.ONE)));
                    writer.println(power(a, d, m));
                }
            }
        }
        writer.close();
    }

    void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    BigInteger power(BigInteger a, BigInteger n, BigInteger m) {
        BigInteger result = BigInteger.ONE;
        while (!n.equals(BigInteger.ZERO)) {
            if (n.testBit(0)) {
                result = result.multiply(a).remainder(m);
            }
            a = a.multiply(a).remainder(m);
            n = n.shiftRight(1);
        }
        return result;
    }

    BigInteger getInverse(BigInteger a, BigInteger m) {
        BigInteger b = extendedGCD(a, m)[0];
        return b.remainder(m).add(m).remainder(m);
    }

    BigInteger[] extendedGCD(BigInteger a, BigInteger b) {
        if (a.equals(BigInteger.ONE)) {
            return new BigInteger[]{BigInteger.ONE, BigInteger.ZERO};
        }
        BigInteger[] result = extendedGCD(b, a.remainder(b));
        BigInteger x = result[1];
        BigInteger y = result[0];
        // b * y + (a - a / b * b) * x = a * x + (y - a / b * x) * y
        return new BigInteger[]{x, y.subtract(a.divide(b).multiply(x))};
    }
}
