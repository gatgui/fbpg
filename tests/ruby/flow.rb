
i = 0
while i < 20 do
  puts i
  i = i + 1
  if i >= 10 then
    puts "early exit"
    break
  end
end

x = 4
y = 4

if x == y then
  puts "x equals y"
else
  puts "x does not equal y"
end

y = 5
if x != y then
  puts "As expected"
end
