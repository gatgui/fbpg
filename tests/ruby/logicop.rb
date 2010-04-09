
x = 1.0
y = -x

puts "x = #{x}"
puts "y = #{y}"

if x >= y and y < 0  then
  puts "x>=y and y<0"
else
  puts "flawed logic"
end

if x >= y and not y >= 0 then
  puts "x>=y and y<0"
else
  puts "flawed logic"
end

if x < 0 or y < 0 then
  puts "x<0 or y<0"
else
  puts "flawed logic"
end

if not x < 0 or y > 0 then
  puts "not x<0 or y>0"
else
  puts "flawed logic"
end

if not (x>0 or y<0) then
  puts "flawed logic"
else
  puts "x>0 and y<0"
end
