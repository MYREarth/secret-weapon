from random import randint
n = 500
m = n * (n - 1) // 2
q = 200000
print(n, m, q)
total = 0
for i in range(n):
    for j in range(i):
        total += 1
        print(i + 1, j + 1, total)
for i in range(q):
    if (randint(1,2)==1):
        print(1,randint(1,n))
    else:
        print(2,randint(1,m))
