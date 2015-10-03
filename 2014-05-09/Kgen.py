from itertools import permutations

def solve(n, k):
    s1, s2 = 0, 0
    for p in permutations(xrange(n)):
        even = 0
        for i in xrange(n):
            for j in xrange(i):
                if p[i] < p[j]:
                    even += 1
        for i in xrange(n):
            for j in xrange(i):
                for k in xrange(j):
                    for l in xrange(k):
                        for q in xrange(l):
                            if p[i] > p[j] > p[k] > p[l] > p[q]:
                                if even % 2 == 0:
                                    s2 += 1
                                else:
                                    s1 += 1
    return s1, s2

n, k = map(int, raw_input().split())
print solve(n, k)
