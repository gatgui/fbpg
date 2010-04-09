
x = 1.0
y = -x

print("x = %s" % x)
print("y = %s" % y)

if x >= y and y < 0:
  print("x>=y and y<0")
else:
  print("flawed logic")

if x >= y and not y >= 0:
  print("x>=y and y<0")
else:
  print("flawed logic")

if x < 0 or y < 0:
  print("x<0 or y<0")
else:
  print("flawed logic")

if not x < 0 or y > 0:
  print("not x<0 or y>0")
else:
  print("flawed logic")

if not (x>0 or y<0):
  print("flawed logic")
else:
  print("x>0 and y<0")
