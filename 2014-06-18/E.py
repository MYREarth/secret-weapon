from random import randint
for _ in xrange(50):
    n = 75
    print n
    graph = [['0'] * n for _ in xrange(n)]
    for i in xrange(n):
        for j in xrange(i):
            if randint(0, 1) == 0:
                graph[i][j] = '1'
            else:
                graph[j][i] = '1'
    for i in xrange(n):
        print "".join(graph[i])

