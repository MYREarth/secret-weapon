c = "123"
b = c + c + "0"
a = b + b
print a
n = len(a)
result = 0
for i in xrange(n):
    for j in xrange(i + 1, n + 1):
        print a[i:j]
        if (a[i] != '0' or i + 1 == j) and int(a[i : j]) % 2 == 0:
            result += 1
print result
