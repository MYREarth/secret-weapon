from sys import argv
from random import randint

def describe(n):
    s = str(n)
    result = ''
    i = 0
    while i < len(s):
        j = i
        while j < len(s) and s[i] == s[j]:
            j += 1
        result += str(j - i) + s[i]
        i = j
    return result

n = 1
while True:
    p = describe(n)
    if len(str(p)) >= 10000:
        break
    n = p
print n
#backup = n = randint(1, int(argv[1])) for i in xrange(randint(1, int(argv[2]))): n = describe(n) print n print backup
