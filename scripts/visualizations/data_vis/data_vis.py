import sys
import pandas as pd
import numpy as np
import math
import matplotlib.pyplot as plt


class Contender:
    big = sys.float_info.max

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
        eq_string = eq_string.rstrip(" ")
        eq_string = eq_string.lstrip(" ")
        eq = eq_string.split(" ")

        contender = cls(evals, fitness, eq)
        return contender

    @classmethod
    def safe_div(cls, a, b):
        """Performs a safe division of a by b, to return a number if b = 0, but not crash"""
        if b == 0:
            if a > 0:
                return cls.big
            else:
                return -1 * cls.big
        else:
            return a / b

    @classmethod
    def test_float(cls, string):
        try:
            out = float(string)
            return out
        except ValueError:
            return None

    @classmethod
    def parse_values(cls, index, x, eq):
        test = cls.test_float(eq[index])
        if test is None:
            if eq[index] == "VAR":
                return x
            elif eq[index] == "ADD":
                temp = cls.parse_values(index * 2, x, eq) + cls.parse_values(index * 2 + 1, x, eq)
                if temp == math.inf:
                    return cls.big
                elif temp == -1 * math.inf:
                    return -1 * cls.big
                else:
                    return temp
            elif eq[index] == "SUB":
                temp = cls.parse_values(index * 2, x, eq) - cls.parse_values(index * 2 + 1, x, eq)
                if temp == math.inf:
                    return cls.big
                elif temp == -1 * math.inf:
                    return -1 * cls.big
                else:
                    return temp
            elif eq[index] == "MLT":
                temp = cls.parse_values(index * 2, x, eq) * cls.parse_values(index * 2 + 1, x, eq)
                if temp == math.inf:
                    return cls.big
                elif temp == -1 * math.inf:
                    return -1 * cls.big
                else:
                    return temp
            elif eq[index] == "DIV":
                return cls.safe_div(cls.parse_values(index * 2, x, eq), cls.parse_values(index * 2 + 1, x, eq))
            elif eq[index] == "SIN":
                return math.sin(cls.parse_values(index * 2, x, eq))
            elif eq[index] == "COS":
                return math.cos(cls.parse_values(index * 2, x, eq))
        else:
            return test

    def get_prediction(self, points):
        x_vals = points['x'].tolist()
        y_vals = []
        for x in x_vals:
            y_vals.append(self.parse_values(1, x, self.eq))
        prediction = {'x': x_vals, 'y': y_vals}
        return pd.DataFrame(prediction)


class Experiment:
    def __init__(self, exp_path, data_set, run_time, params, method, contenders):
        self.exp_path = exp_path
        self.data_set = data_set
        self.run_time = run_time
        self.params = params
        self.method = method
        self.contenders = contenders

    @classmethod
    def blank_experiment(cls):
        blank = cls("", "", "", {}, "", [])
        return blank

    @classmethod
    def parse_params(cls, line):
        """
        splits the params line and returns a dictionary containing the parameters
        :param line: parameter line to parse
        :return: dictionary describing params
        """
        params = {}
        pairs = line.split(" ")
        for pair in pairs:
            parts = pair.split(":")
            params[parts[0]] = parts[1]

        return params

    @classmethod
    def read_in_experiment(cls, path):
        """

        :param path:
        :return: Experiment object containing data parsed from <path>
        """

        exp = Experiment.blank_experiment()
        exp.path = path

        with open(path, 'r') as f:
            index = 0
            line = f.readline()

            while line != '':
                line = line.rstrip('\n')
                if index == 0:
                    exp.data_set = line.split('\t')[1]
                elif index == 1:
                    exp.run_time = line.split('\t')[1]
                elif index == 2:

                    exp.method = line.split('\t')[1]
                elif index == 3:
                    exp.params = cls.parse_params(line.split('\t')[1])
                elif index > 7:
                    exp.contenders.append(Contender.read_in_contender(line))
                line = f.readline()
                index += 1
        return exp


def read_in_points(data_path):
    """
    Returns data frame containing points from data set
    :param data_path:
    :return: points - pandas data frame representing the datasets points
    """
    points = pd.read_csv(data_path, sep="\t", header=None, names=['x', 'y'])
    return points


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


def plot_frame(contender, points):
    """
    Plots a single image of a contender against the points
    :param contender:
    :param points:
    :return:
    """


if __name__ == '__main__':
    # a = "250 | 0.507485 | ROOT SIN SIN BLANK SUB BLANK BLANK BLANK COS DIV BLANK BLANK BLANK BLANK BLANK BLANK SUB
    # BLANK ADD MLT BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK 8.583254 VAR BLANK BLANK
    # -5.630509 VAR VAR VAR BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK
    # BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK
    # BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK
    # BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK
    # BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK BLANK
    # BLANK" b = Contender.read_in_contender(a) print(b.eq[1])
    pass
