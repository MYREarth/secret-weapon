from sys    import argv
from random import choice, randint

n, m = map(int, argv[1:3])
print n
for _ in xrange(n):
    print choice(('ADD', 'FIND', 'REMOVE')), randint(1, m)
