from random import randint

M = 100
n = randint(1, M)
k = randint(1, n)
print(n, k)
print(" ".join(map(str, [randint(-M, M) for _ in range(n)])))
