#=
progGraph:
- Julia version: 
- Author: atlas1323
- Date: 2022-11-22
=#

using GLMakie, Makie, Random, Printf

function progupdate()

end

struct GraphPoints
    x::Vector{Float64}
    y::Vector{Float64}
end

mutable struct Contender
    evals::Int64
    fitness::Float64
    eq::Vector{String}

    Contender() = new()
end

mutable struct Experiment
    data_set::String
    run_time::String
    params::Dict{String, Any}
    method::String
    data_path::String
    contenders::Vector{Contender}

    Experiment() = new()
end

"""
Experiment parameter string parser
"""
function parse_parameters(param_string::SubString{String})::Dict{String, Any}
    dict = Dict{String, Any}()
    params = split(param_string, " ")
    for p in params
        if ':' in p
            key, val = split(p, ':')
            dict[key] = parse(Float64, val)
        end
    end
    return dict
end

mutable struct DataPoint
    average::Float64
    stdev::Float64
    evals::Int64
end


# Cohort struct defintition
mutable struct Cohort
    experiments::Vector{Experiment}
    data_set::String
    data_path::String
    parameters::Dict{String, Any}
    method::String
    step_size::Int64
    data::Vector{DataPoint}
    n::Int64

    Cohort() = new()
end

function safe_div(a::Float64, b::Float64)::Float64
#     println("Safe division: ", a, " ", b)
    big = prevfloat(typemax(Float64))
#     out = big
#     if (b == 0 && a > 0)
#         println("BOOM")
#         out = big
#     elseif (b ==0 && a < 0)
#         println("BOOM2")
#         out = -1*big
#     elseif (b == 0 && a == 0)
#         println("BOOM3")
#         out = 0
#     else
#         out =  a / b
#     end
#     println(out)
#     return out
    resultant = a / b
#     println(resultant == Inf)
    if (resultant == Inf)
#         println(a, " ", b)
        return big
    elseif (resultant == -Inf)
        return -1 * big
    else
       return resultant
    end
end

function safe_product(a::Float64, b::Float64)::Float64
    big = prevfloat(typemax(Float64))
    resultant = a*b
    if (resultant == Inf)
#         println(a, " ", b)
        return big
    elseif (resultant == -Inf)
        return -1 * big
    else
       return resultant
    end

end


"""
Creates function for data
"""
function getEq(index::Int64, x, eq::Vector{String})

    big = prevfloat(typemax(Float64))
    if (tryparse(Float64, eq[index]) == nothing)
        if (eq[index] == "VAR")
            return x
        elseif (eq[index] == "ADD")
            temp = getEq(index * 2, x, eq) + getEq(index * 2 + 1, x, eq)
            if temp == Inf
                return big
            elseif temp == -Inf
                return -1 * big
            end
            return temp
        elseif (eq[index] == "SUB")
            temp = getEq(index * 2, x, eq) - getEq(index * 2 + 1, x, eq)
            if temp == Inf
                return big
            elseif temp == -Inf
                return -1 * big
            end
            return temp
        elseif (eq[index] == "MLT")
            temp = getEq(index * 2, x, eq) * getEq(index * 2 + 1, x, eq)
            if temp == Inf
                return big
            elseif temp == -Inf
                return -1 * big
            end
            return temp
        elseif (eq[index] == "DIV")
#             return getEq(index*2, x, eq) / getEq(index*2 + 1, x, eq)
            temp = getEq(index * 2, x, eq) / getEq(index * 2 + 1, x, eq)
            if temp == Inf
                return big
            elseif temp == -Inf
                return -1 * big
            end
            return temp
        elseif (eq[index] == "SIN")
            temp = getEq(index * 2, x, eq)
#             println(temp)
            return sin(temp)
        elseif (eq[index] == "COS")
            return cos(getEq(index * 2, x, eq))
        end
    else
        return parse(Float64, eq[index])
    end

    return f(x)
end

"""
Reads in data from an experiment logfile
"""
function read_in_experiment(file_path::String)
    # read in file
    exp = Experiment()
    exp.contenders = Contender[]
    open(file_path, "r") do io
        lines = readlines(io)
        for (index, line) in enumerate(lines)
            if index == 1
                exp.data_set = split(line, ":\t")[2]
            elseif index == 2
                exp.run_time = split(line, ":\t")[2]
            elseif index == 3
                exp.method = split(line, ":\t")[2]
            elseif index == 4
                parse_string = split(line, "\t")[2]
                exp.params = parse_parameters(parse_string)
            elseif index == 5
                exp.data_path = split(line, ":\t")[2]
            elseif index > 8
                contender = Contender()
                parts = split(line, " | ")
                contender.evals = parse(Int64, parts[1])
                contender.fitness = parse(Float64, parts[2])
                contender.eq = split(parts[3], " ")[2:end]

                push!(exp.contenders, contender)
            end
        end
    end

    return exp
end


"""
Reads in points from a dataset
"""
function read_in_points(path::String)::GraphPoints
    xPoints = Float64[]
    yPoints = Float64[]
    open(path, "r") do io
        while ! eof(io)
            line = readline(io)
            temp = split(line, "\t")
            push!(xPoints, parse(Float64, temp[1]))
            push!(yPoints, parse(Float64, temp[2]))
        end
    end
    points = GraphPoints(xPoints, yPoints)
    return points
end

"""
"""
function plot_func(con::Contender, points::GraphPoints)
    fig = Figure()
    ax = Axis(fig[1, 1], title = "BOOMSHAKA")
    f(x) = getEq(1, x, con.eq)
    y_vals = f.(points.x)
    scatter!(ax, points.x, points.y, color = :coral2, markersize = 2, linewidth = 1)
    scatter!(ax, points.x, y_vals, color = :orchid, markersize = 2, linewidth = 1)
    fig
end

function get_y_vals(exp::Experiment, conDex::Int64, points::GraphPoints)
        f(x) = getEq(1, x, exp.contenders[conDex].eq)
        return f.(points.x)
end

function animate_func(exp::Experiment, points::GraphPoints, savePath::String)
    s = Scene(resolution = (500,500))
    time = Node(1)
#     g(x) = @lift(getEq(1, x, exp.contenders[$time].eq))
#     f(x) = getEq(1, x, exp.contenders[1].eq)
#     y_vals = f.(points.x)
    y_vals = @lift(get_y_vals(exp, $time, points))
    scatter!(s, points.x, points.y, color = :coral2, markersize = 2, linewidth = 1)
    scatter!(s, points.x, y_vals, color = :orchid, markersize = 2, linewidth = 1)


    steps = collect(1:size(exp.contenders, 1))
    Makie.record(s, savePath, steps; framerate = 1) do step
#         delete!(s, s[end])
#         f(x) = getEq(1, x, exp.contenders[step].eq)
#         y_vals = f.(points.x)
#         scatter!(s, points.x, y_vals, color = :orchid, markersize = 2, linewidth=1)
        time[] = step
    end

end

function animate_func2(exp::Experiment, points::GraphPoints, savePath::String)
    fig = Figure()
    ax = Axis(fig[1, 1],
    title = "Animation....")
    time = Observable(1)
    y_vals = @lift(get_y_vals(exp, $time, points))
    scatter!(ax, points.x, points.y, color = :coral2, markersize = 2, linewidth = 1)
    scatter!(ax, points.x, y_vals, color = :orchid, markersize = 2, linewidth = 1)

    steps = collect(1:size(exp.contenders, 1))
    record(fig, savePath, steps; framerate = 7) do step
        time[] = step
    end
end



function convergence_plot(plotTitle::String, dataPaths::String, criterion::Float64, step::Int64, eval_count::Int64)
    println("Building convergence plot: ", plotTitle)
    file_names = readdir(dataPaths);
    tracker = fill(eval_count + 5, size(file_names))

    println("....")

end


function main()
   data_set = "../resources/datasets/data.txt"
#    exp_path = "../resources/out/data_HFC-Cross_2022`12`2-22`59`1.txt"
  exp_path = "../resources/out/data_HFC-Rand_2022`12`19-20`45`10/data_HFC-Rand_2022`12`19-20`45`10_learn.txt"



   points = read_in_points(data_set)
   exp = read_in_experiment(exp_path)

#    plot_func(exp.contenders[end], points)
    animate_func2(exp, points, "../resources/Images/testAnim-RandHFC.mp4")
end

main()
