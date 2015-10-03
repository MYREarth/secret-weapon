from random import choice
print 1, 1
print "".join([choice(('a', 'b')) for i in xrange(100000)])
print 100000
for i in xrange(100000):
    print '1', '+', choice(('a', 'b'))
