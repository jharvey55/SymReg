import sys
import pandas as pd


class Contender:
    def __init__(self, evals, fitness, eq):
        self.evals = evals
        self.fitness = fitness
        self.eq = eq

    @classmethod
    def read_in_contender(cls, line):
        """
        parses contender from line in experiment files
        :param line: data entry from experiment learn file
        :return: contender (instance of Contender extracted from line)
        """
        [evals_string, fitness_string, eq_string] = line.split(" | ")

        evals = int(evals_string)
        fitness = float(fitness_string)
        eq_string = eq_string.rstrip("\n")
        eq = eq_string.split(" ")

        contender = cls(evals, fitness, eq)
        return contender

    @classmethod
    def safe_div(cls, a, b):
        """Performs a safe division of a by b, to return a number if b = 0, but not crash"""
        if b == 0:
            if a > 0:
                return sys.float_info.max
            else:
                return -1 * sys.float_info.max
        else:
            return a / b


class Experiment:
    def __init__(self, data_set, run_time, params, method, data_path, contenders):
        self.data_set = data_set
        self.run_time = run_time
        self.params = params
        self.method = method
        self.data_path = data_path
        self.contenders = contenders
        self.points = pd.read_csv(data_path, sep="\t", header=None, names=['x', 'y'])


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
    a = "250 | 0.507485 | ROOT SIN SIN BLANK SUB BLANK BLANK BLANK COS DIV BLANK BLANK BLANK BLANK BLANK BLANK SUB BLANK ADD MLT BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK 8.583254 VAR BLANK BLANK -5.630509 VAR VAR VAR BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK"
    b = Contender.read_in_contender(a)
    print(b.eq[1])
