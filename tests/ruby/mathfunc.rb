

puts "PI/2 = #{Math::PI/2}"
puts "PI/4 = #{Math::PI/4}"
puts "PI/6 = #{Math::PI/6}"
puts "sin(PI/4) = #{Math.sin(Math::PI/4)}"
puts "sqrt(2)/2 = #{Math.sqrt(2)/2}"
puts "cos(PI) = #{Math.cos(Math::PI)}"
puts "tan(PI/2) = #{Math.tan(0.5*Math::PI)}"
puts "atan(1) = #{Math.atan(1)}"
puts "atan2(1, sqrt(2)/2) = #{Math.atan2(1, Math.sqrt(2)/2)}"
puts "acos(0.5) = #{Math.acos(0.5)}"
puts "hypot(2, 4) = #{Math.hypot(2, 4)}"
puts "abs(-2.71) = #{-2.71.abs}"
puts "ceil(-2.71) = #{-2.71.ceil}"
puts "floor(-2.71) = #{-2.71.floor}"
puts "log(0.2) = #{Math.log(0.2)}"
puts "log10(0.2) = #{Math.log10(0.2)}"
puts "exp(1.3) = #{Math.exp(1.3)}"
puts "log(exp(10)) = #{Math.log(Math.exp(10))}"
puts "pow(2, 4) = #{2 ** 4}"
puts "mod(6.34, 2) = #{6.34.divmod(2)[1]}"

#puts "round(-2.71) = #{Math.round(-2.71)}"
#puts "trunc(-2.71) = #{Math.trunc(-2.71)}"
#puts "cbrt(8) = #{Math.cbrt(8)}"
#puts "log2(0.2) = #{Math.log2(0.2)}"
#puts "exp2(1.3) = #{Math.exp2(1.3)}"
#puts "log2(exp2(10)) = #{Math.log2(exp2(10))}"
#puts "remainder(6.34, 2) = #{Math.remainder(6.34, 2)}"
#puts "max(6.34, 5.987) = #{Math.max(6.34, 5.987)}"
#puts "min(6.34, 5.987) = #{Math.min(6.34, 5.987)}"

a = Math.sin(0.6)
b = Math.cos(-0.2)
c = (a + b) / 0.5
puts "(sin(0.6) + cos(-0.2)) / 0.5 = #{c}"
