from random import choice

n = 10 ** 6
print "".join([choice(('a', 'b')) for i in xrange(n)])
