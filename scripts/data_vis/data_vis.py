import sys

class Contender:
    def __init__(self, evals, fitness, eq):
        self.evals = evals
        self.fitness = fitness
        self.eq = eq


class Experiment:
    def __init__(self, data_set, run_time, params, method, data_path, contenders):
        self.data_set = data_set
        self.run_time = run_time
        self.params = params
        self.method = method
        self.data_path = data_path
        self.contenders = contenders


class Cohort:
    def __init__(self, experiments, data_set, data_path, parameters, method, step_size, data, n):
        self.experiments = experiments
        self.data_set = data_set
        self.data_path = data_path
        self.parameters = parameters
        self.method = method
        self.step_size = step_size
        self.data = data
        self.n = n

        def safe_div(a, b):
            """Performs a safe division of a by b, to return a number if b = 0, but not crash"""
            if b == 0:
                if a > 0:
                    return sys.float_info.max
                else:
                    return -1 * sys.float_info.max
            else:
                return a / b


if __name__ == '__main__':
    print('what\n')
