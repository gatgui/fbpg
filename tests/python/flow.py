
i = 0
while i < 20:
  print(i)
  i = i + 1
  if i >= 10:
    print("early exit")
    break

x = 4
y = 4

if x == y:
  print("x equals y")
else:
  print("x does not equal y")

y = 5
if x != y:
  print("As expected")
