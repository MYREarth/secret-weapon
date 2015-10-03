from sys    import argv
from random import choice

n = int(argv[1])
print "".join([choice(('a', 'b')) for i in xrange(n)])
