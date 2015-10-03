from random import shuffle

n = 10000
print 1
print n
p = range(1, n + 1)
shuffle(p)
print " ".join(map(str, p))
