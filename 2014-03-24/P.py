from sys    import argv
from random import randint

n, m = map(int, argv[1:3])
print n
for i in xrange(n):
    print randint(0, m), randint(0, m), randint(0, m)
