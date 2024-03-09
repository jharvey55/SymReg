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


if __name__ == '__main__':
    print('what\n')
