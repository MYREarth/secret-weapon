from fractions import Fraction
from random    import shuffle

def brute_force(n, m):
    if n > m:
        return brute_force(m, n)
    board = [[False] * (n + m - 1) for _ in xrange(n + m - 1)]
    x0, y0 = m - 1, 0
    for i in xrange(n):
        for j in xrange(m):
            board[x0 - j][y0 + j] = True
        x0 += 1
        y0 += 1
    for i in xrange(n + m - 1):
        y0 = 0
        while not board[i][y0]:
            y0 += 1
        y1 = n + m - 2
        while not board[i][y1]:
            y1 -= 1
        for j in xrange(y0, y1 + 1):
            board[i][j] = True
        #print "".join(map(lambda flag : flag and '#' or '.', board[i]))
    partial = [[0] * (n + m) for _ in xrange(n + m)]
    for i in reversed(xrange(n + m - 1)):
        for j in reversed(xrange(n + m - 1)):
            partial[i][j] = partial[i + 1][j] + partial[i][j + 1] - partial[i + 1][j + 1]
            if not board[i][j]:
                partial[i][j] += 1
    result = 0
    for i in xrange(n + m - 1):
        for ii in xrange(i, n + m - 1):
            for j in xrange(n + m - 1):
                for jj in xrange(j, n + m - 1):
                    if partial[i][j] - partial[ii + 1][j] - partial[i][jj + 1] + partial[ii + 1][jj + 1] == 0:
                        result += 1
    return result

## 1, n, m, n * m, n * n, m * m, n * n * m, n * m * m, n * n * m * m

coefficient = []
for n in xrange(1, 15):
    for m in xrange(n, 15):
        rows = []
        for i in xrange(7):
            for j in xrange(7):
                if i + j <= 6:
                    rows.append(pow(n, i) * pow(m, j))
        rows.append(brute_force(n, m))
        coefficient.append(rows)
shuffle(coefficient)
n = len(coefficient)
m = len(coefficient[0]) - 1
print n, m
for j in xrange(m):
    pivot = j
    while pivot < n and coefficient[pivot][j] == 0:
        pivot += 1
    assert pivot < n
    coefficient[j], coefficient[pivot] = coefficient[pivot], coefficient[j]
    for i in xrange(n):
        if i != j:
            t = Fraction(coefficient[i][j]) / coefficient[j][j]
            for k in xrange(m + 1):
                coefficient[i][k] -= coefficient[j][k] * t
for i in xrange(m, n):
    assert all(map(lambda zero : zero == 0, coefficient[i]))
k = 0
for i in xrange(7):
    for j in xrange(7):
        if i + j <= 6:
            rows.append(pow(n, i) * pow(m, j))
            c = coefficient[k][m] / coefficient[k][k]
            if c != 0:
                print c, "n^%d m^%d" %(i, j)
            k += 1
#for i in xrange(n):
#    print coefficient
