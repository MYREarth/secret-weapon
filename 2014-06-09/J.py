from random import randint
N = 32767
print N
for i in xrange(1, N + 1):
    left = i * 2 <= N and i * 2 or 0
    right = i * 2 + 1 <= N and i * 2 + 1 or 0
    print left, right, randint(0, 1)
