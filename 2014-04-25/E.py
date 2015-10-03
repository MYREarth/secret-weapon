from random import randint

print 1
n = 200000
print n, n
print " ".join(map(str, [randint(-100, 1000) for i in xrange(n)]))
for i in xrange(2, n + 1):
    print i - 1, i
    #print randint(1, i - 1), i
