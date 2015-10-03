from sys    import argv
from random import randint

n, m = map(int, argv[1:3])
print n, m
#s = "a" * n
s = ("abcdefghijklmnopqrstuvxyz" * 10000)[:n]
print s
for i in xrange(m):
    print " ".join(map(str, sorted([randint(1, n), randint(1, n)])))
