#=
tdGen:
- Julia version: 
- Author: atlas1323
- Date: 2022-07-03
=#
using Printf



function writeData(fname::String, xs::Vector{Float64}, ys::Vector{Float64})
    fpath = @sprintf "../resources/datasets/%s" fname

    open(fpath, "a") do io
        for (index, x) in enumerate(xs)
            line = string(x) * " " * string(ys[index]) * "\n"
            write(io, line)
        end
    end
end


function main()
    x = collect(0.1:0.1:20)

    f1 = fill(3.14, size(x))
    writeData("f1.txt", x, f1)

    f2 = 3.0 .* cos.(x);
    writeData("f2.txt", x, f2)

    f3 = (x.^4)./2;
    writeData("f3.txt", x, f3)

    f4 = 2 .* x
    writeData("f4.txt", x, f4)

    f5 = cos.(2 .* x .+ 3) .+ 1 ./ x
    writeData("f5.txt", x, f5)
end


main()