#=
test.jl:
- Julia version: 
- Author: atlas1323
- Date: 2022-06-29
=#
using Printf

index = 9
size = 128

base_level = trunc(Int64, floor(log2(index)))
max_depth = trunc(Int64, log2(size))
d = max_depth - base_level

println("#############################################")

for l in (d - 1):-1:0
    left_node = (2^l) * index
    println(l)
    for n in (2^l - 1):-1:0
        print(left_node + n, " ")
    end
    println("")
end

println("#############################################")

branchdex = 1

for l in 0:(d - 1)
    left_node = trunc(Int64, (2^l) * index)
    println(l)
    for n in 0:((2^l) - 1)
        @printf("(%2d:%3d) ", branchdex, left_node + n)
        global branchdex += 1
    end
    println("")
end