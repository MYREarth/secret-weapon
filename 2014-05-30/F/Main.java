import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    List <List <Integer>> generate(List <List <Integer>> partitions, int[] partition, int n, int min, int size) {
        if (n == 0) {
            List <Integer> partitionClone = new ArrayList <Integer>();
            for (int i = 0; i < size; ++ i) {
                partitionClone.add(partition[i]);
            }
            partitions.add(partitionClone);
            return partitions;
        }
        for (int x = min; x <= n; ++ x) {
            partition[size] = x;
            generate(partitions, partition, n - x, x, size + 1);
        }
        return partitions;
    }

    Result[][] results;

    class Result {
        int[]      permutation;
        BigInteger count;
    }

    void prepare(int n) {
        List <List <Integer>> partitions = generate(new ArrayList <List <Integer>>(), new int[n], n, 1, 0);
        int m = partitions.size();
        BigInteger[][] transfer = new BigInteger[m][m];
        for (int _ = 0; _ < m; ++ _) {
            Arrays.fill(transfer[_], BigInteger.ZERO);
            List <Integer> partition = partitions.get(_);
            transfer[_][_] = transfer[_][_].add(BigInteger.valueOf(n));
            int p = partition.size();
            for (int i = 0; i < p; ++ i) {
                for (int j = 0; j < p; ++ j) {
                    if (i == j) {
                        for (int x = 1; x < partition.get(i); ++ x) {
                            List <Integer> newPartition = new ArrayList <Integer>();
                            for (int k = 0; k < p; ++ k) {
                                if (k != i && k != j) {
                                    newPartition.add(partition.get(k));
                                }
                            }
                            newPartition.add(x);
                            newPartition.add(partition.get(i) - x);
                            Collections.sort(newPartition);
                            int __ = partitions.indexOf(newPartition);
                            transfer[_][__] = transfer[_][__].add(BigInteger.valueOf(partition.get(i)));
                        }
                    } else {
                        List <Integer> newPartition = new ArrayList <Integer>();
                        for (int k = 0; k < p; ++ k) {
                            if (k != i && k != j) {
                                newPartition.add(partition.get(k));
                            }
                        }
                        newPartition.add(partition.get(i) + partition.get(j));
                        Collections.sort(newPartition);
                        int __ = partitions.indexOf(newPartition);
                        transfer[_][__] = transfer[_][__].add(BigInteger.valueOf(partition.get(i) * partition.get(j)));
                    }
                }
            }
        }
        BigInteger[] factorial = new BigInteger[n + 1];
        factorial[0] = BigInteger.ONE;
        for (int i = 1; i <= n; ++ i) {
            factorial[i] = factorial[i - 1].multiply(BigInteger.valueOf(i));
        }
        BigInteger[] duplicates = new BigInteger[m];
        for (int i = 0; i < m; ++ i) {
            List <Integer> partition = partitions.get(i);
            duplicates[i] = factorial[n];
            for (int size : partition) {
                duplicates[i] = duplicates[i].divide(BigInteger.valueOf(size));
            }
            for (int j = 0; j < partition.size(); ) {
                int k = j;
                while (k < partition.size() && partition.get(j) == partition.get(k)) {
                    k ++;
                }
                duplicates[i] = duplicates[i].divide(factorial[k - j]);
                j = k;
            }
        }
        BigInteger[][] ways = new BigInteger[2][m];
        Arrays.fill(ways[0], BigInteger.ZERO);
        ways[0][0] = BigInteger.ONE;
        results[n][0] = new Result();
        results[n][0].permutation = new int[n];
        for (int i = 0; i < n; ++ i) {
            results[n][0].permutation[i] = i;
        }
        results[n][0].count = BigInteger.ONE;
        for (int i = 1; i <= 300; ++ i) {
            Arrays.fill(ways[i & 1], BigInteger.ZERO);
            for (int j = 0; j < m; ++ j) {
                for (int k = 0; k < m; ++ k) {
                    if (transfer[j][k].signum() > 0) {
                        ways[i & 1][k] = ways[i & 1][k].add(ways[i + 1 & 1][j].multiply(transfer[j][k]));
                    }
                }
            }
            BigInteger max = ways[i & 1][0];
            for (int j = 0; j < m; ++ j) {
                max = max.max(ways[i & 1][j].divide(duplicates[j]));
            }
            int j = 0;
            while (j < m && !ways[i & 1][j].divide(duplicates[j]).equals(max)) {
                j ++;
            }
            List <Integer> partition = partitions.get(j);
            int[] permutation = new int[n];
            int start = 0;
            for (int k = 0; k < partition.size(); ++ k) {
                for (int p = 0; p < partition.get(k); ++ p) {
                    permutation[start + p] = start + (p + 1) % partition.get(k);
                }
                start += partition.get(k);
            }
            results[n][i] = new Result();
            results[n][i].count = max;
            results[n][i].permutation = permutation;
        }
    }

    public void run() {
        results = new Result[15][301];
        BigInteger[][] all = new BigInteger[15][301];
        for (int n = 1; n <= 14; ++ n) {
            prepare(n);
            all[n][0] = BigInteger.ONE;
            for (int t = 1; t <= 300; ++ t) {
                all[n][t] = all[n][t - 1].multiply(BigInteger.valueOf(n * n));
            }
        }
        try {
            Scanner scanner = new Scanner(new File("frequent.in"));
            PrintWriter writer = new PrintWriter(new File("frequent.out"));
            while (true) {
                int n = scanner.nextInt();
                int t = scanner.nextInt();
                if (n == 0) {
                    break;
                }
                Result result = results[n][t];
                for (int i = 0; i < n; ++ i) {
                    if (i > 0) {
                        writer.print(" ");
                    }
                    writer.print(result.permutation[i] + 1);
                }
                writer.println();
                BigInteger p = result.count;
                BigInteger q = all[n][t];
                BigInteger g = p.gcd(q);
                writer.println(p.divide(g) + "/" + q.divide(g));
            }
            writer.close();
        } catch (FileNotFoundException ex) {
        }
    }

    private void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }
}
