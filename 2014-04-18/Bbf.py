n, m = map(int, raw_input().split())
a = map(int, raw_input().split())
result = 0
for mask in xrange(1 << n):
    count, number = 0, ""
    for i in xrange(n):
        if mask >> i & 1:
            number += str(a[i])
        else:
            count += 1
    if count == m:
        result = max(result, int(number))
print(result)
