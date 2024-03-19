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
        :param line: Log String
        :return: Contender built form line components
        """

        [evals_string, fitness_string, solution_string] = line.split(' | ')
        evals = int(evals_string)
        fitness = float(fitness_string)
        solution = solution_string.rstrip("\n").rstrip(" ").lstrip(" ")

        contender = cls(evals, fitness, solution)
        return contender


class Experiment:
    def __init__(self, exp_path=None, data_set=None, run_time=None, params=None, method=None, contenders=None):
        """

        :param exp_path:  Path to experiment directory
        :param data_set: Name of Dataset
        :param run_time: Timestamp for experiment run
        :param params: Experiment parameters
        :param method: Optimization Method
        :param contenders: List of contenders
        """
        self.exp_path = exp_path
        self.data_set = data_set
        self.run_time = run_time
        self.params = params
        self.method = method
        self.contenders = [] if contenders is None else contenders

    @classmethod
    def parse_params(cls, line):
        """
        Turns line into dictionary containing parameters of the experiment
        :param line: string of parameters in format <key>:value> seperated by a space
        :return: dictionary containing parameters for the experiment
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
        reads in experiment at the provided path
        :param path: location of experiment log file to be read in
        :return: experiment object containing data from  log file
        """

        exp = Experiment()
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
