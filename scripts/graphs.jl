#=
graphs:
- Julia version: 
- Author: atlas1323
- Date: 2022-07-22
=#

using CairoMakie, Random, Printf

"""
"""
struct GraphPoint
    x::Float64
    y::Float64
end


mutable struct Contender
   evals::Int64

end

mutable struct ExperimentalGraph
    data_set::String
    runt_time::String
    paramaters::Dict{String, Any}
    method::String
    data_path::String
    contenders::Vector{Contender}
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


# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Data Processing
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

mutable struct DataPoint
    average::Float64
    stdev::Float64
    evals::Int64
end

mutable struct Cohort
#     experiments::Vector{Experiment}
    data_set::String
    data_path::String
    parameters::Dict{String, Any}
    method::String
    step_size::Int64
    data::Vector{DataPoint}
    n::Int64

    Cohort() = new()
end

function build_cohort(directory::String)::Cohort
    # Get all files in directory and collect experiments
    cohort = Cohort()
    exp_list = readdir(directory)
    cohort.n = size(exp_list, 1)
    cohort.experiments = Vector{Experiment}()
    for e in exp_list
        path = @sprintf "%s/%s" directory e
        println(path)
        push!(cohort.experiments, get_experiment(path))
    end

    # TODO: Populate other variables
    cohort.data_set = cohort.experiments[1].data_set
    cohort.data_path = cohort.experiments[1].data_path
    cohort.method = cohort.experiments[1].method
    cohort.parameters = cohort.experiments[1].parameters
    cohort.step_size = 1000
    println(cohort.parameters)

    println(typeof(cohort))
    data_calc!(cohort)
    return cohort
end

function data_calc!(cohort::Cohort)
    counter = fill(1, cohort.n)
    println(cohort.parameters["E"])
    println(cohort.experiments[1].data_set)
    cohort.data = Vector{DataPoint}()
    for i in 1:cohort.step_size:cohort.parameters["E"]
        μ = 0
        σ = 0
        target = i*cohort.step_size
        for j in 1:cohort.n
            # advance counter until it recaches target, then grab 1 before that
            while (target >= cohort.experiments[j].contenders[counter[j]].evals) && (counter[j] < size(cohort.experiments[j].contenders, 1))
                # println(@sprintf "%i :: %i :: %i" target cohort.experiments[j].contenders[counter[j]].evals counter[j])
                counter[j] += 1
            end
            # use determined counter to create average
            μ += cohort.experiments[j].contenders[counter[j] - 1].path_length
        end
        μ /= cohort.n
        for j in 1:cohort.n
            σ += (cohort.experiments[j].contenders[counter[j] - 1].path_length - μ)^2
        end
        σ = sqrt(σ / cohort.n)
        push!(cohort.data, DataPoint(μ, σ, target))
    end
end

# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Data IO
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽


# Read in experiment files and store in container of experiments
"""
Retrieves data from file described by `path` and returns Vector of points
"""
function read_in_points(path::String)::Vector{GraphPoint}
    points = GraphPoint[]
    open(path, "r") do io

        while ! eof(io)
            line = readline(io)
            temp = split(line, "\t")
            push!(points, GraphPoint(parse(Float64, temp[1]), parse(Float64, temp[2])))

        end
    end

    return points
end


function get_experiment(path::String)::Experiment
    # TODO: Populate
    print("Retrieving Experiment...")
end



# △△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△△
# Graph Factory
# ▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽

function translate_route(points::Vector{GraphPoint}, route::Vector{Int64})
    xs = Vector{Float64}()
    ys = Vector{Float64}()

    for index in route
        push!(xs, points[index].x)
        push!(ys, points[index].y)
    end

    return xs, ys
end

function graph_route(xs::Vector{Float64}, ys::Vector{Float64}, f)
    # f = Figure()
#     Axis(f[1, 1])
#     Axis(f[1, 1], xscale = log10, title = string("log10"),
#         yminorticksvisible = true, yminorgridvisible = true,
#         yminorticks = IntervalsBetween(8))

    scatter!(xs, ys, markersize = 2, linewidth = 1)
    # f
end

function main()
    data_path = "../resources/datasets/data.txt"
    points = read_in_points(data_path)
    p_size = size(points, 1)
    route = collect(1:p_size)

    save_path = "../resources/graphs/test.png"
    g_title = "Data.txt ScatterLinePlot"
    fig = Figure(resolution = (800, 800))
    Axis(fig[1, 1], title = g_title)
    xs, ys = translate_route(points, route)
    graph_route(xs, ys, fig)

    ys2 = fill(sin(-5.821042), size(ys, 1))
    graph_route(xs, ys2, fig)


    save(save_path, fig)
end


main()
