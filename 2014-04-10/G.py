from sys    import argv
from random import randint, choice

for i in xrange(int(argv[1])):
    print choice(('buy', 'sell')), randint(1, int(argv[2])), randint(1, int(argv[3]))
print 'end'
