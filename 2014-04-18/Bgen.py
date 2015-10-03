from sys import argv
from random import randint

n = int(argv[1])
m = randint(1, n - 1)
#alphabet = argv[2]
print n, m
print " ".join([str(randint(1, 1000000)) for _ in xrange(n)])
