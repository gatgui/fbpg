
# I haven't found a way to make this work in python yet...

def createCounter (n):
  i = 0
  def fn():
    if i >= n:
      return False
    else:
      i = i + 1
      return False
  return fn


counter = createCounter(10)
while counter():
  counter2 = createCounter(5)
  while counter2():
    print("  Counter 2")
  print("Counter")

