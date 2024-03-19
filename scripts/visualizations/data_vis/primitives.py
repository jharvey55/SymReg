import os
import data_vis


class Contender:
    def __init__(self, evals=None, fitness=None, solution=None):
        """

        :param evals: int representing the evaluation for contenders.
        :param fitness: float representing fitness of solution
        :param solution: representation of solution
        """
        self.evals = evals
        self.fitness = fitness
        self.solution = solution

    @classmethod
    def read_in_contender(cls, line):
        """
        Creates a contender from a line in a file with components split by " | "
        :param line:
        :return: contender built form line components
        """

        [evals_string, fitness_string, solution_string] = line.split(' | ')
        evals = int(evals_string)
        fitness = float(fitness_string)
        solution = solution_string.rstrip("\n").rstrip(" ").lstrip(" ")

        contender = cls(evals, fitness, solution)
        return contender

class Cohort:

    def __init__(self, experiments=None, data_set=None, data_path=None, parameters=None,
                 method=None, step_size=1000, data=None, n=None):
        self.experiments = [] if experiments is None else experiments
        self.data_set = data_set
        self.data_path = data_path
        self.parameters = {} if parameters is None else parameters
        self.method = method
        self.step_size = step_size
        self.data = data
        self.n = n

    def load_cohort(self, root_dir):
        pass
