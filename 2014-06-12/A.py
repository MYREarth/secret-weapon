print 4000
a = 'b' * 1000 + 'a' * 2000 + 'b' * 1000
b = 'a' * 999 + 'b' + 'a' + 'b' * 1998 + 'a' + 'b' + 'a' * 999
assert len(a) == 4000 and len(b) == 4000
print a
print b
