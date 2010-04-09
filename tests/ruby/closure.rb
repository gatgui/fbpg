
def createCounter(n)
  i = 0
  # def fn() -> doesn't work at all
  # fn = Proc.new -> doesn't work because of the return statement
  fn = Kernel.proc do
    if i >= n then
      return false
    else
      i = i + 1
      return true
    end
  end
  return fn
end


counter = createCounter(10)
while counter.call() do
  counter2 = createCounter(5)
  while counter2.call() do
    puts "  Counter 2"
  end
  puts "Counter"
end

